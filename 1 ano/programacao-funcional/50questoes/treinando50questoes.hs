{-# OPTIONS_GHC -Wno-overlapping-patterns #-}
group' :: Eq a => [a] -> [[a]]
group' (h:t) = myTakeWhile h (h:t) : group' (myDropWhile h (h:t))

myTakeWhile :: Eq a => a -> [a] -> [a]
myTakeWhile _ [] = []
myTakeWhile x (h:t) = if x == h then h : myTakeWhile x t else h:t

myDropWhile :: Eq a => a -> [a] -> [a]
myDropWhile _ [] = []
myDropWhile x (h:t) = if x == h then h:t else myDropWhile x t


data Equipamento = Bom | Razoavel | Avariado deriving Show

naoReparar :: [Equipamento] -> Int
naoReparar (h:t) = case h of
    Avariado ->  a
    otherwise -> 1 + a
    where a = naoReparar t


delete :: Eq a => a -> [a] -> [a]
delete x [] = []
delete x (h:t) = if x == h then t else h : delete x t

data Movimento = Norte | Sul | Este | Oeste deriving Show

hasLoops' :: (Int,Int) -> [Movimento] -> Bool
hasLoops' (x,y) l = if length l == 0 && (x,y) == (0,0) then True else False
hasLoops' (x,y) (h:t) = case h of 
                    Norte -> hasLoops' (x,y + 1) t
                    Sul -> hasLoops' (x,y - 1) t
                    Este -> hasLoops' (x + 1,y) t
                    Oeste -> hasLoops' (x - 1,y) t

enumFromThenTo' :: Int -> Int -> Int -> [Int] 
enumFromThenTo' x y z = if y < z then x : enumFromThenTo' (x+(y-x)) ((y-x)+y) z else []