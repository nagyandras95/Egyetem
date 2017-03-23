{-# LANGUAGE FlexibleContexts #-}
module While where

import Control.Applicative
import Control.Monad.Writer
import Control.Monad.State
import Data.Char
import Data.List
import qualified Data.Map as DM
import Data.Maybe (fromJust)
import Parser

-- Típusszinonima az azonosítókra.
type Var = String

-- Az alapvető kifejezések típusa:
data Expr
  = ALit Integer            -- egész számok literálja,
  | BLit Bool               -- logikai értékek literálja,
  | Variable Var            -- azonosító,
  | InfixOp Char Expr Expr  -- infix művelet (operátor).
  deriving (Eq, Show)

-- A nyelvi kifejezések típusa:
data Stm
  = Assignment Var Expr     -- értékadás,
  | Skip                    -- üres utasítás,
  | Seq Stm Stm             -- szekvencia,
  | If Expr Stm Stm         -- elágazás: feltétel, igaz ág, hamis ág,
  | While Expr Stm          -- ciklus: feltétel, ciklusmag.
  deriving (Eq,Show)

-- A While nyelv típusainak lehetséges értékei:
data Type
  = WBoolean           -- logikai érték,
  | WInteger           -- szám,
  | NA                 -- ismeretlen.
  deriving (Eq, Show)

-- A változókat egy véges leképezésben (map) tartjuk karban.
type Variables = DM.Map Var Type

-- Megadja a paraméterként kapott kifejezés típusát.
getType :: Variables -> Expr -> Type
getType _ (ALit _)          = WInteger
getType _ (BLit _)          = WBoolean
getType _ (InfixOp '+' _ _) = WInteger
getType _ (InfixOp '^' _ _) = WBoolean
getType vars (Variable x)   = maybe NA id (DM.lookup x vars)

-- Az újonnan deklarált változókat felveszi a már deklarált változók
-- listájába.
collect :: Variables -> Stm -> Variables
collect vs (Assignment v val@(Variable x))
  | getType vs (Variable v) == NA = DM.insert v (getType vs val) vs
  | otherwise                     = vs
collect vs (Assignment v e) = DM.insert v (getType vs e) vs
collect vs (Seq x y)        = collect (collect vs x) y
collect vs (If _ x y)       = collect (collect vs x) y
collect vs (While _ body)   = collect vs body
collect vs Skip             = vs

whitespace :: Parser String
whitespace = many (matches isSpace)

boolean :: Parser Bool
boolean = (pure conv) <*>  ((token "tt") <|> (token "ff")) where
 conv :: String -> Bool
 conv "tt" = True
 conv "ff" = False


integer :: Parser Integer
integer = ((pure read) :: Parser (String -> Integer)) <*>  (some (matches isDigit))

identifier :: Parser String
identifier = (:) <$> (matches isAlpha) <*> many (matches isAlphaNum)

operator :: Parser Char
operator = toChar <$> (token "+" <|> token "^") where
 toChar:: String -> Char
 toChar [c] = c

expr :: Parser Expr
expr = (whitespace *> expr2 <* whitespace) `chainl1` ( ( \op e1 e2 -> InfixOp op e1 e2) <$> (operator) ) where
 expr2 = (BLit <$> boolean) <|> (ALit <$> integer) <|> (Variable <$> identifier)

stm :: Parser Stm
stm = (whitespace *> allPars <* whitespace) `chainl1` ( ( \_ s1 s2 -> Seq s1 s2) <$> (token ";") )
skipPars = Skip <$ ( whitespace *> token "skip" <* whitespace )
asignPars = Assignment <$> (whitespace *> identifier <* whitespace) <* (whitespace *> token ":=" <* whitespace) <*> (whitespace *> expr <* whitespace)  
ifPars = If <$ (whitespace *> token "if" <* whitespace) <*> (whitespace *> expr <* whitespace) <* (whitespace *> token "then" <* whitespace) <*> (whitespace *> stm <* whitespace <* token "else" <* whitespace ) <*> (whitespace *> stm <* whitespace) <* (whitespace *> token "fi" <* whitespace)
whilePars = While <$ (whitespace *> token "while" <* whitespace) <*> (whitespace *> expr <* whitespace) <* (whitespace *> token "do" <* whitespace) <*> (whitespace *> stm <* whitespace) <* (whitespace *> token "od" <* whitespace) 
allPars = skipPars <|> asignPars <|> whilePars <|> ifPars

accept :: Stm -> ([String], Bool)
accept = checkStm DM.empty
  where
    fine      = ([], True)
    wrong msg = ([msg], False)

    infixr 5 +++
    (+++) :: ([a],Bool) -> ([a],Bool) -> ([a],Bool)
    (xs,b1) +++ (ys,b2) = (xs ++ ys, b1 && b2)

    checkStm :: Variables -> Stm -> ([String],Bool)
    checkStm _ Skip = fine
    checkStm vars (Assignment v e) = c +++ asmType
      where
        asmType
          | getType vars (Variable v) == NA             = fine
          | getType vars (Variable v) == getType vars e = fine
          | otherwise                                   =
            wrong "Incompatible types in assignment."
        c = checkExpr vars e
    checkStm vars (If c a b) = cond +++ condType +++ left +++ right
      where
        left  = checkStm vars a
        right = checkStm (collect vars a) b
        cond  = checkExpr vars c
        condType
          | getType vars c == WBoolean = fine
          | otherwise                  = wrong "Incompatible type in condition."
    checkStm vars (While c a) = cond +++ condType +++ body
      where
        body = checkStm vars a
        cond = checkExpr vars c
        condType
          | getType vars c == WBoolean = fine
          | otherwise                  = wrong "Incompatible type in condition."
    checkStm vars (Seq a b) = s1 +++ s2
      where
        s1 = checkStm vars a
        s2 = checkStm (vars `DM.union` (collect vars a)) b

    checkExpr :: Variables -> Expr -> ([String],Bool)
    checkExpr declVars (ALit _) = fine
    checkExpr declVars (BLit _) = fine
    checkExpr declVars v@(Variable x)
      | getType declVars v == NA = wrong (x ++ " is not initialized.")
      | otherwise                = fine
    checkExpr declVars (InfixOp op a b) = left +++ right +++ opType
      where
        opType =
          case (op, getType declVars a, getType declVars b) of
            ('+',WInteger, WInteger) -> fine
            ('^',WBoolean, WBoolean) -> fine
            ('+',_,_)                -> wrong "Incompatible types in addition."
            ('^',_,_)                -> wrong "Incompatible types in conjunction."
        left  = checkExpr declVars a
        right = checkExpr declVars b



rev :: (a,b) -> (b,a)
rev (x,y) = (y,x)


accept2 :: Stm -> ([String] , Bool)
accept2 x = rev (runWriter (acceptWithWriter DM.empty x))
  where
  acceptWithWriter :: Variables -> Stm -> Writer [String] Bool
  acceptWithWriter _ Skip = return True
  acceptWithWriter vars (Assignment v e) = do
   expre_check <- checkExprWithWriter vars e
   let cond = (getType vars (Variable v) == NA || getType vars (Variable v) == getType vars e)
   when (not cond) (tell["Incompatible types in assignment."])
   return (expre_check && cond)
  acceptWithWriter vars (If c a b) = do
   cond <- checkExprWithWriter vars c
   let condType = getType vars c == WBoolean
   unless condType (tell["Incompatible type in condition."])
   left <- acceptWithWriter vars a
   right <- acceptWithWriter (collect vars a) b
   return (cond && condType && left && right)
  acceptWithWriter vars (While c a) = do
   cond  <- checkExprWithWriter vars c
   let condType = (getType vars c == WBoolean)
   unless condType (tell["Incompatible type in condition."])
   body <- acceptWithWriter vars a
   return (cond && condType && body )
  acceptWithWriter vars (Seq a b) = do
   s1 <- acceptWithWriter vars a
   s2 <- acceptWithWriter (vars `DM.union` (collect vars a)) b
   return (s1 && s2)
     where
  checkExprWithWriter :: Variables -> Expr -> Writer [String] Bool
  checkExprWithWriter declVars (ALit _) = return True
  checkExprWithWriter declVars (BLit _) = return True
  checkExprWithWriter declVars v@(Variable x) = do
   let cond = getType declVars v /= NA 
   unless cond (tell[x ++ " is not initialized."])  
   return (cond)
  checkExprWithWriter declVars (InfixOp op a b) = do
   left <- checkExprWithWriter declVars a
   right <- checkExprWithWriter declVars b 
   case (op, getType declVars a, getType declVars b) of
    ('+',WInteger, WInteger) -> return ()
    ('^',WBoolean, WBoolean) -> return ()
    ('+',_,_)                -> tell ["Incompatible types in addition."]
    ('^',_,_)                -> tell ["Incompatible types in conjunction."]
   return (left && right && ok (op, getType declVars a, getType declVars b))
    where
     ok ('+',WInteger, WInteger) = True
     ok ('^',WBoolean, WBoolean) = True
     ok _ = False
   

   
accept3 :: Stm -> ([String], Bool)
accept3 x = rev (fst (runState (runWriterT (acceptWithWriterState x)) DM.empty))
  where
   acceptWithWriterState :: (MonadState Variables m, MonadWriter [String] m) => Stm -> m Bool
   acceptWithWriterState Skip = return True
   acceptWithWriterState (Assignment v e) = do
    expr_check <- checkExprWithWriterState e
    vars <- get
    if (getType vars (Variable v) == NA || getType vars (Variable v) == getType vars e)
     then return ()
     else tell["Incompatible types in assignment."]
    put (vars)
    return (expr_check && (getType vars (Variable v) == NA || getType vars (Variable v) == getType vars e))
   acceptWithWriterState (If c a b) = do  
    cond <- checkExprWithWriterState c
    vars <- get
    if (getType vars c == WBoolean)
     then return ()
     else tell["Incompatible type in condition."]
    left <- acceptWithWriterState a
    put ((collect vars a))
    right <- acceptWithWriterState b
    put (vars)
    return (cond && left && right && (getType vars c == WBoolean))
   acceptWithWriterState (While c a) = do 
    cond <- checkExprWithWriterState c
    vars <- get
    if (getType vars c == WBoolean)
     then return ()
     else tell["Incompatible type in condition."]
    body <- acceptWithWriterState a
    return (cond && (getType vars c == WBoolean) && body)
   acceptWithWriterState (Seq a b) = do
    s1 <- acceptWithWriterState a
    vars <- get
    put (((collect vars a) `DM.union` vars))
    s2 <- acceptWithWriterState b
    return (s1 && s2)
      where
   checkExprWithWriterState :: (MonadState Variables m, MonadWriter [String] m) => Expr -> m Bool
   checkExprWithWriterState (ALit _) = return True
   checkExprWithWriterState (BLit _) = return True
   checkExprWithWriterState v@(Variable x) = do
    declVars <- get
    if getType declVars v == NA
     then tell[x ++ " is not initialized."]
     else return ()
    put (declVars)
    return ((getType declVars v) /= NA)
   checkExprWithWriterState (InfixOp op a b) = do
    left <- checkExprWithWriterState a
    right <- checkExprWithWriterState b
    declVars <- get
    case (op, getType declVars a, getType declVars b) of
     ('+',WInteger, WInteger) -> return ()
     ('^',WBoolean, WBoolean) -> return ()
     ('+',_,_)                -> tell ["Incompatible types in addition."]
     ('^',_,_)                -> tell ["Incompatible types in conjunction."]
    put (declVars)
    return (left && right && ok (op, getType declVars a, getType declVars b))
     where
      ok ('+',WInteger, WInteger) = True
      ok ('^',WBoolean, WBoolean) = True
      ok _ = False 



--
-- Tesztek
--

-- Szintaxisfa beolvasása fájlból.
parseFromFile :: FilePath -> IO ()
parseFromFile fp = readFile fp >>= print . parseAs stm

-- Szintaxisfa beolvasása fájlból és ellenőrzése.
parseAndAcceptFromFile :: FilePath -> (Stm -> ([String], Bool)) -> IO ()
parseAndAcceptFromFile fp f = readFile fp >>=  print . f . fromJust . parseAs stm

whitespaceTest =
  [ runParser whitespace "  as" == [("  ","as"),(" "," as"),("","  as")] ]

booleanTest =
  [ runParser boolean "tt asd"   == [(True, " asd")]
  , runParser boolean "ff asd"   == [(False, " asd")]
  , runParser boolean "astt asd" == []
  ]

integerTest =
  [ parseAs integer "123"   == Just 123
  , parseAs integer "0123"  == Just 123
  , runParser integer "a12" == []
  ]

identifierTest =
  [ runParser identifier "asd" == [("asd",""),("as","d"),("a","sd")]
  , runParser identifier "1asd" == []
  , runParser identifier "x" == [("x","")]
  , runParser identifier "Ax" == [("Ax",""),("A","x")]
  ]

operatorTest =
  [ runParser operator "+ asd" == [('+', " asd")]
  , runParser operator "^ asd" == [('^', " asd")]
  , runParser operator "? asd" == []
  ]

pts = sequence
  [ pure $ parseAs stm "x:=1 y:=2" == Nothing
  , pure $ parseAs stm "if tt skip" == Nothing
  , pure $ parseAs stm "if tt then skip" == Nothing
  , pure $ parseAs stm "if tt then skip skip" == Nothing
  , pure $ parseAs stm "if tt then skip else skip" == Nothing
  , pure $ parseAs stm "while" == Nothing
  , pure $ parseAs stm "while ff" == Nothing
  , pure $ parseAs stm "while ff do" == Nothing
  , pure $ parseAs stm "while ff do x:=1" == Nothing
  , pure $ parseAs stm "x:=x+1" == Just (Assignment "x" (InfixOp '+' (Variable "x") (ALit 1)))
  , pure $ parseAs stm "if tt then skip else skip fi" == Just (If (BLit True) Skip Skip)
  , pure $ parseAs stm "while ff do x:=1 od" == Just (While (BLit False) (Assignment "x" (ALit 1)))
  , pure $ parseAs stm "x:=1; y:=2" == Just (Seq (Assignment "x" (ALit 1)) (Assignment "y" (ALit 2)))
  , pure $ parseAs expr "1" == Just (ALit 1)
  , pure $ parseAs expr "tt" == Just (BLit True)
  , pure $ parseAs expr "ff" == Just (BLit False)
  , pure $ parseAs expr "1+1+1+1" == Just (InfixOp '+' (InfixOp '+' (InfixOp '+' (ALit 1) (ALit 1)) (ALit 1)) (ALit 1))
  , pure $ parseAs expr "1+1+1+x" == Just (InfixOp '+' (InfixOp '+' (InfixOp '+' (ALit 1) (ALit 1)) (ALit 1)) (Variable "x"))
  , pure $ parseAs expr "tt ^ tt  ^ ff" == Just (InfixOp '^' (InfixOp '^' (BLit True) (BLit True)) (BLit False))
  , pure $ parseAs expr "tt ^ x  ^ ff" == Just (InfixOp '^' (InfixOp '^' (BLit True) (Variable "x")) (BLit False))
  , pure $ parseAs expr "x" == Just (Variable "x")
  , (==) <$> (readFile "good/good1.while" >>= return . parseAs stm) <*> (pure $ Just good1AST)
  , (==) <$> (readFile "good/good2.while" >>= return . parseAs stm) <*> (pure $ Just good2AST)
  , (==) <$> (readFile "bad/bad1.while" >>= return . parseAs stm) <*> (pure $ Just bad1AST)
  , (==) <$> (readFile "bad/bad2.while" >>= return . parseAs stm) <*> (pure $ Just bad2AST)
  , (==) <$> (readFile "bad/bad3.while" >>= return . parseAs stm) <*> (pure $ Just bad3AST)
  , (==) <$> (readFile "bad/bad4.while" >>= return . parseAs stm) <*> (pure $ Just bad4AST)
  , (==) <$> (readFile "bad/bad5.while" >>= return . parseAs stm) <*> (pure $ Just bad5AST)
  ]

good1AST = Seq (Seq (Seq (Assignment "x" (ALit 5)) (While (BLit True)
  (Assignment "x" (InfixOp '+' (Variable "x") (ALit 1))))) (Assignment "b" (BLit True)))
  (If (Variable "b") (Assignment "x" (ALit 4)) (Assignment "x" (ALit 5)))

good2AST = Seq (Seq (Seq (Assignment "x" (ALit 1)) (Assignment "b" (BLit True)))
 (Assignment "identifier1" (ALit 1))) (While (Variable "b") (If (BLit False)
 (Assignment "x" (InfixOp '+' (InfixOp '+' (Variable "x") (Variable "identifier1"))
 (ALit 1))) (Seq (Assignment "x" (InfixOp '+' (Variable "x") (ALit 2)))
 (While (Variable "b") (Assignment "identifier1" (InfixOp '+' (Variable "x") (ALit 5)))))))

bad1AST = Seq (Assignment "x" (ALit 1)) (If (Variable "x") (Assignment "x" (ALit 1)) Skip)
bad2AST = While (Variable "x") (Assignment "z" (BLit True))
bad3AST = Seq (If (Variable "x") (Seq (Assignment "z" (Variable "y"))
  (Assignment "a" (BLit True))) Skip) (Assignment "a" (ALit 5))

bad4AST = Seq (Assignment "x" (ALit 4)) (While (Variable "x")
  (Seq (Assignment "b" (BLit True)) (If (Variable "x")
  (Seq (Seq (Seq (Assignment "b" (ALit 5)) Skip) (Assignment "x" (Variable "y")))
  (Assignment "a" (ALit 5))) (Seq (Seq (Seq Skip (Assignment "b" (BLit False))) Skip)
  (Assignment "a" (BLit False))))))

bad5AST = Seq (Seq (Seq (Seq (Assignment "x" (ALit 5))
  (Assignment "x" (BLit True))) (Assignment "y" (Variable "x")))
  (While (Variable "y") Skip)) (If (InfixOp '^' (BLit True) (BLit False))
  (Assignment "x" (InfixOp '+' (Variable "z") (ALit 1))) Skip)

acceptWithWriterTest =
  [ accept ast == accept2 ast | ast <- astList ]
    where
      astList =
        [ good1AST
        , good2AST
        , bad1AST
        , bad2AST
        , bad3AST
        , bad4AST
        , bad5AST
        ]

acceptWithWriterStateTest =
  [ accept ast == accept3 ast | ast <- astList ]
    where
      astList =
        [ good1AST
        , good2AST
        , bad1AST
        , bad2AST
        , bad3AST
        , bad4AST
        , bad5AST
        ]

tests = do
  parseTest <- pts
  let all_tests =
        [ whitespaceTest
        , booleanTest
        , integerTest
        , identifierTest
        , operatorTest
        , parseTest
        , acceptWithWriterTest
        , acceptWithWriterStateTest
        ]
  return (and (concat all_tests), all_tests)
