module Huffman

import StdEnv, StdLib

:: Bit = Zero | One

:: Frequency :== (Char, Int)

:: Frequencies :== ([Frequency], Int)

:: CodeTree = Node Int CodeTree CodeTree
            | Leaf Char

::Code :== [Bit]


instance == Bit where
  (==) Zero Zero = True
  (==) One One = True
  (==) _ _ = False

instance == CodeTree where
  (==) (Leaf a) (Leaf b) = a == b
  (==) (Node x aLeft aRight) (Node y bLeft bRight) = x == y && aLeft == bLeft && aRight == bRight
  (==) _ _ = False

getFrequencies :: String -> [Frequency]
getFrequencies str = frequency (fromString str) []
	where
		frequency :: [Char] [Char] -> [Frequency]
		frequency [] _ = []
		frequency [x:xs] chars
			| not (isMember x chars) =  [ (x, 1 + length (filter (\c -> c == x) xs ) ) : frequency xs [x:chars] ]
			| otherwise = frequency xs chars

frequencyToFrequencies :: [Frequency] -> [Frequencies]
frequencyToFrequencies frs = map ( \(c,n) -> ([(c,n)],n) ) frs

toOneFrequencies :: [Frequencies] -> [Frequencies]
toOneFrequencies [f] = [f]
toOneFrequencies [ (x,n):(y,l):xs ] = toOneFrequencies [(y ++ x, n + l) : xs]

buildTree :: [Frequencies] -> CodeTree
buildTree frs = build (getOne (toOneFrequencies (sortFrequencies frs)))
	where
		build :: Frequencies -> CodeTree
		build ( [ (c,_) ] , _ ) = Leaf c
		build ( [ (c,n) : xs ] , s) = Node s (Leaf c) (build ( xs , s - n))
		getOne:: [a] -> a
		getOne [x] = x



frequencyIsBetter :: Frequencies Frequencies -> Bool
frequencyIsBetter f1 f2 = (snd f1 < snd f2)

sortFrequencies :: [Frequencies] -> [Frequencies]
sortFrequencies frs = sortBy frequencyIsBetter frs

lookupCode :: CodeTree Char -> Code
lookupCode tree c = reverse  (fst (look tree c []))
	where
		look :: CodeTree Char Code -> (Code,Bool)
		look (Leaf c) ch co
			| ch == c = (co,True)
			| otherwise = (co,False)
		look (Node _ (ct1) (ct2) ) ch co 
			| snd leftTree = (fst leftTree,True)
			| snd rightTree = (fst rightTree,True)
				where
					leftTree = look ct1 ch [Zero:co]
					rightTree = look ct2 ch [One:co]
					

lookup :: CodeTree Code -> (Char,Code)
lookup (Leaf c) co = (c,co)
lookup (Node _ lt rt) [Zero:cs] = lookup lt cs
lookup (Node _ lt rt) [One:cs] = lookup rt cs

lookupPrefix :: CodeTree Code -> Char
lookupPrefix t c  = fst (lookup t c)


encode :: String -> (CodeTree, Code)
encode str = (tree,co)
	where
		tree = (buildTree o frequencyToFrequencies o getFrequencies) str	
		co = flatten ( map (\c -> lookupCode tree c) (fromString str) )			

decode :: (CodeTree, Code) -> String
decode (tree, c) = toString (reverse (accdecode tree c []))
	where 
		accdecode :: CodeTree Code [Char] -> [Char]
		accdecode tree [] s = s
		accdecode tree c s = accdecode tree resCode [ resChar : s]
		where 
			(resChar,resCode) = lookup tree c

Start = decode (encode "alma")
/*(and (flatten allTests), allTests)
  where
    allTests =
      [ test_getFrequencies
      , test_frequencyToFrequencies
      , test_sortFrequencies
      , test_buildTree
      , test_lookupCode
      , test_lookupPrefix
      , test_encode
      , test_decode
      ]*/

test_getFrequencies =
  [ isEmpty (getFrequencies "")
  , and (map (\x -> isMember x (getFrequencies "abrakadabra")) [('r',2),('k',1),('d',1),('b',2),('a',5)])
  , and (map (\x -> isMember x (getFrequencies "Szeretem a clean-t")) [('z',1),('t',2),('r',1),('n',1),('m',1),('l',1),('e',4),('c',1),('a',2),('S',1),('-',1),(' ',2)])
  , and (map (\x -> isMember x (getFrequencies "adadada")) (getFrequencies "dadadaa"))
  ]

test_frequencyToFrequencies =
  [
    frequencyToFrequencies [('r',2),('k',1),('d',1),('b',2),('a',5)] == [([('r',2)],2),([('k',1)],1),([('d',1)],1),([('b',2)],2),([('a',5)],5)]
  ]

test_sortFrequencies = 
  [ sort (map snd (sortFrequencies [([('r',2)],2),([('d',1)],1),([('k',1)],1),([('b',2)],2),([('a',5)],5)])) == [1,1,2,2,5]
  ]

test_buildTree = 
  [ buildTree [([('a',1)],1)] == Leaf 'a'
  , buildTree [([('a',1)],1), ([('b',2)],2)] == Node 3 (Leaf 'a') (Leaf 'b') || buildTree [([('a',1)],1), ([('b',2)],2)] == Node 3 (Leaf 'b') (Leaf 'a')
  , countNodes (buildTree (frequencyToFrequencies (getFrequencies "sokféle karakterbõl álló szöveg"))) == 37
  ]
    where
      countNodes (Leaf _) = 1
      countNodes (Node _ left right) = 1 + (countNodes left) + (countNodes right)

test_lookupCode = 
  [ lookupCode abrakadabra 'a' == [Zero]
  , lookupCode abrakadabra 'b' == [One,Zero,One]
  , lookupCode abrakadabra 'd' == [One,One,One]
  , lookupCode (Leaf 'a') 'a'  == [Zero]
  ]
  where
    abrakadabra = Node 11 (Leaf 'a') (Node 6 (Node 4 (Leaf 'r') (Leaf 'b')) (Node 2 (Leaf 'k') (Leaf 'd')))

test_lookupPrefix =
  [ lookupPrefix abrakadabra (lookupCode abrakadabra 'a') == 'a'
  , lookupPrefix abrakadabra (lookupCode abrakadabra 'b') == 'b'
  , lookupPrefix abrakadabra (lookupCode abrakadabra 'd') == 'd'
  , lookupPrefix abrakadabra (lookupCode (Leaf 'a') 'a')  == 'a'
  ]
  where
    abrakadabra = Node 11 (Leaf 'a') (Node 6 (Node 4 (Leaf 'r') (Leaf 'b')) (Node 2 (Leaf 'k') (Leaf 'd')))

test_encode =
  [ (length o snd) (encode "abrakadabra") == 23
  , encode "aaaaa" == (Leaf 'a', [Zero,Zero,Zero,Zero,Zero])
  ]

test_decode =
  [ decode (encode "Decode function test") == "Decode function test"
  ,  decode (encode "Functional programming is fun!") == "Functional programming is fun!"
  ,  decode (abrakadabra, [Zero,One,Zero,One,One,Zero,Zero,Zero,One,One,Zero]) == "abrak"
  ]
  where
    abrakadabra = Node 11 (Leaf 'a') (Node 6 (Node 4 (Leaf 'r') (Leaf 'b')) (Node 2 (Leaf 'k') (Leaf 'd')))
