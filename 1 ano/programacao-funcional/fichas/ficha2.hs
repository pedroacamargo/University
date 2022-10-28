funA :: [Double] -> Double
funA [] = 0
funA (h:t) = h^2 + (funA t)

funB :: [Int] -> [Int]
funB [] = []
funB (h:t) = if (mod h 2)==0 then h : (funB t)
else (funB t)

-- Questão 2
-- a)
dobros :: [Float] -> [Float]
dobros (h:t) = h*2 : dobros t
dobros [] = []

-- b)
numOcorre :: Char -> String -> Int
numOcorre x [] = 0
numOcorre x (h:t) = if x == h then 1 + numOcorre x t
                    else numOcorre x t

-- c)
positivos :: [Int] -> Bool
positivos [x] = x > 0 
positivos (h:t) = if h > 0 then positivos t
                  else False

-- d)
soPos :: [Int] -> [Int]
soPos [x] = if x < 0 then [] else [x]
soPos (h:t) = if h > 0 then h : soPos t
              else soPos t

-- e)
somaNeg :: [Int] -> Int
somaNeg [x] = if x < 0 then x else 0
somaNeg (h:t) = if h < 0 then h + somaNeg t else somaNeg t

-- f)
tresUlt :: [a] -> [a]
tresUlt [] = []
tresUlt (h:t) = if length (h:t) <= 3 then (h:t) else tresUlt t

-- g)
segundos :: [(a,b)] -> [b]
segundos [] = []
segundos ((x,y):t) = y : segundos t

-- h)
nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool
nosPrimeiros a [] = False
nosPrimeiros a [(x,y)] = if a == x then True else False
nosPrimeiros a ((x,y):t) = if a == x then True else nosPrimeiros a t

-- i)
sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos [(a,b,c)] = (a,b,c)
sumTriplos ((a,b,c):t) = let (a',b',c') = sumTriplos t
                         in (a + a', b + b', c + c')

-- Questão 4

type Polinomio = [Monomio]
type Monomio = (Float, Int)

p :: Polinomio
p = [(2,3), (3,4), (5,3), (0,9), (4,5)]

-- a)
conta :: Int -> Polinomio -> Int
conta x [] = 0
conta n ((c,g):t) = if n == g then 1 + conta n t else conta n t

-- b)
grau :: Polinomio -> Int
grau [(c,e)] = e
grau ((c,e):t) = max e (grau t)

-- c)
selgrau :: Int -> Polinomio -> Polinomio
selgrau _ [] = []
selgrau x ((c,e):t) | x == e = (c,e) : selgrau x t
                    | otherwise = selgrau x t

-- d)
deriv :: Polinomio -> Polinomio
deriv ((c,e):t) = (c*(fromIntegral e), e - 1) : deriv t
deriv [] = []

-- e)
calcula :: Float -> Polinomio -> Float
calcula x ((c,e):t) = c * (x^e) + calcula x t
calcula x [] = 0

-- f)
simp :: Polinomio -> Polinomio
simp [] = []
simp ((c,e):t) | c == 0 = simp t
               | c /= 0 = (c,e) : simp t
               | otherwise = simp t 

-- g)
mult :: Monomio -> Polinomio -> Polinomio
mult (c,e) ((c2,e2):t) = (c*c2,e + e2) : mult (c,e) t
mult (c,e) [] = []

-- h)
addMonomio :: Monomio -> Polinomio -> Polinomio
addMonomio (c,e) [] = [(c,e)]
addMonomio (c,e) ((c2,e2):t) | e == e2 = (c + c2, e) : t
                             | otherwise = (c2,e2) : addMonomio (c,e) t

normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza (m:t) = let p' = normaliza t
                  in addMonomio m p'

-- i)
soma :: Polinomio -> Polinomio -> Polinomio
soma [(c,e)] [] = [(c,e)]
soma [] [] = []
soma ((c,e):t) ((c2,e2):t2) = let a = normaliza t
                                  b = normaliza t2
                              in if e == e2 then (c + c2,e) : soma a b
                                 else normaliza ((c,e):(c2,e2):soma a b)
-- soma ((c,e):t) ((c2,e2):t2) = if e == e2 then (c + c2,e) : soma t t2 
                              -- else normaliza ((c,e):(c2,e2):soma t t2)

-- j)
produto :: Polinomio -> Polinomio -> Polinomio
produto [] [] = []
produto _ [] = []
produto [] _ = []
produto ((c,e):t) ((c2,e2):t2) = (c * c2, e + e2) : produto t t2

-- k)
{-
ordena :: Polinomio -> Polinomio
ordena [] = []
ordena ((c,e):t) = if (e < min e t) then (c,e) : ordena t
                   else [(c,e)]
-}

-- l)
