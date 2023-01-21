--1)
data Frac = F Integer Integer
--a)
mdc :: Integer -> Integer -> Integer
mdc x y | x == y = x
        | x > y = mdc (x-y) y
        | x < y = mdc x (y-x)

normaliza :: Frac -> Frac
normaliza (F 0 x) = F 0 1
normaliza (F x y) = let md = mdc (abs x) (abs y)
                        sinal = if x * y > 0 then 1 else (-1)
                    in  F (sinal * (div (abs x) md)) (div (abs y) md)

--b)
instance Eq Frac where
    (F x y) == (F a b) | x*b == a*y = True
    (F x y) /= (F a b) = False

--c)
instance Ord Frac where
    (F x y) `compare` (F a b) 
        | x*b < y*a = LT 
        | x*b > y*a = GT
        | otherwise = EQ


--d)
instance Show Frac where
    show (F a 1) = show a
    show (F a b) = show a ++ "/" ++ show b

--e)
instance Num Frac where
    (F x y) + (F a b) = normaliza (F ((x*b) + (y * a)) (y * b))
    (F x y) - (F a b) = normaliza (F ((x*b) - (y * a)) (y * b))
    (F x y) * (F a b) = normaliza (F (x*a) (y*b))
    negate (F x y) = (F (-x) y)
    abs (F x y) = (F (abs x) (abs y))
    signum (F n1 n2) | n1 == 0 = F 0 1
                     | n1*n2 > 0 = F 1 1
                     | n1*n2 < 0 = F (-1) 1
    fromInteger n1 = F n1 1

--f)
isGreaterThanDouble :: Frac -> [Frac] -> [Frac]
isGreaterThanDouble (F x y) [] = []
isGreaterThanDouble f l = filter (\x -> x > 2*f) l






















--Teste2022-2023.hs


data Lista a = Esq a (Lista a) | Dir (Lista a) a | Nula 

arv ::(Num a) => Lista a
arv = (Esq 1 (Dir (Dir (Esq 9 Nula) 3) 4))

instance Show a => Show (Lista a) where
    show (Esq x Nula) = show x
    show (Esq x l) = show x ++ "," ++ show l
    show (Dir Nula x) = show x
    show (Dir l x) = show l ++ "," ++ show x
    show (Nula) = ""

showArv :: Show a => Lista a -> String
showArv a = "[" ++ show a ++ "]"