module Assignment2 where

import Control.Concurrent
import Control.Concurrent.Chan
import Control.Concurrent.STM       -- cabal install stm
import Control.Concurrent.STM.TChan
import Control.DeepSeq
import Control.Exception
import Control.Monad
import Control.Monad.Par            -- cabal install monad-par
import Control.Parallel.Strategies  -- cabal install parallel
import Data.List hiding (insert)
import Data.Maybe
import Data.Time.Clock
import System.Random                -- cabal install random
import Test.QuickCheck              -- cabal install QuickCheck
import Test.QuickCheck.Test

-- A szinusz függvény közelítése hatványsorral.
sine :: (Floating a, RealFrac a, Integral b) => a -> b -> a
sine x n = go x' 1.0 x' 1
  where
    x' = x - ((2.0 * pi) * (fromIntegral (floor (x / (pi * 2.0)))))
    go h f s i
      | i >= n    = s'
      | otherwise = go h' f' s' (i + 1)
      where
        h' = h * x' * x' * (-1.0)
        f' = f * 2.0 * fromIntegral i * (2.0 * fromIntegral i + 1.0)
        s' = s + (h' / f')

prop_sine :: Double -> Property
prop_sine = undefined

-- Az AVL-fa típusdefiníciója és adatkonstruktorai:
data AVLTree a
  = E                           -- üres fa,
  | N (AVLTree a) a (AVLTree a) -- csomópont két, egy bal- és jobb oldali
                                -- részfával.
  deriving (Eq, Show)

-- Üres AVL-fa.
empty :: AVLTree a
empty = E

-- Tartalmazási vizsgálat AVL-fára.
memberOf :: Ord a => a -> AVLTree a -> Bool
memberOf _ E = False
memberOf e (N left x right)
  | e == x = True
  | e < x  = e `memberOf` left
  | e > x  = e `memberOf` right

-- Az AVL-fa inorder bejárása.
inorder :: AVLTree a -> [a]
inorder E                = []
inorder (N left x right) = inorder left ++ [x] ++ inorder right

-- Az AVL-fa kiegyensúlyozottságának vizsgálata.  A fa kiegyensúlyozott, ha
-- minden csúcsra igaz, hogy a két részfájának a magasságkülönbsége maximum
-- 1.
isBalanced :: AVLTree a -> Bool
isBalanced E                  = True
isBalanced t@(N left _ right) =
  isBalanced left && isBalanced right && abs (skew t) <= 1

-- Elem beszúrása a fába a kigyensúlyozottság megőrzésével
insert :: Ord a => a -> AVLTree a -> AVLTree a
insert e E = N E e E
insert e (N left x right)
  | e < x  = balance (N (insert e left) x right)
  | e == x = N left x right
  | e > x  = balance (N left x (insert e right))
  where
    balance t@(N left x right)
      | skew t == 2 && skew left == (-1)  = rotateLeftRight t
      | skew t == 2                       = rotateRight t
      | skew t == (-2) && skew right == 1 = rotateRightLeft t
      | skew t == (-2)                    = rotateLeft t
    balance t = t

    rotateRight     (N (N x a y) b z) = N x a (N y b z)
    rotateLeft      (N x a (N y b z)) = N (N x a y) b z
    rotateLeftRight (N x a y)         = rotateRight (N (rotateLeft x) a y)
    rotateRightLeft (N x a y)         = rotateLeft (N x a (rotateRight y))

-- AVL-fa magassága.
height :: AVLTree a -> Int
height E                = 0
height (N left _ right) = 1 + max (height left) (height right)

-- Két részfa magasságának különbsége, a fa dőlésének aránya.
skew :: AVLTree a -> Int
skew E                = 0
skew (N left _ right) = height left - height right

-- Lista rendezettségének vizsgálata.
isOrdered :: Ord a => [a] -> Bool
isOrdered xs = and $ zipWith (<=) xs (tail xs)

-- AVL-fák véletlenszerű előállítása QuickCheck-generátorral.
instance (Random a, Ord a, Arbitrary a) => Arbitrary (AVLTree a) where
  arbitrary = undefined

-- A generátor helyes működésének tesztelése.
test_arbitrary :: AVLTree Int -> Bool
test_arbitrary t = isOrdered (inorder t) && isBalanced t

-- Az AVL-fa műveleteinek helyességét ellenőrző programtulajdonságok.
prop_avl1 :: (Ord a, Arbitrary a) => NonEmptyList a -> AVLTree a -> Property
prop_avl1 = undefined

prop_avl2 :: (Ord a, Arbitrary a) => NonEmptyList a -> AVLTree a -> Property
prop_avl2 = undefined

prop_avl3 :: (Ord a, Arbitrary a) => NonEmptyList a -> AVLTree a -> Property
prop_avl3 = undefined

