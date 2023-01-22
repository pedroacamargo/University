import Data.List
import Data.Char
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


-----------------------------------------------------------------------------------------------------------
--2)
data Exp a = Const a | Simetrico (Exp a) | Mais (Exp a) (Exp a) | Menos (Exp a) (Exp a) | Mult (Exp a) (Exp a)

calcula :: Num a => Exp a -> a
calcula (Const x) = x
calcula (Simetrico x) = - calcula x
calcula (Mais x y) = calcula x + calcula y
calcula (Menos x y) = calcula x - calcula y
calcula (Mult x y) = calcula x * calcula y


infixa :: Show a => Exp a -> String
infixa (Const x) = show x
infixa (Simetrico x) = '-' : '(' :  infixa x ++ ")"
infixa (Mais x y) = '(' : infixa x ++ " + " ++ infixa y ++ ")"
infixa (Menos x y) = '(' : infixa x ++ " - " ++ infixa y ++ ")"
infixa (Mult x y) = '(' : infixa x ++ " * " ++ infixa y ++ ")"
--a) instância show de Exp a

instance Show a => Show (Exp a) where
    show x = infixa x

--b)
instance (Num a, Eq a) => Eq (Exp a) where
    e1 == e2 = calcula e1 == calcula e2

--c)
instance Num a => Num (Exp a) where
    e1 + e2 = Const (calcula e1 + calcula e2)
    e1 - e2 = Const (calcula e1 - calcula e2)
    e1 * e2 = Const (calcula e1 * calcula e2)
    abs e = Const (abs (calcula e))
    negate e1 = Const (negate (calcula e1))
    signum e = Const (signum (calcula e))
    fromInteger n = Const (fromInteger n)

--------------------------------------------------------------------------------------------------------------
--3)
data Movimento = Credito Float | Debito Float
data Data = D Int Int Int
data Extracto = Ext Float [(Data, String, Movimento)]

--a)
instance Eq Data where
    (D a b c) == (D x y z) = True
    (D a b c) /= (D x y z) = False

instance Ord Data where
    (D a b c) `compare` (D x y z) 
        | (c,b,a) == (z,y,x) = EQ
        | (c,b,a) < (z,y,x) = LT
        | (c,b,a) > (z,y,x) = GT

--b)
instance Show Data where
    show (D d m a) = show d ++ "/" ++ show m ++ "/" ++ show a

--c) lista de movimentos apareça ordenada por ordem crescente de data
ordena :: Extracto -> Extracto
ordena (Ext vi l) = let lf = sortOn (\(d,_,_)->d) l
                    in (Ext vi lf)

--d)
saldo :: Extracto -> Float
saldo (Ext x l) = foldr (\(_,_,m) acc -> case m of Credito a -> a + acc
                                                   Debito a -> acc - a) x l


instance Show Extracto where
    show (Ext x l) = 
        "Saldo anterior: " ++ show x ++
                     "\n---------------------------------------" ++
                     "\nData       Descricao   Credito   Debito" ++
                     "\n---------------------------------------\n" ++ concatMap (\(d,s,m) ->  show d ++ replicate (11 - (length (show d))) ' ' ++ map (toUpper) s ++ "     \n") l ++
                     "\n Saldo Total: " ++ show (saldo (Ext x l))


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