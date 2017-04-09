module bst

import StdEnv, StdLib, GenEq, StdMaybe


:: BSTree a = Empty | Node a (BSTree a) (BSTree a)

:: KeyValue a b = KV a b

derive gEq BSTree, KeyValue, Maybe, MapKV

BSTree_emptyInt :: BSTree Int
BSTree_emptyInt = Empty

BSTree_emptyKV  :: BSTree (KeyValue Int Char)
BSTree_emptyKV = Empty


BSTree_insert :: (BSTree a) a -> (BSTree a) | < a
BSTree_insert Empty e = Node e Empty Empty
BSTree_insert (Node n t1 t2) e
	| e < n = Node n (BSTree_insert t1 e) t2   
	| n < e = Node n t1 (BSTree_insert t2 e)  
	| otherwise = (Node n t1 t2)


BSTree_lookup :: (BSTree a) a -> Maybe a | < a
BSTree_lookup Empty _ = Nothing
BSTree_lookup (Node n t1 t2) e
	| n < e = BSTree_lookup t2 e
	| n > e = BSTree_lookup t1 e
	| otherwise = Just n
	
BSTree_depth :: (BSTree a) -> Int
BSTree_depth Empty = 0
BSTree_depth (Node _ t1 t2) = 1 + ( max (BSTree_depth t1) (BSTree_depth t2) )

BSTree_isBalanced :: (BSTree a) -> Bool
BSTree_isBalanced Empty = True
BSTree_isBalanced (Node _ t1 t2) =  abs ((BSTree_depth t1 - BSTree_depth t2)) < 2

class Traversable t where
	inOrder :: (a b -> b) b (t a) -> b
	preOrder :: (a b -> b) b (t a) -> b
	postOrder :: (a b -> b) b (t a) -> b
	
instance Traversable BSTree where

	inOrder :: (a b -> b) b (BSTree a) -> b
	inOrder f k Empty = k
	inOrder f k (Node n t1 t2) = inOrder f (f n (inOrder f k t1) ) t2
	

	preOrder :: (a b -> b) b (BSTree a) -> b
	preOrder f k Empty = k
	preOrder f k (Node n t1 t2) = preOrder f (preOrder f (f n k) t1) t2 
	
	postOrder :: (a b -> b) b (BSTree a) -> b
	postOrder f k Empty = k
	postOrder f k (Node n t1 t2) = f n (postOrder f (postOrder f k t1) t2)
	

sortBSTree :: (BSTree a) -> [a]
sortBSTree t = inOrder (\x s -> s ++ [x] ) [] t

:: MapKV k v = M (BSTree (KeyValue k v))

instance < (KeyValue a b) | < a
 where
	< (KV a _) (KV c _) = a < c 
			
MapKV_update :: (MapKV k v) k (v -> Maybe v) -> MapKV k v | < k
MapKV_update (M tree) key f = M (my_update tree (BSTree_lookup tree (KV key undef)))
	where
		//my_update :: (BSTree (KeyValue k v)) (Maybe (KeyValue k v)) ->  (BSTree (KeyValue k v))
		my_update tree Nothing = tree
		my_update (Node (KV k1 v1) t1 t2) (Just e) 
			| key < k1 = Node (KV k1 v1) (my_update t1 (Just e)) t2
			| k1 < key = Node (KV k1 v1) t1 (my_update t2 (Just e))
			| otherwise = maybe_update (Node (KV k1 v1) t1 t2) (f v1)
			
				where
					maybe_update tree Nothing = tree
					maybe_update (Node (KV k2 v2) t1 t2) (Just e1) = (Node (KV k2 e1) t1 t2)


MapKV_lookup :: (MapKV k v) k -> Maybe (KeyValue k v) | < k
MapKV_lookup (M tree) key = BSTree_lookup tree (KV key undef)

MapKV_insert :: (MapKV k v) k v -> (MapKV k v) | < k
MapKV_insert (M tree) key val = M (BSTree_insert tree (KV key val))

testIntBSTree =
  (Node 1 (Node 0 Empty Empty)
  (Node 21 (Node 4 (Node 2 Empty Empty)
  (Node 6 Empty (Node 8 Empty Empty)))
  (Node 63 Empty Empty)))
  
testKVBSTree =
  (Node (KV 6 'a')
  (Node (KV 4 'c')
  (Node (KV 3 'l') Empty Empty)
  (Node (KV 5 'y') Empty Empty))
  (Node (KV 9 'r')
  (Node (KV 7 's') Empty
  (Node (KV 8 'q') Empty Empty))
  (Node (KV 10 'p') Empty
  (Node (KV 50 'o') Empty Empty))))
  
test_BSTRe_Empty =
  [ BSTree_emptyInt === Empty
  , BSTree_emptyKV === Empty
  ]
  