-- Összefésüléses rendezés, szekvenciális változat.
mergeSort :: Ord a => [a] -> [a]
mergeSort []     = []
mergeSort xs@[_] = xs
mergeSort xs     = merge (mergeSort ys1) (mergeSort ys2)
  where
    (ys1, ys2) = split xs

    -- A paraméterül kapott lista felbontása két részlistára.
    split []       = ([], [])
    split [x]      = ([x], [])
    split (x:y:xs) = (x:xs1, y:xs2)
      where (xs1, xs2) = split xs

    -- Két lista rendezett összefésülése.
    merge [] ys = ys
    merge xs [] = xs
    merge as@(x:xs) bs@(y:ys)
      | x < y     = x : merge xs bs
      | otherwise = y : merge as ys

-- Konkurens változat.
mergeSortC :: Ord a => [a] -> IO [a]
mergeSortC = undefined

-- Párhuzamos változat.
mergeSortP :: (NFData a, Ord a) => [a] -> [a]
mergeSortP = undefined

-- Prímek keresése, szekvenciális változat.
primes :: Integer -> [Integer]
primes n = f [2..n]
  where
    f []     = []
    f (p:xs) = p : f [ x | x <- xs, x `mod` p /= 0 ]

-- Konkurens változat.
primesC :: Integer -> IO [Integer]
primesC = undefined

-- Párhuzamos változat.
primesP :: Integer -> [Integer]
primesP = undefined

--
-- Tesztek
--

-- Akció futási idejének mérése.  Ez csupán megközelítő érték, illetve csak
-- "wall-clock" időt méri, vagyis a ténylegesen processzoron töltött időt
-- nem.
measure m = do
  t1 <- getCurrentTime
  x <- m
  t2 <- getCurrentTime
  return (x, diffUTCTime t2 t1)

-- Értékek azonosságnak vizsgálata.
identical xs@(_:_) = and (zipWith (==) xs (tail xs))
identical _        = True

-- Egy függvény különböző változatainak összehasonlítása adott tesztesetekre.
compete s (f1, f2, f3) ts = do
  r <- try $ do
    putStrLn $ "==> " ++ s
    rs <- forM (zip [1..] ts) $ \(n, t) -> do
      putStrLn $ "Test case #" ++ show n
      putStr " - sequential: "
      r1@(xs1,t1) <- measure $ do
        evaluate $ force $ f1 t
      print t1
      putStr " - concurrent: "
      r2@(xs2,t2) <- measure $ do
        force <$> f2 t
      print t2
      putStr " - parallel: "
      r3@(xs3,t3) <- measure $ do
        evaluate $ force $ f3 t
      print t3
      when (not $ identical [xs1,xs2,xs3]) $
        putStrLn "Warning: The results are not the same."
      return (r1, r2, r3)
    let (is,es) = unzip [ (identical [v1,v2,v3], t2 < t1 && t3 < t1)
                        | ((v1,t1),(v2,t2),(v3,t3)) <- rs
                      ]
    putStrLn $ "<== " ++ s
    return (and is, and es)
  case r of
    Left err -> do
      putStrLn $ "There was an exception: " ++ show (err :: SomeException)
      return (False, False)
    Right x -> return x

-- QuickCheck-tulajdonság teljesülésének ellenőrzése.
checkProperty p = isSuccess <$> quickCheckWithResult stdArgs p

tests = do
  putStrLn "Property for `sine`:"
  propSineWorks <- checkProperty prop_sine
  putStrLn "Arbitrary instance for AVLTree:"
  arbitraryAvlWorks <- checkProperty test_arbitrary
  avlPropertiesWork <-
    forM (zip [1..] [prop_avl1, prop_avl2, prop_avl3]) $ \(n,p) -> do
      putStrLn $ "AVL property #" ++ show n ++ ":"
      checkProperty (p :: NonEmptyList Integer -> AVLTree Integer -> Property)
  let n = 100000 :: Integer
  let xs1 = [n, n - 1 .. 1]
  let xs2 = [1 .. n]
  let xs3 = [n, n - 1 .. (n `div` 2)] ++ [1 .. (n `div` 2) - 1]
  let xs4 = [ (-1)^x * x | x <- [1..n] ]
  (identicalMergeSort, effectiveMergeSort) <-
    compete "mergesort" (mergeSort, mergeSortC, mergeSortP) [xs1, xs2, xs3, xs4]
  let n = 5000
  (identicalPrimes, effectivePrimes) <-
    compete "primes" (primes, primesC, primesP) [n, n * 2, n * 4, n * 8]
  let criteria = [ propSineWorks
                 , arbitraryAvlWorks ] ++
                 avlPropertiesWork ++
                 [ effectiveMergeSort, identicalMergeSort
                 , effectivePrimes, identicalPrimes
                 ]
  return (and criteria, criteria)
