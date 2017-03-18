> module Parser (
>   Parser(..),
>   char,
>   token,
>   runParser,
>   parseAs,
>   matches,
>   chainl,
>   chainl1
> ) where
>
> import Control.Applicative
> import Data.List

Ez a modul egy szintaktikai elemzőt definiál, amelyet a `Parser` típussal
és annak műveleteivel írunk le.

> newtype Parser a = P (String -> [(a, String)])
>
> runParser :: Parser a -> String -> [(a, String)]
> runParser (P p) s = p s
>
> parseAs :: Parser a -> String -> Maybe a
> parseAs p s = fst <$> find (\(x,s) -> null s) (runParser p s)

Az elemző a következő kombinátorokkal rendelkezik:

 - `char` : Egy paraméterként kapott karaktert ismer fel a bemenet elejéről.
   Példa az alkalmazására:

     ~~~
     runParser (char 'a') "alma" == [('a',"lma")]
     ~~~

> char :: Char -> Parser Char
> char c = P $ \s -> case s of
>   (x : xs) | x == c -> [(x, xs)]
>   _                   -> []

 - `token` : Egy paraméterként kapott karaktersorozatot ismer fel a
   bemenet elejéről.  Például:

     ~~~
     runParser (token "al") "alma" == [("al","ma")]
     ~~~

> token :: String -> Parser String
> token = foldr (\x xs -> (:) <$> char x <*> xs) (pure "")

 - `matches`: A paraméterként kapott függvény kiértékelésével eldönti, hogy a
   bemenet elején szereplő karaktert elfogadja-e.

     ~~~
     runParser (matches isLetter) "alma" == [('a',"lma")]
     ~~~

> matches :: (Char -> Bool) -> Parser Char
> matches p = P (\s -> case s of
>   (x : xs) | p x -> [(x,xs)]
>   _              -> [])

A `Parser` típus továbbá megvalósítja az `Alternative` osztályt, amely révén a
következő további műveletek érhető el:

> instance Alternative Parser where
>   empty           = P $ \s -> []
>   (P p) <|> (P q) = P $ \s -> p s ++ q s

 - `<|>`: Alternatívák megadása a következő módon:

     ~~~
     runParser (char 'x' <|> char 'y') "xsd" == [('x',"sd")]
     runParser (char 'x' <|> char 'y') "ysd" == [('y',"sd")]
     ~~~

 - `many`: Adott elemező szerint nulla vagy több szövegrészlet felismerése.
   Például:

     ~~~
     runParser (many (matches isLetter)) "alma1" ==
       [("alma","1"),("alm","a1"),("al","ma1"),("a","lma1"),("","alma1")]
     ~~~

 - `some`: Az előzőhöz hasonlóan működő függvény, azzal a különbséggel, hogy
   a `many` megengedi, hogy nem ismerünk fel egy karaktert sem, a `some`
   esetén viszont legalább egy karaktert fel kell dolgoznunk a bemenetből.

A `Parser` típus megvalósítja a `Functor` és `Applicative` osztályokat is, tehát
applikatív funktorként tud viselkedni.

> instance Functor Parser where
>   fmap f x = pure f <*> x
>
> instance Applicative Parser where
>   (P pf) <*> (P q) = P $ \s -> [(f x, s2) | (f, s1) <- pf s, (x, s2) <- q s1]
>   pure x           = P $ \s -> [(x, s)]

Ennek egyik következménye, hogy az elemzőket egymás után tudjuk kapcsolni, és
például össze tudjuk fűzni az általuk rendre felismert részeket egyetlen
`String` értékké.  Tekintsük például azt, hogy az első karakter legyen nagy betű,
utána pedig bármennyi betű.

~~~
runParser ((:) <$> (matches isUpper) <*> many (matches isLetter)) "Alma" ==
  [("Alma",""),("Alm","a"),("Al","ma"),("A","lma")]
~~~

Előfordulhat azonban, hogy a következő nyelvtani szabályt szeretnénk ezen a
módon megvalósítani, amely szóközzel elválasztott `'a'` betűk sorozatát ismeri
fel:

~~~
S -> 'a' | S ' ' S
~~~

Erre az eddigiek segítségével következő elemzőt írhatnánk fel, amely azonban
nem fog terminálni:

~~~
let s = ((:[]) <$> char 'a') <|> ((:) <$> s <* char ' ' *> s)
runParser s "a a a a" --> [(()," a a a"),(()," a a"),(()," a"),((),"") ...
~~~

Ennek az az oka, hogy ez egy balrekurzív szabály, amelyet ezzel a módszerrel
közvetlenül nem tudunk kezelni.  Feloldásképpen erre definiálhatjuk a `chainl`
és `chainl1` kombinátorokat, amelyek a fenti alakú szabályok felismerésére
használható függvények.  A `chainl` nulla vagy több, a `chainl1` pedig legalább
egy elválasztó szimbólum jelenlétét feltételezi.

~~~
let s1 = ((:[]) <$> char 'a') `chainl1` ((\_ x y -> x ++ y) <$> ((:[]) <$> char ' '))
runParser s1 "a a a a" == [("aaaa",""),("aaa"," a"),("aa"," a a"),("a"," a a a")]
~~~

> chainl :: Parser a -> Parser (a -> a -> a) -> a -> Parser a
> chainl p op a = (p `chainl1` op) <|> pure a

> chainl1 :: Parser a -> Parser (a -> a -> a) -> Parser a
> chainl1 p op = foldl (flip ($)) <$> p <*> many (flip <$> op <*> p)