test_BSTree_insert =
  [ BSTree_insert BSTree_emptyInt 3 ===
    Node 3 Empty Empty
  , BSTree_insert (BSTree_insert BSTree_emptyInt 3) 5 ===
    Node 3 Empty (Node 5 Empty Empty)
  , BSTree_insert (BSTree_insert BSTree_emptyInt 3) 3 ===
    Node 3 Empty Empty
  , BSTree_insert (BSTree_insert BSTree_emptyInt 3) 1 ===
    Node 3 (Node 1 Empty Empty) Empty
  ]
  
test_BSTree_lookup =
  [ BSTree_lookup testIntBSTree 21 === Just 21
  , map (BSTree_lookup testIntBSTree) [3, 7, 50, 100] === repeatn 4 Nothing
  , BSTree_lookup Empty 'x' === Nothing
  , BSTree_lookup testKVBSTree (KV 3 undef) === Just (KV 3 'l')
  ]
  
test_BSTree_depth =
  [ BSTree_depth BSTree_emptyInt == 0
  , BSTree_depth BSTree_emptyKV == 0
  , BSTree_depth testIntBSTree == 5
  , BSTree_depth testKVBSTree == 4
  ]
  
test_BSTree_isBalanced =
  [ BSTree_isBalanced Empty == True
  , BSTree_isBalanced testIntBSTree == False
  , BSTree_isBalanced testKVBSTree == True
  ]
  
instance toString (KeyValue a b) | toString a & toString b
  where
    toString (KV x y) = "key: " +++ toString x +++ ", value: " +++ toString y

test_Traversable =
  [ inOrder (\x s -> s +++ toString x +++ ", ") "" testKVBSTree ==
    "key: 3, value: l, key: 4, value: c, key: 5, value: y, key: 6, "
    +++"value: a, key: 7, value: s, key: 8, value: q, key: 9, value: r, "
    +++"key: 10, value: p, key: 50, value: o, "
  , preOrder (\x s -> s +++ toString x) "" testIntBSTree == "1021426863"
  , postOrder (\x s -> s +++ toString x) "" testIntBSTree == "0286463211"
  , inOrder (\x s -> s +++ toString x) "" BSTree_emptyInt == ""
  , preOrder (\x s -> s +++ toString x) "" BSTree_emptyInt == ""
  , postOrder (\x s -> s +++ toString x) "" BSTree_emptyInt == ""
  ]
  
test_sortBSTree =
  [ sortBSTree BSTree_emptyInt == []
  , map (\(KV k v) -> v) (sortBSTree testKVBSTree) == ['l','c','y','a','s','q','r','p','o']
  , sortBSTree testIntBSTree == sort (sortBSTree testIntBSTree)
  , length (sortBSTree testIntBSTree) == 8
  ]
  
test_MapKV_update =
  [ MapKV_update (M BSTree_emptyKV) 4 (\_ -> Just 'a') === M BSTree_emptyKV
  , MapKV_update (M (Node (KV 5 'a') (Node (KV 3 's') Empty (Node (KV 4 'r') Empty Empty)) Empty)) 5 (\_ -> Just 't') ===
    M ((Node (KV 5 't') (Node (KV 3 's') Empty (Node (KV 4 'r') Empty Empty)) Empty))
  , MapKV_update (M (Node (KV 5 'a') (Node (KV 3 's') Empty (Node (KV 4 'r') Empty Empty)) Empty)) 5 (\_ -> Nothing) ===
    M ((Node (KV 5 'a') (Node (KV 3 's') Empty (Node (KV 4 'r') Empty Empty)) Empty))
  ]
  
test_MapKV_lookup =
  [ MapKV_lookup (M BSTree_emptyKV) 3 === Nothing
  , MapKV_lookup (M testKVBSTree) 7 === Just (KV 7 's')
  ]
  
test_MapKV_insert =
  [ foldl (\x (k,v) -> MapKV_insert x k v) (M BSTree_emptyKV)
    [(6,'a'),(4,'c'),(9,'r'),(5,'y'),(3,'l'),(7,'s'),(8,'q'),
    (10,'p'),(50,'o')] === M testKVBSTree
  , MapKV_insert (M BSTree_emptyKV) 4 'a' === M (Node (KV 4 'a') Empty Empty)
  , MapKV_insert (MapKV_insert (M BSTree_emptyKV) 4 'a') 4 'b' ===
    M (Node (KV 4 'a') Empty Empty)
  ]
	
Start = 
 (and (flatten allTests), allTests)
	where
		allTests =
			[test_BSTRe_Empty,
			 test_BSTree_insert,
			 test_BSTree_lookup,
			 test_BSTree_depth,
			 test_BSTree_isBalanced,
			 test_Traversable,
			 test_sortBSTree,
			 test_MapKV_update,
			 test_MapKV_lookup,
			 test_MapKV_insert
			]