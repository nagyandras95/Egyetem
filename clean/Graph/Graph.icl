module Graph

import StdEnv, StdLib, GenEq, StdArray 

:: Weight = Infinite | Weight Int

:: Color = White | Gray | Black

:: Vertex :== Int
:: EdgeList :== (Color, [(Vertex, Weight)])
:: Adjacency :== (Color, [Weight])

derive gEq Weight, Color


listAdj :: [] Adjacency
listAdj =
  [(White,[(Weight 0),(Weight 1),Infinite,Infinite,Infinite,Infinite,Infinite])
  ,(Gray,[(Weight 1),(Weight 0),Infinite,(Weight 1),Infinite,Infinite,(Weight 1)])
  ,(Black,[(Weight 1),Infinite,(Weight 0),Infinite,Infinite,Infinite,Infinite])
  ,(Gray,[Infinite,(Weight 1),Infinite,(Weight 0),(Weight 1),Infinite,Infinite])
  ,(White,[Infinite,Infinite,Infinite,(Weight 1),(Weight 0),Infinite,Infinite])
  ,(Black,[Infinite,Infinite,(Weight 1),Infinite,(Weight 1),(Weight 0),Infinite])
  ,(White,[Infinite,Infinite,Infinite,Infinite,Infinite,(Weight 1),(Weight 0)])
  ]
  
listEdge :: [] EdgeList
listEdge =
  [(White,[(1,(Weight 1))])
  ,(Gray,[(0,(Weight 1)),(3,(Weight 1)),(6,(Weight 1))])
  ,(Black,[(0,(Weight 1))])
  ,(Gray,[(1,(Weight 1)),(4,(Weight 1))])
  ,(White,[(3,(Weight 1))])
  ,(Black,[(2,(Weight 1)),(4,(Weight 1))])
  ,(White,[(5,(Weight 1))])
  ]

class Node t where
  newNode      :: Int -> t
  getColor     :: t -> Color
  color        :: t Color -> t
  neighbours   :: t -> [Vertex]
  add          :: t -> t
  addNeighbour :: t Vertex Weight -> t


instance Node EdgeList where
  newNode      :: Int -> EdgeList
  newNode _ = (White, [])
  
  getColor     :: EdgeList -> Color
  getColor (c,_) = c
  
  color        :: EdgeList Color -> EdgeList
  color (_, e) c = (c, e)
  
  neighbours   :: EdgeList -> [Vertex]
  neighbours (_, e) = map fst e
  
  add          :: EdgeList -> EdgeList
  add x = newNode 0
  
  addNeighbour :: EdgeList Vertex Weight -> EdgeList
  addNeighbour (c,e) n w = (c, [(n,w):e] )
  
instance Node Adjacency where
  newNode      :: Int -> Adjacency
  newNode n = (White, myNewNode n) where
  	myNewNode :: Int -> [Weight]
  	myNewNode 0 = [Weight 0]
  	myNewNode n = [Infinite : myNewNode (n-1)]
    
  getColor     :: Adjacency -> Color
  getColor (c,_) = c
  
  color        :: Adjacency Color -> Adjacency
  color (_, a) c = (c, a)
  
  neighbours   :: Adjacency -> [Vertex]
  neighbours (_, a) = adj a 0
  	where
  		adj :: [Weight] Int -> [Vertex]
  		adj [] _ = []
  		adj [Infinite:ws] n = adj ws (n+1)
  		adj [(Weight _):ws] n = [n : adj ws (n+1)]
  		
  add          :: Adjacency -> Adjacency
  add (c,a) = (c, a ++ [Infinite])
  
  addNeighbour :: Adjacency Vertex Weight -> Adjacency
  addNeighbour (c,a) v w = (c, myAddNeighbour v w a 0)
  	where
  		myAddNeighbour:: Vertex Weight [Weight] Int -> [Weight]
  		myAddNeighbour v w [o:ws] i
  			| i == v = [w:ws]
  			| otherwise = [o : myAddNeighbour v w ws (i+1)]

