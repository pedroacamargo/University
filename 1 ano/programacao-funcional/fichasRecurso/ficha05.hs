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
p1 = [(2,3), (3,4), (5,3), (4,5),(0,10)] 
--a)
selgrau :: Int -> Polinomio -> Polinomio
selgrau x ((c,g):t) = filter (\n -> x == snd n) ((c,g):t)

--b) conta n p -> quantos monomios de grau n existem em p
conta :: Int -> Polinomio -> Int
conta x poli = foldr (\n conta -> if x == snd n then conta + 1 else conta) 0 poli

conta' :: Int -> Polinomio -> Int
conta' x p = length (filter (\v -> x == snd v) p)

--c)(n é o valor atual e g é o acumulador)
grau :: Polinomio -> Int
grau p = foldr (\n g -> if snd n > g then snd (n) else g) 0 p

--d) Essa função irá aplicar a derivada em todos elementos do polinomio, caso o grau seja menor do que 0, a função map retorna (0,0) no lugar desse elemento. Então, com o filter, iremos tirar os (0,0) da lista como resultado.
deriv :: Polinomio -> Polinomio 
deriv p = let l = map (\(x,y) -> if y > 0 then (x*fromIntegral(y),y-1) else (0,0)) p
          in filter (/= (0,0)) l

--e) (c,g) são os monómios, caso o grau seja > 0, então fazemos a derivada, se não, retornamos o acumulador e passamos para o próximo elemento da lista. 0 == acumulador inicial e iremos aplicar o foldr no polinomio dado no input da função
calcula :: Float -> Polinomio -> Float
calcula x pol = foldr (\(c,g) acc -> if g > 0 then (c * (x^g) + acc) else acc) 0 pol

--f)
simp :: Polinomio -> Polinomio
simp pol = filter (\x -> fst(x) /= 0) pol

--g)
mult :: Monomio -> Polinomio -> Polinomio
mult (c,g) pol = map (\(c2,g2) -> ((c*c2),g+g2)) pol

--h)
ordena :: Polinomio -> Polinomio
ordena pol = foldr aux [] pol
             where aux :: Monomio -> Polinomio -> Polinomio
                   aux (cm,gm) [] = [(cm,gm)]
                   aux (cm,gm) ((cm2,gm2):t) = if gm < gm2 then (cm,gm): (cm2,gm2): t else (cm2,gm2): aux (cm,gm) t

ordena' :: Polinomio -> Polinomio
ordena' pol = sortOn' snd pol

---- On work -----

--i)
normaliza :: Polinomio -> Polinomio
normaliza l = let x = fromIntegral (grau l) in filter (\a -> x /= snd a) l

--k)
produto :: Polinomio -> Polinomio -> Polinomio
produto pol1 pol2 = foldr mult pol1 pol2