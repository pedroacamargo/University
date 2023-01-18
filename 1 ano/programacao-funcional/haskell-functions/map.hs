-- map :: (a -> b) -> [a] -> [b]


{-

-> Whenever we want to apply a function on each element of a given list and produce a new list consisting of the updated elements, then we make use of a function called map() function in Haskell.

-> The map() function takes two parameters namely a list and the function to be applied on each element in the list and returns a new list as the output.

-> The map() function is available in Data.Map module in Haskell programming language.

-> The internal implementation of map is a balanced binary tree and this is a very efficient representation in Haskell programming language when compared to the other implementations such as Hash table.

-}



-- defining a main function in which we are using the map function on a list to add 2 to each element in the list and display the resulting new list as the output on the screen

main  = do
let new = map (+2) [10, 20, 30, 40, 50] putStrLn "The elements in the new list after using map function is:\n"
print $ new

-- -> [12, 22, 32, 42, 52]

---------------------------------------------------------------------------------------------------------------------------------------

-- The syntax (\x -> ) means define a function that takes one parameter and we will call it x, then we define a body for the function.
-- This is a way to define a function in line and without giving it a name.

map (\x -> x - avg) [0.0,2.0,3.4,5.6] -- simple example to return the average of a given list


-- In this case, the map is used to return an email, inside a list of different parameters. (Email, TLM, Name, ....)
-- You can use the sintax (\x ->) with the 'case x of' to give you different parameters of a list.
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails nome [(nom, cont)] = if nome == nom then Just (map (\x -> case x of Email e -> e) cont) else Nothing
verEmails nome ((nom,cont): agenda) = if nome == nom then verEmails nome [(nom,cont)] else verEmails nome agenda