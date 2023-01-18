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

--2) dada uma lista de inteiros, conta o número de valores negativos, zeros e positivos, devolvendo um triplo com essa informação
nzp :: [Int] -> (Int,Int,Int)
nzp (h:t) | h < 0 = (x+1,y,z)
          | h == 0 = (x,h+1,z)
          | h > 0 = (x,y,h+1)
          | otherwise = (x,y,z)
          where (x,y,z) = nzp t

nzp' :: [Int] -> (Int,Int,Int)
nzp' (h:t) = foldl (\(x,y,z) s -> if s < 0 then (x+1,y,z) else if s == 0 then (x,y+1,z) else if s > 0 then (x,y,z+1) else (x,y,z)) (0,0,0) (h:t)

--3)
