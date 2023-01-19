--1)
--a)
any' :: (a -> Bool) -> [a] -> Bool
any' f [] = False
any' f (h:t) = if f h == True then True else any' f t 

--b)
zipWith' :: (a->b->c) -> [a] -> [b] -> [c]
zipWith' f (h:t) (x:xs) = (h `f` x) : zipWith' f t xs
zipWith' f _ _ = []

--c)
takeWhile' :: (a->Bool) -> [a] -> [a]
takeWhile' f [] = []
takeWhile' f (h:t) = if f h then h : takeWhile' f t else []

--d)
dropWhile' :: (a->Bool) -> [a] -> [a] 
dropWhile' f [] = []
dropWhile' f (h:t) = if f h then dropWhile' f t else (h:t)

--e)
span' :: (a-> Bool) -> [a] -> ([a],[a])
span' f (h:t) | f h == True = (h:a,b)
             | f h == False = ([],(h:t))
             where (a,b) = span' f t

--f)
deleteBy' :: (a -> a -> Bool) -> a -> [a] -> [a]
deleteBy' f _ [] = []
deleteBy' f n (x:xs) = if f n x then xs else x:deleteBy' f n xs

--g)
sortOn' :: Ord b => (a -> b) -> [a] -> [a]
sortOn' f [] = []
sortOn' f (h:t) = aux f h (sortOn' f t)
                  where aux :: Ord b => (a -> b) -> a -> [a] -> [a]
                        aux f x [] = [x]
                        aux f x (a:b) = if f x > f a then a : aux f x b else x : a : b

----------------------------------------------------------------------------------------------------------------------------------------
--2)
type Polinomio = [Monomio]
type Monomio = (Float,Int)
p1 :: Polinomio
p1 = [(2,3), (3,4), (5,3), (4,5)] 
--a)
selgrau :: Int -> Polinomio -> Polinomio
selgrau x ((c,g):t) = filter (\n -> x == snd n) ((c,g):t)

--b) conta n p -> quantos monomios de grau n existem em p
conta :: Int -> Polinomio -> Int
conta x poli = foldr (\n conta -> if x == snd n then conta + 1 else conta) 0 poli

conta' :: Int -> Polinomio -> Int
conta' x p = length (filter (\v -> x == snd v) p)

--c) indica o grau do polinomio (n é o valor atual e g é o acumulador)
grau :: Polinomio -> Int
grau p = foldr (\n g -> if snd n > g then snd (n) else g) 0 p