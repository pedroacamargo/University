-- 1)

any' :: (a -> Bool) -> [a] -> Bool
any' _ [] = False
any' p (h:t) = if p h then True
              else any' p t

zipWith' :: (a->b->c) -> [a] -> [b] -> [c]
zipWith' _ [] l = []
zipWith' _ l [] = []
zipWith' f (h:t) (x:xs) = (f h x) : zipWith' f t xs

takeWhile' :: (a->Bool) -> [a] -> [a]
takeWhile' p [] = []
takeWhile' p (h:t) | p h = h : takeWhile' p t
                   | otherwise = []

dropWhile' :: (a->Bool) -> [a] -> [a]
dropWhile' p [] = []
dropWhile' p (h:t) | p h = dropWhile' p t
                   | otherwise = (h:t)

span' :: (a-> Bool) -> [a] -> ([a],[a])
span' p l = (takeWhile p l, dropWhile' p l)

spanE :: (a-> Bool) -> [a] -> ([a],[a])
spanE _ [] = ([],[])
spanE p (h:t) = 
    if p h then (h:lt,ld)
    else ([],(h:t))
    where (lt,ld) = spanE p t

deleteBy' :: (a -> a -> Bool) -> a -> [a] -> [a] 
deleteBy' f x (h:t) = if f x h then t
                      else h:deleteBy' f x t

----------------- ANOTAÇÕES -----------------
map' :: (a->b) -> [a] -> [b]
map' f [] = []
map' f (h:t) = f h : map f t

filter' :: (a->Bool) -> [a] -> [a]
filter' _ [] = []
filter' p (h:t) | p h = h : filter' p t
                | otherwise = filter' p t

-- 2)
type Polinomio = [Monomio]
type Monomio = (Float,Int)

p :: Polinomio
p = [(2,3),(3,4),(5,3),(4,5)]

selGrau :: Int -> Polinomio -> Polinomio
selGrau n [] = []
selGrau n ((c,e):t) | e == n = (c,e) : selGrau n t
                    | otherwise = selGrau n t

selGrau' :: Int -> Polinomio -> Polinomio
selGrau' n p = filter f p
    where f (c,e) = e == n

selGrau'' :: Int -> Polinomio -> Polinomio
selGrau'' n p = filter (\ (c,e) -> e == n) p


conta :: Int -> Polinomio -> Int
conta n p = length (selGrau'' n p)

grau :: Polinomio -> Int
grau p = foldr f 0 p
    where f (c,e) r = max e r
