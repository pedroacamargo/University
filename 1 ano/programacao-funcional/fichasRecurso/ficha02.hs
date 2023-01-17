import Data.Char
--------------------------------------------------------------------------------------------------
--1)
--a)
-- A funçao funA vai dar a soma dos quadrados da lista 4 + 9 + 25 + 1 = 39

--b)
-- A função funB vai dar a lista dos números pares. Então funB [8,5,12] = [8,12]

--c)
-- A função funC vai dar a lista com o último elemento caso length da lista seja impar. Caso seja par o resultado será []

--d)
-- A função funD dá a função reverse. funD "otrec" = "certo"

--------------------------------------------------------------------------------------------------
--2)
--a)
dobros :: [Float] -> [Float] 
dobros [] = []
dobros (h:t) = (h * 2) : dobros t

--b)
numOcorre :: Char -> String -> Int
numOcorre _ [] = 0
numOcorre c (h:t) | c == h = 1 + numOcorre c t
                  | otherwise = numOcorre c t

--c)
positivos :: [Int] -> Bool
positivos [] = True
positivos (h:t) = if h > 0 then positivos t else False

--d)
soPos :: [Int] -> [Int]
soPos [] = []
soPos (h:t) = if h <= 0 then soPos t else h : soPos t

--e)
somaNeg :: [Int] -> Int
somaNeg [] = 0
somaNeg (h:t) = if h < 0 then h + somaNeg t else somaNeg t

--f)
tresUlt :: [a] -> [a]
tresUlt (h:t) = if length (h:t) <= 3 then (h:t) else tresUlt t

--g)
segundos :: [(a,b)] -> [b]
segundos [] = []
segundos ((x,y):t) = y : segundos t

--h)
nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool
nosPrimeiros n [] = False
nosPrimeiros n ((x, y):t) | n == x = True
                          | otherwise = nosPrimeiros n t

--i)
sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos [] = (0,0,0)
sumTriplos ((n1,n2,n3):t) = (n1 + x,n2 + y,n3 + z)
                          where (x,y,z) = sumTriplos t

--------------------------------------------------------------------------------------------------
--3)
--a)
isDigit :: Char -> Bool
isDigit x = if ord(x) >= 48 && ord(x) <= 57 then True else False

soDigitos :: [Char] -> [Char]
soDigitos [] = []
soDigitos (h:t) = if Data.Char.isDigit h then h : soDigitos t else soDigitos t

--b)
isLower :: Char -> Bool
isLower x = if ord(x) >= 97 && ord(x) <= 122 then True else False

minusculas :: [Char] -> Int
minusculas [] = 0
minusculas (h:t) = if Data.Char.isLower h then 1 + minusculas t else minusculas t

--c)
nums :: String -> [Int]
nums [] = []
nums (h:t) = if elem h ['0'..'9'] then (ord h - ord '0') : nums t else nums t

--------------------------------------------------------------------------------------------------
--4)
type Polinomio = [Monomio]
type Monomio = (Float,Int)

polinomioExemplo :: Polinomio
polinomioExemplo = [(2,3), (3,4), (5,3), (4,5), (10,0)]
--a)
conta :: Int -> Polinomio -> Int
conta n [] = 0
conta n ((c,g):t) = if n == g then 1 + conta n t else conta n t

--b)
grau :: Polinomio -> Int
grau [] = 0
grau [(c,g)] = g
grau ((c,g):(c2,g2):t) = if g > g2 then grau ((c,g):t) else grau ((c2,g2):t)

--c)
selgrau :: Int -> Polinomio -> Polinomio
selgrau n [] = []
selgrau n ((c,g):t) = if n == g then (c,g) : selgrau n t else selgrau n t

--d)
deriv :: Polinomio -> Polinomio
deriv [] = []
deriv ((c,g):t) | g >= 1 = (c * (fromIntegral g), g - 1) : deriv t
                | otherwise = (0,0) : deriv t

--e)
calcula :: Float -> Polinomio -> Float
calcula x [] = 0
calcula x ((c,g):t) = (c * (x^2)) + calcula x t

--f)
simp :: Polinomio -> Polinomio
simp [] = []
simp ((c,g):t) = if c == 0 then simp t else (c,g) : simp t

--g)
mult :: Monomio -> Polinomio -> Polinomio
mult (c,g) [] = []
mult (c,g) ((c2,g2):t) = ((c * c2), g + g2) : mult (c,g) t

--h)
addMonomio :: Monomio -> Polinomio -> Polinomio
addMonomio m [] = [m]
addMonomio (c,g) ((c2,g2):t) | g == g2 = (c + c2,g) : t
                             | otherwise = (c2,g2) : addMonomio (c,g) t

normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza ((c,g):t) = addMonomio (c,g) (normaliza t)

--i)
soma :: Polinomio -> Polinomio -> Polinomio
soma p1 p2 = normaliza (p1 ++ p2)

--j)
produto :: Polinomio -> Polinomio -> Polinomio 
produto _ [] = []
produto [] _ = []
produto ((c,g):t) ((c2,g2):t2) = normaliza ((c * c2, g + g2) : produto t t2)

--k)
ordena :: Polinomio -> Polinomio
ordena [] = []
ordena ((c1,g1):t) = insertP (c1,g1) (ordena t)
                            where insertP :: Monomio -> Polinomio -> Polinomio
                                  insertP m [] = [m]
                                  insertP (c1,g1) ((c2,g2):t) = if g1 < g2 then (c1,g1) : ((c2,g2):t) else (c2,g2) : insertP (c1,g1) t

--l)
equiv :: Polinomio -> Polinomio -> Bool
equiv p1 p2 = ordena p1 == ordena p2