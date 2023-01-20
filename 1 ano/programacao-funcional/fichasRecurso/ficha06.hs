--1)

data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show

arv :: (Num a) => BTree a
arv = Node 7 (Node 5 (Node 3 Empty Empty) (Node 2 Empty Empty))
             (Node 6 (Node 1 Empty (Node 8 Empty Empty)) Empty)

arv2 :: (Num a) => BTree a
arv2 = Node 14 (Node 2 (Node 9 Empty Empty) (Node 4 Empty Empty))
               (Node 24 (Node 14 Empty Empty) Empty)

arv3 :: (Num a) => BTree a
arv3 = Node 2 (Empty) (Node 4 (Empty) (Empty))

--a)
altura :: BTree a -> Int
altura Empty = 0
altura (Node _ x y) = 1 + max ( altura x ) (altura y) 

--b)
contaNodos :: BTree a -> Int
contaNodos Empty = 0
contaNodos (Node x ae ad) = 1 + contaNodos ae + contaNodos ad

--c)
folhas :: BTree a -> Int
folhas Empty = 0
folhas (Node x Empty Empty) = 1
folhas (Node x ae ad) = folhas ae + folhas ad

--d)
prune :: Int -> BTree a -> BTree a
prune _ (Empty) = Empty
prune 0 _ = Empty
prune x (Node c ae ad) = Node c (prune (x-1) ae) (prune (x-1) ad)

--e) False -> Esquerda || True -> direita
path :: [Bool] -> BTree a -> [a]
path (h:t) (Empty) = []
path [] (Node x ae ad) = [x]
path (h:t) (Node x ae ad) | h == False = x : path t ae
                          | h == True = x : path t ad

--f)
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node r ae ad) = Node r (mirror ad) (mirror ae)

--g)
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT f (Node x1 ae1 ad1) (Node x2 ae2 ad2) = let a = zipWithBT f ae1 ae2
                                                      b = zipWithBT f ad1 ad2
                                                  in (Node (x1 `f` x2) a b)
zipWithBT _ _ _ = Empty

--h)
unzipBT :: BTree (a,b,c) -> (BTree a,BTree b,BTree c)
unzipBT Empty = (Empty,Empty,Empty)
unzipBT (Node (r1,r2,r3) ae ad) = let (ae1,ae2,ae3) = unzipBT ae
                                      (ad1,ad2,ad3) = unzipBT ad
                                  in ((Node r1 ae1 ad1),(Node r2 ae2 ad2),(Node r3 ae3 ad3))

--------------------------------------------------------------------------------------------------------