import Data.Char

-------------------------------------------------------------------------------------------------------------------------
--1)
--a) see the foldr definition at University/1 ano/programacao-funcional/haskell-functions/foldl.hs
digitAlpha :: String -> (String,String)
digitAlpha [] = ("","")
digitAlpha (h:t) | isAlpha h = (h:a,b)
                 | isDigit h = (a,h:b)
                 | otherwise = (a,b)
                 where (a,b) = digitAlpha t

digitAlpha' :: String -> (String,String)
digitAlpha' string = foldl (\(alpha,digit) s -> if isDigit s then (alpha,digit ++ [s]) else if isAlpha s then (alpha ++ [s], digit) else (alpha,digit)) ("","") string 

-------------------------------------------------------------------------------------------------------------------------

--2) dada uma lista de inteiros, conta o número de valores negativos, zeros e positivos, devolvendo um triplo com essa informação
nzp :: [Int] -> (Int,Int,Int)
nzp (h:t) | h < 0 = (x+1,y,z)
          | h == 0 = (x,h+1,z)
          | h > 0 = (x,y,h+1)
          | otherwise = (x,y,z)
          where (x,y,z) = nzp t

nzp' :: [Int] -> (Int,Int,Int)
nzp' (h:t) = foldl (\(x,y,z) s -> if s < 0 then (x+1,y,z) else if s == 0 then (x,y+1,z) else if s > 0 then (x,y,z+1) else (x,y,z)) (0,0,0) (h:t)

-------------------------------------------------------------------------------------------------------------------------
--3) divisão e o resto da divisão inteira por subtrções sucessivas
divMod' :: Integral a => a -> a -> (a, a) 
divMod' x y | x - y > 0 = (1 + a,b)
            | otherwise = (0,x)
           where (a,b) = divMod' (x-y) y

divMod'' :: Integral a => a -> a -> (a, a)
divMod'' x y = foldl (\(div',res) n -> (div'+1,res-y)) (0,x) [y,2*y..x]
-------------------------------------------------------------------------------------------------------------------------
--4)
fromDigits'' :: [Int] -> Int -> Int
fromDigits'' [] acc = acc
fromDigits'' (h:t) acc = fromDigits'' t (acc*10+h)

fromDigits' :: [Int] -> Int
fromDigits' l = aux 0 l 
                where aux :: Int -> [Int] -> Int
                      aux n [] = n
                      aux n (x:xs) = aux (n*10+x) xs

-------------------------------------------------------------------------------------------------------------------------
--5)
--maxSumInit'' :: (Num a, Ord a) => [a] -> a
--maxSumInit'' l = foldl (\ acc x -> max(sum x) acc) (sum l) (init l)

-------------------------------------------------------------------------------------------------------------------------
--6)
fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n-1) + fib (n-2)

fib' :: Int -> Int
fib' n = aux (0,1) n
         where aux :: (Int,Int) -> Int -> Int
               aux (a,b) 0 = a
               aux (a,b) 1 = b
               aux (a,b) x | x>1 = aux (b,a+b) (x-1)

-------------------------------------------------------------------------------------------------------------------------
--7)
intToStringAcc' :: Int -> String -> String
intToStringAcc' x acc
    | x < 0     = '-' : intToStringAcc' (abs x) acc
    | x == 0    = acc
    | otherwise = intToStringAcc' (x `div` 10) ((chr (x `mod` 10 + ord '0')) : acc)

-------------------------------------------------------------------------------------------------------------------------
--8)
--a) [x | x <- [1..20], mod x 2 == 0, mod x 3 == 0]
-- Pega no x que varia de 1 até 20 retirando apenas aqueles que têm modulo tanto de 2 como 3 ficando [6,12,18]  

--b)
-- [x | x <- [y | y <- [1..20], mod y 2 == 0], mod x 3 == 0]
-- Faz exatamente o mesmo que a alínea anterior logo fica [6,12,18]

--c)
-- [(x,y) | x <- [0..20], y <- [0..20], x+y == 30]
-- Vai retornar uma lista de pares tal que a soma dê 30. Ficando[(10,20),(11,19),(12,18),(13,17),...,(20,10)]

--d)
-- [sum [y | y <- [1..x], odd y] | x <- [1..10]]]
{- Neste caso y apenas pode tomar valores impares de x e acaba por formar uma lista com os seguintes 
valores [[1],[1],[1,3],[1,3],[1,3,5], [1,3,5],[1,3,5,7],[1,3,5,7],[1,3,5,7,9],[1,3,5,7,9]], por fim faz a soma dos valores
de cada lista ficando [1,1,4,4,9,9,16,16,25,25] -}

-------------------------------------------------------------------------------------------------------------------------
--2. Defina cada uma das listas seguintes por compreensão.

--(a) [1,2,4,8,16,32,64,128,256,512,1024]

--R.: Esta lista representa os valores de 2^0 ate 2^10.
exp2 = [2^x | x <- [0..10]]

--(b) [(1,5),(2,4),(3,3),(4,2),(5,1)]

--R.: Par de valores em que a soma dê 6.
sum6 = [(x,y) | x <- [1..10], y <- [1..10], x+y == 6]

--(c) [[1],[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5]]

--R.: Lista com listas de todos os valores menores que 6.
min6 = [[y | y <- [1..x]] | x <- [1..5]]
min6' = [[1..x] | x <- [1..5]]

--(d) [[1],[1,1],[1,1,1],[1,1,1,1],[1,1,1,1,1]]

--R.: Lista com listas de o valor 1 repetidos no máximo 5 vezes
list1 = [replicate x 1 | x <- [1..5]]

--(e) [1,2,6,24,120,720]

--R.: 720/120 = 6; 120/24 = 5; 24/6 = 4;...
prod = [product [y | y <- [1..x]] | x <-[1..6]]
