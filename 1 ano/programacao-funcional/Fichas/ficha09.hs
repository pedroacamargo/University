import Control.Monad  
import Data.Char 
import System.Random -- I CAN'T IMPORT THIS WTFFFFFFFFFF
  
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

playBingo :: [Int] -> IO ()
playBingo numbers = do
  putStrLn "Welcome to the bingo game!"
  putStrLn "The numbers are:"
  print numbers
  putStrLn "Pick a number between 1 and 75"
  number <- readLn
  if number `elem` numbers
    then do
      putStrLn "You got a match! The number is in the list"
      playBingo (filter (/= number) numbers)
    else do
      putStrLn "Sorry, the number is not in the list"
      playBingo numbers