arrayAdj :: {} Adjacency
arrayAdj = { x \\ x <- listAdj }

arrayEdge :: {} EdgeList
arrayEdge = { x \\ x <- listEdge }

class Graph t1 t2 | Node t2 where
  resetGraph  :: (t1 t2) -> (t1 t2)
  graphSize   :: (t1 t2) -> Int
  getNode     :: (t1 t2) Vertex -> t2
  addNode     :: (t1 t2) -> (t1 t2)
  updateGraph :: (t1 t2) Vertex t2 -> (t1 t2)

instance Graph [] a | Node a where

  resetGraph g = map (\node -> color node White ) g
  
  graphSize g = length g
  
  getNode g n = g !! n
  
  //addNode :: [a] -> [a]
  addNode g = g ++ [(newNode (length g))]
  
  //updateGraph :: [a] Vertex a -> [a]
  updateGraph g v node = update g v node 0
  	where
  		update [g:gs] v node i
  			| i == v = [node:gs]
  			| otherwise = [g : update gs v node (i+1)]
  			


instance Graph {} a | Node a where

  resetGraph g = FromList (map (\node -> color node White ) (ToList g))
  
  graphSize g = length (ToList g)
  
  getNode g n = (ToList g) !! n
  
  addNode g = FromList (gl ++ [(newNode (length gl))])
  	where gl = ToList g
  
  updateGraph g v node = FromList (update (ToList g) v node 0)
  	where
  		update [g:gs] v node i
  			| i == v = [node:gs]
  			| otherwise = [g : update gs v node (i+1)]

whiteNeighbours :: (a b) Vertex -> [Vertex] | Graph a b
whiteNeighbours g v = [ x \\ x <- (neighbours (getNode g v)) |  getColor (getNode g x) === White ]


addEdgeToGraph :: (t1 t2) Vertex Vertex Weight -> (t1 t2) | Graph t1 t2
addEdgeToGraph g v1 v2 w = updateGraph g v1 newNode
	where
		forUpdate = getNode g v1
		newNode = addNeighbour forUpdate v2 w

bfs :: (a b) Int -> [Vertex] | Graph a b
bfs g v = iterate startGraph [v] [] 
where
	iterate :: (a b) [Vertex] [Vertex] -> [Vertex] | Graph a b
	iterate g [] vs = vs
	iterate g [x:xs] l = iterate (update g x (whiteNeighbours g x)) (whiteNeighbours g x ++ xs) [x:l]
	
	startGraph = updateGraph defaultGraph v (color (getNode defaultGraph v) Gray)
	where
		defaultGraph = resetGraph g
	
	update g v vs = updateAllGray (updateGraph g v (color (getNode g v) Black)) vs 
	where
		updateAllGray :: (a b) [Vertex] -> (a b) | Graph a b	
		updateAllGray g [] = g
		updateAllGrey g [v:vs] = updateAllGrey (updateGraph g (color (getNode v) Gray)) vs

test_newNode =
  [ adj 2  === (White, [Infinite, Infinite, Weight 0])
  , adj 0  === (White, [Weight 0])
  , edge 0 === (White, [])
  ]
  where
    adj :: Int -> Adjacency
    adj x = newNode x

    edge :: Int -> EdgeList
    edge x = newNode x

test_updateGraph =
  [ getNode (updateGraph listAdj 1 na) 1 === na
  , getNode (updateGraph listEdge 1 ne) 1 === ne
  , getNode (updateGraph arrayAdj 1 na) 1 === na
  , getNode (updateGraph arrayEdge 1 ne) 1 === ne
  ]
  where
    ne :: EdgeList
    ne = (White, [])

    na :: Adjacency
    na = (Gray,[(Weight 1),(Weight 0),Infinite,(Weight 1),(Weight 2),Infinite,(Weight 1)])

ToList :: {a} -> [a]
ToList array = [x \\ x<-:array]

FromList :: [a] -> {a}
FromList list = {x \\ x<-list}

Start = test_updateGraph /*test_newNode*/