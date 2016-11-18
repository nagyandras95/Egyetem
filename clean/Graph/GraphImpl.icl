module GraphImpl

import StdEnv, StdLib, GenEq 

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
  add x = (White, [])
  
  addNeighbour :: EdgeList Vertex Weight -> EdgeList
  addNeighbour (c,e) n w = (c, sortBy wb [(n,w):e] )
  	where
  		wb:: (Vertex, Weight) (Vertex, Weight) -> Bool
  		wb (v1,_) (v2, _) = v1 < v2
  
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
  		adj [(Weight 0):ws] n = adj ws (n+1)
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
	iterate g [x:xs] l = iterate newGraph newVertexes (l ++ [x])
	where
		newVertexes = xs ++ (whiteNeighbours g x)
		newGraph = update g x (whiteNeighbours g x)
		where
			update:: (a b) Vertex [Vertex] -> (a b) | Graph a b
			update g v vs = updateAllGray (updateGraph g v (color (getNode g v) Black)) vs
			 
			where
				updateAllGray :: (a b) [Vertex] -> (a b) | Graph a b	
				updateAllGray g vs
					| vs == [] = g
					| otherwise = updateAllGray coloredGraph (tl vs)
				where
					coloredGraph = updateGraph g (hd vs) (color (getNode g (hd vs) ) Gray)	
			
	startGraph = updateGraph defaultGraph v (color (getNode defaultGraph v) Gray)
	where
		defaultGraph = resetGraph g
	

/*updateAllGrayT :: (a b) [Vertex] -> (a b) | Graph a b	
updateAllGrayT g vs
	| vs == [] = g
	| otherwise = updateAllGrayT coloredGraph (tl vs)
where
	coloredGraph = updateGraph g (hd vs) (color (getNode g (hd vs) ) Gray)*/

//converter

ToList :: {a} -> [a]
ToList array = [x \\ x<-:array]

FromList :: [a] -> {a}
FromList list = {x \\ x<-list}

//node tests

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

test_getColor =
  [ map fst listAdj === [White,Gray,Black,Gray,White,Black,White]
  , map fst listAdj === map fst listEdge
  ]

test_color =
  [ color adj Gray === (Gray, [Weight 0, Infinite])
  , color adj Black === (Black, [Weight 0, Infinite])
  , color (color adj Black) White === (White, [Weight 0, Infinite])
  , color edge Black === (Black, [(1, Weight 2)])
  , color (color edge Gray) Black === (Black, [(1, Weight 2)])
  ]
  where
    adj :: Adjacency
    adj = (White, [Weight 0, Infinite])

    edge :: EdgeList
    edge = (White, [(1, Weight 2)])

test_neighbours =
  [ map neighbours listAdj  === [[1],[0,3,6],[0],[1,4],[3],[2,4],[5]]
  , map neighbours listEdge === [[1],[0,3,6],[0],[1,4],[3],[2,4],[5]]
  ]
  
test_add =
  [ add (adj 0)  === (White, [Weight 0, Infinite])
  , add (edge 0) === edge 0
  , add (adj 2)  === (White, [Infinite, Infinite, Weight 0, Infinite])
  , add (edge 5) === edge 3
  ]
  where
    adj :: Int -> Adjacency
    adj x = newNode x

    edge :: Int -> EdgeList
    edge x = newNode x
  
test_addNeighbour =
  [ addNeighbour (adj 2) 1 (Weight 3) === (White, [Infinite, Weight 3, Weight 0])
  , addNeighbour (addNeighbour (adj 2) 1 (Weight 3)) 0 (Weight 5) === (White, [Weight 5, Weight 3, Weight 0])
  , addNeighbour (edge 2) 1 (Weight 3) === (White, [(1, Weight 3)])
  , addNeighbour (addNeighbour (addNeighbour (edge 3) 2 (Weight 3)) 0 (Weight 5)) 1 (Weight 6) === (White, [(0,Weight 5),(1, Weight 6), (2, Weight 3)])
  ]
  where
    adj :: Int -> Adjacency
    adj x = newNode x

    edge :: Int -> EdgeList
    edge x = newNode x
    
