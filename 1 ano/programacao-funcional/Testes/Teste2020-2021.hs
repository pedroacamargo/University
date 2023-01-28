--1
barra :: Eq a => [a] -> [a] -> [a]
barra l [] = l
barra [] _ = []
barra (x:xs) (h:t) = barra (delete' (x:xs) h) t 

delete' :: Eq a => [a] -> a -> [a]
delete' [] _ = [] 
delete' (x:xs) n = if x == n then xs 
                   else x : delete' xs n 
--2)
type MSet a = [(a,Int)]

--a)
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet n ((a,1):t) = if n == a then t
                         else (a,1) : removeMSet n t 
removeMSet n ((a,b):t) = if n == a then (a,b-1):t
                         else (a,b) : removeMSet n t

--b)

calcula :: MSet a -> ([a],Int)
calcula (h:t) = foldl (\(acc1,acc2) (x,y) -> (x : acc1,y + acc2) ) ([],0) (h:t)

--4)
data BTree a = Empty | Node a (BTree a) (BTree a)

remove :: Ord a => a -> BTree a -> BTree a 
remove _ Empty = Empty 
remove n (Node r e d) | n > r = Node r e (remove n d)   
                      | n < r = Node r (remove n e) d 
                      | otherwise = Empty