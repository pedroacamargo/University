--1)
data ExpInt = Const Int
            | Simetrico ExpInt
            | Mais ExpInt ExpInt
            | Menos ExpInt ExpInt
            | Mult ExpInt ExpInt

-- Folhas são inteiros e nodos são operadores



--a)
calcula :: ExpInt -> Int
calcula x = case x of 
        Const a -> a
        Simetrico s -> (-1) * (calcula s)
        Mais a b -> (calcula a) + (calcula b)
        Menos a b -> (calcula a) - (calcula b)
        Mult a b -> (calcula a) * (calcula b)

--b)
infixa :: ExpInt -> String
infixa x = case x of
       Const a -> show a
       Simetrico a -> "-(" ++ infixa a
       Mais a b -> "(" ++ (infixa a) ++ " + " ++ (infixa b)++ ")"
       Menos a b -> "(" ++ (infixa a) ++ " - " ++ (infixa b)++ ")"
       Mult a b -> "(" ++ (infixa a) ++ " * " ++ (infixa b)++ ")"

--c)
posfixa :: ExpInt -> String
posfixa x = case x of
        Const a -> show a
        Simetrico a -> posfixa a ++ "-"
        Mais k1 k2 -> posfixa k1 ++ " " ++ posfixa k2 ++ "+"
        Menos k1 k2 -> posfixa k1 ++ " " ++ posfixa k2 ++ "-"
        Mult k1 k2 -> posfixa k1 ++ " " ++ posfixa k2 ++ "*"

----------------------------------------------------------------------------------------------------------
--2)
data RTree a = R a [RTree a]
               deriving Show

{-
TRAVESSIAS
esq - pai - dir ===> infixa
esq - dir - pai ===> posfixa
pai - esq - dir ===> perfixa
-}

rt :: RTree Int
rt = R 7[ R 3 [ R 2 [], R 14 []],
          R 5 [],
          R 10 [ R 17 [R 44 [], R 6 []]]
        ]

--a)
soma :: Num a => RTree a -> a
soma (R v filhos) = v + sum (map soma filhos)

--b)
altura :: RTree a -> Int
altura (R v []) = 1
altura (R v filhos) = 1 + maximum (map altura filhos)

--c)
prune :: Int -> RTree a -> RTree a
prune 0 (R a filhos) = (R a [])
prune x (R a filhos) = (R a (map (prune (x-1)) filhos))

--d)
mirror :: RTree a -> RTree a
mirror (R a filhos) = (R a (map mirror (reverse filhos)))

--e)
postOrder :: RTree a -> [a]
postOrder (R a l) = concat (map postOrder l) ++ [a]

-------------------------------------------------------------------------------------------
--3)
data BTree a = Empty | Node a (BTree a) (BTree a)

data LTree a = Tip a | Fork (LTree a) (LTree a)

--a)
ltSum :: Num a => LTree a -> a
ltSum (Tip x) = x
ltSum (Fork x1 x2) = ltSum x1 + ltSum x2

--b)
listaLT :: Num a => LTree a -> [a]
listaLT (Tip a) = [a]
listaLT (Fork x1 x2) = listaLT x1 ++ listaLT x2

--c)
ltHeight :: LTree a -> Int
ltHeight (Tip x) = 1
ltHeight (Fork x1 x2) = 1 + max (ltHeight x1) (ltHeight x2)

-------------------------------------------------------------------------------------------
--4)
data FTree a b = Leaf b | No a (FTree a b) (FTree a b)
-- full tree informação nos nodos e nas folhas

--a)
splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf x) = (Empty, Tip x)
splitFTree' (No r ae ad) = (Node r bte btd , Fork lte ltd)
                           where (bte, lte) = splitFTree ae
                                 (btd, ltd) = splitFTree ad

--b)
joinTrees :: BTree a -> LTree b -> Maybe (FTree a b)
joinTrees (Empty) (Tip x) = Just (Leaf x)
joinTrees (Node r ae1 ad1) (Fork ae2 ad2) = Just (No r aux1 aux2)
                                            where Just aux1 = joinTrees ae1 ae2
                                                  Just aux2 = joinTrees ad1 ad2 
joinTrees _ _ = Nothing