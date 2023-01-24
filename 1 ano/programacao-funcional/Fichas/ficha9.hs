import Control.Monad  
import Data.Char 
-- I CAN'T IMPORT THIS WTFFFFFFFFFF ---------
import System.Random
---------------------------------------------
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


main :: IO ()
main = do
  gen <- getStdGen
  let numbers = take 25 (randomRs (1, 75) gen)
  playBingo numbers

------------------------------------------------------------------------------------
--1)
--a)
bingo :: IO ()
bingo = do
    gen <- newStdGen
    let numbers = randomRs (1, 90) gen
    loop numbers []

loop :: [Int] -> [Int] -> IO ()
loop (n:ns) used = do
    if n `elem` used
        then loop ns used
    else do
        putStrLn (show n)
        hFlush stdout
        _ <- getLine
        loop ns (n:used)
loop _ _ = return ()