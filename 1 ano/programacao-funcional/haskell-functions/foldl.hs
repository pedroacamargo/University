-- Foldl will apply determined function into the whole list
-- foldl function accumulator list

foldl :: (b -> a -> b) -> b -> [a] -> b
foldl f acc []     =  acc
foldl f acc (x:xs) =  foldl f (f acc x) xs         -- = foldl f (acc `f` x) xs  

foldl (+) 0 [1, 2, 3]     -- is equivalent to ((0 + 1) + 2) + 3