import Data.List
import Data.Char
{-
        Functions:
        head
        tail
        last
        init 
        null (tells if a list is empty)
        reverse (reverse the direction of a list)
        length (length of a list)
        take x (take x firsts elements of a list)
        drop x (excludes x firsts elements of a list)
        maximum (maximum element of a list)
        minimum (minimum element of a list)
        sum (summates every element in a list)
        product (Multiplies every element in a list)
        elem -> if it contains an element or not (True or False)
    -}


-- enumFromTo 1 5 -> [1, 2, 3, 4, 5]


-- Questão 1
myenumFromTo :: Int -> Int -> [Int]
myenumFromTo x y | x >= y = x : []
                 | x < y = x : myenumFromTo (x+1) y
                 | otherwise = []

-- Questão 2
myenumFromThenTo :: Int -> Int -> Int -> [Int]
myenumFromThenTo x y z | x == z = x : []
                       | x < y && x < z = x : myenumFromThenTo y (y + (y - x)) z
                       | otherwise = []


-- Questão 3
(+++) :: [a] -> [a] -> [a]
(+++) (h:t) l =  h : (+++) t l
(+++) x [] = x
(+++) [] x = x

-- Questão 4
(!!!) :: [a] -> Int -> a
(!!!) (h:t) x | x == 0 = h 
              | x >= 1 = (!!!) t (x-1)

-- Questão 5 Dúvida -> O que é o ++ e o :
myreverse :: [a] -> [a]
myreverse (h:t) = (myreverse t) ++ [h]
myreverse [] = []

-- Questão 6
mytake :: Int -> [a] -> [a]
mytake x (h:t) | x == 0 = []
               | x >= 1 && x <= length t = h : mytake (x-1) t
               | otherwise = (h:t)

-- Questão 7
mydrop :: Int -> [a] -> [a]
mydrop n (h:t) | n == 0 = (h:t)
               | n >= 1 && n <= length t = mydrop (n-1) t
               | otherwise = (h:t)

-- Questão 8
myzip :: [a] -> [b] -> [(a, b)]
myzip (h:t) (h2:t2) = (h, h2) : myzip t t2
myzip _ _ = []

-- Questão 9
myreplicate :: Int -> a -> [a]
myreplicate 0 _ = []
myreplicate n x = if n > 0 then x : myreplicate (n-1) x else []

-- Questão 10
myintersperse :: a -> [a] -> [a]
myintersperse x (h:t) = h : [x] ++ myintersperse x t
myintersperse x _ = []

-- Questão 11
mygroup :: Eq a => [a] -> [[a]]
mygroup [] = []
mygroup [h] = [[h]]
mygroup (h:t) = let ((x:xs):y) = mygroup t
                in if h == x then (h:x:xs):y
                   else [h]:(x:xs):y

-- Questão 12
myconcat :: [[a]] -> [a]
myconcat [] = []
myconcat (h:t) = h ++ myconcat t

-- Questão 13
retiraUltimo :: [a] -> [a]
retiraUltimo [x] = []
retiraUltimo (h:t) = h : retiraUltimo t

myinits :: [a] -> [[a]]
myinits [] = [[]]
myinits l = myinits (retiraUltimo l) ++ [l]

-- Questão 14
mytails :: [a] -> [[a]]
mytails [] = [[]]
mytails (h:t) = [(h:t)] ++ mytails t

-- Questão 15
myheads :: [[a]] -> [a]
myheads [] = []
myheads ([]:t) = myheads t
myheads ((h:t):t2) = h : myheads t2

-- Questão 16
mytotal :: [[a]] -> Int
mytotal ((h:t):t2) = length (h:t) + mytotal t2
mytotal ([]:t) = mytotal t
mytotal [] = 0

-- Questão 17
myfun :: [(a,b,c)] -> [(a,c)]
myfun [] = []
myfun ((x,y,z):t) = (x,z) : myfun t

-- Questão 18
cola :: [(String,b,c)] -> String
cola [] = []
cola ((a,b,c):t) = a ++ cola t

-- Questão 19
idade :: Int -> Int -> [(String,Int)] -> [String]
idade _ _ [] = []
idade x y ((nome, ano):t) = if (x - ano) >= y then nome : idade x y t
                            else idade x y t

-- Questão 20
mypowerEnumFrom' :: Int -> Int -> [Int] 
mypowerEnumFrom' n m = if m >= 1 then mypowerEnumFrom' n (m-1) ++ [n^(m-1)]
                       else []


--mypowerEnumFrom :: Int -> Int -> Int -> [Int] 
--mypowerEnumFrom n m acc = if acc /= m then (n ^ acc) : mypowerEnumFrom n (m + 1)
--                    else [] 


