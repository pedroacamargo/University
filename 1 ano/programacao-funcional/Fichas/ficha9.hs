import Control.Monad  
import Data.Char 
import System.IO  

main1 = do  
    putStrLn "What's your first name?"  
    firstName <- getLine  
    putStrLn "What's your last name?"  
    lastName <- getLine  
    let bigFirstName = map toUpper firstName  
        bigLastName = map toUpper lastName  
    putStrLn $ "hey " ++ bigFirstName ++ " " ++ bigLastName ++ ", how are you?"  

-- This program looks like it should read a character and then check if it's a space. If it is, halt execution and if it isn't, print it to the terminal and then do the same thing all over again

main2 = do     
    c <- getChar  
    if c /= ' '  
        then do  
            putChar c  
            main2  
        else return () 

main3 = do  
    rs <- sequence [getLine, getLine, getLine]  
    print rs 

  
main4 = do   
    colors <- forM [1,2,3,4] (\a -> do  
        putStrLn $ "Which color do you associate with the number " ++ show a ++ "?"  
        color <- getLine  
        return color)  
    putStrLn "The colors that you associate with 1, 2, 3 and 4 are: "  
    mapM_ putStrLn colors  

{-
main :: IO ()
main = do
  gen <- getStdGen
  let numbers = take 25 (randomRs (1, 75) gen)
  playBingo numbers
-}
------------------------------------------------------------------------------------
--1)
--a)
{-
bingo :: IO()
bingo = do nl <- acumularNumeros []
           print nl

acumularNumeros :: [Int] -> IO [Int]
acumularNumeros l | length l == 90 = do return l
                  | otherwise = do v <- randomRIO (1,90)
                                   print v
                                   getChar
                                   let nl = if v `elem` l then l else v:l in acumularNumeros nl

--b)
mastermind :: IO ()
mastermind = do (n1,n2,n3,n4) <- getKey
                doGuess (n1,n2,n3,n4)
                return ()
                                

getKey :: IO (Int,Int,Int,Int)
getKey = do a <- randomRIO (0,9)
            b <- randomRIO (0,9)
            c <- randomRIO (0,9)
            d <- randomRIO (0,9)
            return (a,b,c,d)

getGuess :: IO (Int,Int,Int,Int)
getGuess = do x <- getLine
              if length x /= 4 || not $ all isDigit x
              then getGuess
              else return (let (a:b:c:d:resto) = x in (read [a],read [b],read [c],read [d]))

doGuess :: (Int,Int,Int,Int) -> IO ()
doGuess (n1,n2,n3,n4) = do
    let listaNums = [n1,n2,n3,n4]
    (g1,g2,g3,g4) <- getGuess
    let numsC = 0 + (if n1 == g1 then 1 else 0) + (if n2 == g2 then 1 else 0) + (if n3 == g3 then 1 else 0) + (if n4 == g4 then 1 else 0)
    let numsS = 0 + (if n1 /= g1 && g1 `elem` (listaNums \\ [g2,g3,g4]) then 1 else 0) + 
                    (if n2 /= g2 && g2 `elem` (listaNums \\ [g3,g4]) then 1 else 0) + 
                    (if n3 /= g3 && g3 `elem` (listaNums \\ [g4]) then 1 else 0) + 
                    (if n4 /= g4 && g4 `elem` (listaNums \\ []) then 1 else 0)
    if numsC == 4 then print "Ganhaste, parabens!" else print $ "Valores corretos: " ++ show numsC ++ "   Valores no sitio errado: " ++ show numsS
    if numsC == 4 then return () else doGuess (n1,n2,n3,n4)

-}

--------------------------------------------------------------------------------------------------------------------------------------------------------
--2)
data Aposta = Ap [Int] (Int,Int)

--a)
valida :: Aposta -> Bool
valida (Ap (a:b:c:d:e:[]) (f,g)) = and [x `elem` [1..50] | x <- [a,b,c,d,e]] && all (\x -> x `elem` [1..12]) [f,g]
valida _ = False

--b)
comuns :: Aposta -> Aposta -> (Int,Int)
comuns (Ap ap1@(a1:a2:a3:a4:a5:[]) (x1,y1)) (Ap ap2@(b1:b2:b3:b4:b5:[]) (x2,y2)) = (contanums,contaestrelas)
    where contanums = length [x | x <- ap1, x `elem` ap2]
          contaestrelas = length [y | y <- [x1,y1], y `elem` [x2,y2]] 

--c)
instance Eq Aposta where
    (==) a b = comuns a b == (5,2) 

premio :: Aposta -> Aposta -> Maybe Int
premio ap ch = case comuns ap ch of (5,n) -> Just (3 - n)
                                    (4,n) -> Just (6 - n)
                                    (3,n) -> Just (10 - n - (if n == 2 then 1 else 0))
                                    (2,2) -> Just 8
                                    (1,2) -> Just 11
                                    (2,n) -> Just (13 - n)
                                    _ -> Nothing

--d)
leAposta :: IO Aposta
leAposta = do
    print "Introduza os numeros (separados por um espaco):"
    nums <- getLine
    print "Introduza as estrelas (separadas por um espaco):"
    stars <- getLine
    let bet = Ap (map read (unspace nums)) (let (a:b:r) = unspace stars in (read a, read b))
    if valida bet then return bet else do print "Aposta invalida, tente novamente!"; leAposta

unspace :: String -> [String]
unspace str = map Text.unpack (Text.split (==' ') (Text.pack str))

joga :: Aposta -> IO ()
joga ch = do
    ap <- leAposta
    print ((++) "Premio: " $ show $ fromMaybe 0 (premio ap ch))

--e)
geraChave :: IO Aposta
geraChave = do
    nums <- generate 'N' []
    [star1,star2] <- generate 'S' []
    return (Ap nums (star1,star2))

generate :: Char -> [Int] -> IO [Int]
generate c l = do
    n <- randomRIO (1,if c == 'N' then 50 else 12)
    if length l == 5 && c == 'N' || length l == 2 && c == 'S' then return l 
    else if n `elem` l then generate c l else generate c (n:l)

--f)
main :: IO ()
main = do ch <- geraChave
          ciclo ch

ciclo :: Aposta -> IO ()
ciclo ch = do
    menuOpt <- menu
    case menuOpt of "1" -> do joga ch; ciclo ch
                    "2" -> do putStrLn "Nova chave gerada"; main
                    "0" -> return ()


menu :: IO String
menu = do putStrLn menutxt
          putStr "Opcao: "
          getLine
    where menutxt = unlines ["",
                             "Apostar ........... 1",
                             "Gerar nova chave .. 2",
                             "",
                             "Sair .............. 0"]