// graph tests
test_resetGraph =
  [ map getColor (resetGraph listAdj) === repeatn 7 White
  , map getColor (resetGraph listEdge) === repeatn 7 White
  , [getColor x \\ x <-: (resetGraph arrayAdj)] === repeatn 7 White
  , [getColor x \\ x <-: (resetGraph arrayEdge)] === repeatn 7 White
  ]

test_graphSize =
  [ graphSize listAdj == 7
  , graphSize arrayAdj == 7
  ]
  
test_getNode =
  [ getNode listAdj 1 === (Gray,[(Weight 1),(Weight 0),Infinite,(Weight 1),Infinite,Infinite,(Weight 1)])
  , map (getNode listAdj) [0..6] === map (getNode arrayAdj) [0..6]
  , getNode listEdge 3 === (Gray,[(1,(Weight 1)),(4,(Weight 1))])
  , map (getNode listEdge) [0..6] === map (getNode arrayEdge) [0..6]
  ]

test_addNode =
  [ getNode (addNode listAdj) (graphSize listAdj) === (White, [Infinite,Infinite,Infinite,Infinite,Infinite,Infinite,Infinite,Weight 0])
  , graphSize (addNode (addNode listEdge)) == 9
  , getNode (addNode (addNode arrayEdge)) (graphSize arrayEdge) === (White, [])
  ]
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

test_whiteNeighbours =
  [ whiteNeighbours listAdj 1 == [0,6]
  , whiteNeighbours listEdge 2 == [0]
  , map (whiteNeighbours listAdj) [0..6] == map (whiteNeighbours arrayAdj) [0..6]
  , map (whiteNeighbours listEdge) [0..6] == map (whiteNeighbours arrayEdge) [0..6]
  ]
  
test_addEdgeToGraph =
  [ neighbours (getNode (addEdgeToGraph listAdj 3 0 (Weight 5)) 3) == [0,1,4]
  , neighbours (getNode (addEdgeToGraph listEdge 3 0 (Weight 5)) 3) == [0,1,4]
  , neighbours (getNode (addEdgeToGraph arrayAdj 3 0 (Weight 5)) 3) == [0,1,4]
  , neighbours (getNode (addEdgeToGraph arrayEdge 3 0 (Weight 5)) 3) == [0,1,4]
  , getNode (addEdgeToGraph listAdj 4 0 (Weight 5)) 4 === (White,[(Weight 5),Infinite,Infinite,(Weight 1),(Weight 0),Infinite,Infinite])
  ]

test_bfs =
  [ bfs listEdge 0 == [0,1,3,6,4,5,2]
  , bfs listAdj 1 == [1,0,3,6,4,5,2]
  , bfs arrayEdge 6 == [6,5,2,4,0,3,1]
  , bfs arrayAdj 4 == [4,3,1,0,6,5,2]
  , bfs (addNode arrayAdj) 4 == [4,3,1,0,6,5,2]
  ]

generic gJSON a :: a -> String

gJSON{|OBJECT of o|} json (OBJECT x)  = "{\"type\":\"" +++ o.gtd_name +++ "\",\"value\":" +++ json x +++ "}"

gJSON{|PAIR|} jsonx jsony (PAIR x y)  = jsonx x +++ "," +++ jsony y

gJSON{|EITHER|} jsonl _     (LEFT x)  = jsonl x
gJSON{|EITHER|} _     jsonr (RIGHT x) = jsonr x

gJSON{|CONS of c|} json (CONS x)      = "{\"constructor\":\"" +++ c.gcd_name +++ "\",\"params\":[" +++ json x +++ "]}"

gJSON{|UNIT|} _
                       = ""
gJSON{|Int|}    x                     = "{\"type\":\"int\",\"value\":"      +++ toString x +++ "}"
gJSON{|Real|}   x                     = "{\"type\":\"real\",\"value\":"     +++ toString x +++ "}"
gJSON{|String|} x                     = "{\"type\":\"string\",\"value\":\"" +++ x          +++ "\"}"
gJSON{|Char|}   x                     = "{\"type\":\"char\",\"value\":\""   +++ toString x +++ "\"}"

