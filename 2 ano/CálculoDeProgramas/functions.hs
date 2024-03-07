uncurry :: (a -> b -> c) -> (a, b) -> c
uncurry f (x,y) = f x y

curry :: ((a,b) -> c) -> a -> b -> c
curry f x y = f (x,y)

flip :: (a -> b -> c) -> b -> a -> c
flip f x1 x2 = f x2 x1

-- Useless function
id :: a -> a
id x = x

length :: [a] -> Int
length [] = 0
length (_:xs) = 1 + length xs

reverse :: [a] -> [a]
reverse [] = []
reverse (x:xs) = reverse xs ++ [x]