-- Questão 21
isPrime :: Int -> Bool
isPrime 1 = False
isPrime x = if ePrimo x 2 == 0 then True
            else False

ePrimo :: Int -> Int -> Int
ePrimo x y | y >= x = 0
           | mod x y == 0 = 1
           | otherwise = ePrimo x (y+1)

-- Questão 22
myisPrefixOf :: Eq a => [a] -> [a] -> Bool
myisPrefixOf [] l = True
myisPrefixOf (h:t) (h2:t2) = if h == h2 then myisPrefixOf t t2
                             else False

-- Questão 23
myisSuffixOf :: Eq a => [a] -> [a] -> Bool
myisSuffixOf [] [] = True
myisSuffixOf l [] = False
myisSuffixOf [] l = False
myisSuffixOf (h:t) (h2:t2) = if h == h2 then myisSuffixOf t t2
                           else myisSuffixOf (h:t) t2

-- Questão 24
isSubsequenceOf' :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf' [] l = True
isSubsequenceOf' l []  = False
isSubsequenceOf' (x:xs) (h:t) = if x == h then isSubsequenceOf' xs t
                               else isSubsequenceOf' (x:xs) t

-- Questão 25
calculaPosicao :: Eq a => Int -> a -> [a] -> [Int]
calculaPosicao acc x (h:t) = if x == h then acc : calculaPosicao (acc+1) x t 
                             else calculaPosicao (acc+1) x t

myelemIndices :: Eq a => a -> [a] -> [Int]
myelemIndices x (h:t) = calculaPosicao 0 x (h:t) 

-- Questão 26
mynub :: Eq a => [a] -> [a]
mynub [] = []
mynub (h:t) = if pertence h t then mynub t
            else h : mynub t

pertence :: Eq a => a -> [a] -> Bool
pertence x [] = False
pertence x (h:t) = if x == h then True
                   else pertence x t

-- Questão 27
mydelete :: Eq a => a -> [a] -> [a]
mydelete x [] = []
mydelete x (h:t) = if x == h then t
                 else h : mydelete x t

-- Questão 28
(\\\) :: Eq a => [a] -> [a] -> [a]
(\\\) [] _ = []
(\\\) l [] = l
(\\\) (h:t) (h2:t2) = if h == h2 then (\\\) t t2
                      else h : (\\\) t (h2:t2)

-- Questão 29
myunion :: Eq a => [a] -> [a] -> [a]
myunion [] l = l
myunion l [] = l
myunion (h:t) (h2:t2) = if h2 == h then h : myunion t t2
                        else h : myunion t (h2:t2)

-- Questão 30
myintersect :: Eq a => [a] -> [a] -> [a]
myintersect [] [] = []
myintersect (h:t) [] = []
myintersect [] (h:t) = []
myintersect (h:t) (h2:t2) = if h2 /= h then myintersect t t2
                            else h : myintersect t t2

-- Questão 31
myinsert :: Ord a => a -> [a] -> [a]
myinsert x [] = [x]
myinsert x (h:t) = if x >= h then h : insert x t
                 else x : t

-- Questão 32
myunwords :: [String] -> String
myunwords [] = []
myunwords [x] = x
myunwords (h:t) = h ++ " " ++ myunwords t

-- Questão 33
myunlines :: [String] -> String
myunlines [] = []
myunlines [x] = x
myunlines (h:t) = h ++ "\n" ++ myunlines t

-- Questão 34
mypMaior :: Ord a => [a] -> Int
mypMaior (h:t) = checkIfHigher h t 0 1


checkIfHigher :: Ord a => a -> [a] -> Int -> Int -> Int
checkIfHigher _ [] acc _ = acc
checkIfHigher head (h:t) acc acc2 = if h > head then checkIfHigher h t acc2 (acc2+1)
                            else checkIfHigher head t acc (acc2+1)

-- Questão 35
mylookup :: Eq a => a -> [(a,b)] -> Maybe b
mylookup _ [] = Nothing
mylookup x ((a,b):t) = if x == a then Just b
                       else mylookup x t

-- Questão 36
mypreCrescente :: Ord a => [a] -> [a]
mypreCrescente [] = []
mypreCrescente [x] = [x]
mypreCrescente (h:h2:t) = if h <= h2 then h : mypreCrescente (h2:t)
                          else [h]

-- Questão 37
myiSort :: Ord a => [a] -> [a]
myiSort [] = []
myiSort (h:t) = myinsert2 h (myiSort t)


myinsert2 :: Ord a => a -> [a] -> [a]
myinsert2 x [] = [x]
myinsert2 x (h:t) = if x <= h then x:h:t
                       else h : myinsert2 x t