gJSON{|Bool|}   True                  = "{\"type\":\"bool\",\"value\":true}"
gJSON{|Bool|}   False                 = "{\"type\":\"bool\",\"value\":false}"

derive gJSON [], (,), Color, Weight

toJSON :: a -> String | gJSON {|*|} a
toJSON x = gJSON {|*|} x

test_toJSON =
  [ toJSON [(White,[(Weight 0)])]
      ==
    "{\"type\":\"_List\",\"value\":{\"constructor\":\"_Cons\",\"params\":[{\"type\":"
    +++ "\"_Tuple2\",\"value\":{\"constructor\":\"_Tuple2\",\"params\":[{\"type\":\"Color\",\"value\":"
    +++ "{\"constructor\":\"White\",\"params\":[]}},{\"type\":\"_List\",\"value\":{\"constructor\":"
    +++ "\"_Cons\",\"params\":[{\"type\":\"Weight\",\"value\":{\"constructor\":\"Weight\",\"params\":"
    +++ "[{\"type\":\"int\",\"value\":0}]}},{\"type\":\"_List\",\"value\":{\"constructor\":"
    +++ "\"_Nil\",\"params\":[]}}]}}]}},{\"type\":\"_List\",\"value\":{\"constructor\":\"_Nil\",\"params\":[]}}]}}"
  , toJSON [(White,[(1,Weight 1)]), (White,[(0,Weight 1)])]
      ==
    "{\"type\":\"_List\",\"value\":{\"constructor\":\"_Cons\",\"params\":[{\"type\":"
    +++ "\"_Tuple2\",\"value\":{\"constructor\":\"_Tuple2\",\"params\":[{\"type\":\"Color\""
    +++ ",\"value\":{\"constructor\":\"White\",\"params\":[]}},{\"type\":\"_List\",\"value\":"
    +++ "{\"constructor\":\"_Cons\",\"params\":[{\"type\":\"_Tuple2\",\"value\":{\"constructor\":"
    +++ "\"_Tuple2\",\"params\":[{\"type\":\"int\",\"value\":1},{\"type\":\"Weight\",\"value\":"
    +++ "{\"constructor\":\"Weight\",\"params\":[{\"type\":\"int\",\"value\":1}]}}]}},{\"type\":"
    +++ "\"_List\",\"value\":{\"constructor\":\"_Nil\",\"params\":[]}}]}}]}},{\"type\":\"_List\","
    +++ "\"value\":{\"constructor\":\"_Cons\",\"params\":[{\"type\":\"_Tuple2\",\"value\":"
    +++ "{\"constructor\":\"_Tuple2\",\"params\":[{\"type\":\"Color\",\"value\":{\"constructor\":"
    +++ "\"White\",\"params\":[]}},{\"type\":\"_List\",\"value\":{\"constructor\":\"_Cons\",\"params\":"
    +++ "[{\"type\":\"_Tuple2\",\"value\":{\"constructor\":\"_Tuple2\",\"params\":[{\"type\":"
    +++ "\"int\",\"value\":0},{\"type\":\"Weight\",\"value\":{\"constructor\":\"Weight\",\"params\":"
    +++ "[{\"type\":\"int\",\"value\":1}]}}]}},{\"type\":\"_List\",\"value\":{\"constructor\":"
    +++ "\"_Nil\",\"params\":[]}}]}}]}},{\"type\":\"_List\",\"value\":{\"constructor\":\"_Nil\",\"params\":[]}}]}}]}}"
  ]

Start =
 (and (flatten allTests), allTests)
	where
		allTests =
			[ test_newNode,
			  test_getColor,
			  test_color,
			  test_neighbours,
			  test_add,
			  test_addNeighbour,
			  test_resetGraph,
			  test_graphSize,
			  test_getNode,
			  test_addNode,
			  test_updateGraph,
			  test_whiteNeighbours,
			  test_addEdgeToGraph,
			  test_bfs,
			  test_toJSON		  
			]