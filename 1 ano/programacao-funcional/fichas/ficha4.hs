import Data.Char

-- Questão 1
digitAlpha :: String -> (String,String)
digitAlpha [] = ("","")
digitAlpha (h:t) | isDigit h = (ls, h:ds)
                 | isAlpha h = (h:ls, ds)
                 | otherwise = (ls, ds)
                 where (ls, ds) = digitAlpha t

-- Questão 2

nzp :: [Int] -> (Int,Int,Int)
nzp (h:t) | h == 0 = (n1,n2 + 1,n3)
          | h > 0 = (n1 + 1,n2,n3)
          | h < 0 = (n1,n2,n3 + 1)
          | otherwise = (n1,n2,n3)
          where (n1,n2,n3) = nzp t

nzp' :: [Int] -> (Int,Int,Int)
nzp' l = nzpAc (0,0,0) l
    where nzpAc ac [] = ac
          nzpAc (nn,nz,np) (h:t)
                | h > 0 = nzpAc (nn,nz,np + 1) t
                | h < 0 = nzpAc (nn + 1,nz,np) t
                | h == 0 = nzpAc (nn,nz + 1,np) t

-- Questão 3
mydivMod :: Integral a => a -> a -> (a,a)
mydivMod x y | x <= y = (q,(y-x)+l)
             | x > y = (q + 1,l)
             | otherwise = (q,l)
           where (q,l) = mydivMod (x-y) y

{-

mydivMod'' :: Integral a => a -> a -> (a,a)
mydivMod'' x y = mydivModAc'' x y (0,0)
            where mydivModAc'' 0 y acc = acc
                  mydivModAc'' x y (quotient,rest)
                  | x <= y = (quotient,(y-x)+rest) 
                  | x > y = mydivMod'' (x-y) y (1 + quotient,rest)
                  | otherwise = (quotient,rest)
-}

-- Questão 4
fromDigits :: [Int] -> Int
fromDigits [] = 0
fromDigits (h:t) = h * 10 ^ (length t) + fromDigits t

fromDigitsAc :: [Int] -> Int
fromDigitsAc l = fromDigitsAc' 0 l
                where fromDigitsAc' ac [] = ac
                      fromDigitsAc' ac (x:xs) = fromDigitsAc' (x+10*ac) xs

-- Questão 9
-- a) [2^x | x <- [0..10]]
-- b) [(x,y) | x <- [1..5], y <- [1..5], x + y = 6]
-- c) [[y | y <- [1..x]| x <- [1..5]]