-- Questão 38
menor :: String -> String -> Bool
menor [] [] = True
menor l [] = False
menor [] l = True
menor (h:t) (h2:t2) | h < h2 = True
                    | h > h2 = False
                    | otherwise = menor t t2

-- Questão 39
myelemMSet :: Eq a => a -> [(a,Int)] -> Bool
myelemMSet x [] = False
myelemMSet x ((a,b):t) = if x == a then True
                         else myelemMSet x t

-- Questão 40
myconverteMSet :: [(a,Int)] -> [a]
myconverteMSet [] = []
myconverteMSet ((a,x):t) = if x >=1 then a : myconverteMSet ((a,x-1):t)
                           else myconverteMSet t

-- Questão 41
myinsereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
myinsereMSet _ [] = []
myinsereMSet c ((c2,x):t) = if c == c2 then ((c2,x+1):t)
                            else (c2,x) : myinsereMSet c t

-- Questão 42
myremoveMset :: Eq a => a -> [(a,Int)] -> [(a,Int)]
myremoveMset c [] = []
myremoveMset c ((c2,x):t) | c == c2 && x == 1 = t
                          | c == c2 = (c2,x-1):t
                          | otherwise = (c2,x) : myremoveMset c t

-- Questão 43 (SOU UMA MAAAAQUINA)
myconstroiMSet :: Ord a => [a] -> [(a,Int)]
myconstroiMSet [] = []
myconstroiMSet (h:h2:t) = myaux 1 (h:h2:t)

myaux :: Ord a => Int -> [a] -> [(a,Int)]
myaux acc [x] = [(x,acc)]
myaux acc (h1:h2:t) | h1 == h2 = myaux (acc+1) (h2:t)
                    | otherwise = (h1, acc) : myaux 1 (h2:t)

-- Questão 44 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
partitionEitherss :: [Either a b] -> ([a], [b])
partitionEitherss [] = ([],[])
partitionEitherss (h:t) = case h of 
        Left a -> (a:x , y)
        Right b -> (x , b:y )
    where (x,y) = partitionEitherss t

partitionEithers' :: [Either a b] -> ([a],[b])
partitionEithers' l = (left l, right l)
                      where left [] = []
                            left (Left x:xs) = x:left xs
                            left (Right x:xs) = left xs 
                            right [] = []
                            right(Left x:xs) = right xs
                            right (Right x:xs)= x: right xs

-- Questão 45
mycatMaybes :: [Maybe a] -> [a]
mycatMaybes [] = []
mycatMaybes (h:t) = case h of 
    Just a -> a : mycatMaybes t
    Nothing -> mycatMaybes t 

-- Questão 46
data Movimento = Norte | Sul | Este | Oeste
                deriving (Show,Eq)

caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (x1,y1) (x2,y2) | x1 > x2  = Oeste : caminho (x1,y1) (x2+1,y2)
                        | x1 < x2 = Este : caminho (x1,y1) (x2-1,y2)
                        | y1 > y2 = Norte : caminho (x1,y1) (x2, y2+1)
                        | y1 < y2 = Sul : caminho (x1,y1) (x2, y2-1)
                        | otherwise = []

-- Questão 47
myhasLoops :: (Int,Int) -> [Movimento] -> Bool
myhasLoops (x,y) (h:t) | auxxx (x,y) (h:t) 0 == 0 = True
                       | otherwise = False

auxxx :: (Int,Int) -> [Movimento] -> Int -> Int
auxxx (x,y) [] acc = 0
auxxx (x,y) (h:t) acc | h == Norte = 1 + auxxx (x,y) t (acc+1)
                      | h == Sul = (-1) + auxxx (x,y) t (acc-1)
                      | h == Este = 1 + auxxx (x,y) t (acc+1)
                      | h == Oeste = (-1) + auxxx (x,y) t (acc-1)
                      | otherwise = acc

-- Questão 48
type Ponto = (Float,Float)
data Rectangulo = Rect Ponto Ponto

contaQuadrados :: [Rectangulo] -> Int
contaQuadrados [] = 0
contaQuadrados ((Rect (x,y) (x2,y2)):t) = if abs(x-x2) == abs(y-y2) then 1 + contaQuadrados t else contaQuadrados t

-- Questão 49
areaTotal :: [Rectangulo] -> Float
areaTotal [] = 0
areaTotal ((Rect (x,y) (x2,y2)):t) = abs(x - x2) * abs(y - y2) + areaTotal t

-- Questão 50
data Equipamento = Bom | Razoavel | Avariado
                   deriving Show

naoReparar :: Eq Equipamento => [Equipamento] -> Int
naoReparar [] = 0
naoReparar (h:t) = if h == Avariado then naoReparar t else 1 + naoReparar t 