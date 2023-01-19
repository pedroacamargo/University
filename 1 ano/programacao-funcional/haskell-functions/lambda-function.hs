-- The lambda function starts with a backslash () followed by one or more arguments, separated by whitespace. Then there is an arrow (->) 
-- which separates the arguments from the function body.
-- \x y -> x * y

-- You can use this lambda function just as you would any other function, by providing it with arguments:
-- (\x y -> x * y) 3 4    > This will return 12

{-
Lambda functions are often used in higher-order functions such as map, filter, and foldl,
which take a function as an argument and return a new value based on that function. 
For example, you can use a lambda function to filter a list of numbers to only include even numbers:

> filter (\x -> x `mod` 2 == 0) [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
> [2,4,6,8,10]
-}


Keep in mind that the lambda function passed to foldr must take two arguments, the `current` element of the list, and the `accumulator` value.
The lambda function must also return a new `accumulator` value that will be passed to the next element of the list.
-- In these cases, x = current element | acc = accumulator

foldr (\x acc -> x + acc) 0 [1, 2, 3, 4, 5]
-- This will return 15.

foldr (\x acc -> x ++ acc) [] [[1,2,3], [4,5,6], [7,8,9]]
-- This will return [1,2,3,4,5,6,7,8,9].