--- This function (as the name says) will filter an element given a parameter as a function

filter' :: (a->Bool) -> [a] -> [a]
filter' _ [] = []
filter' p (h:t) | p h = h : filter' p t
                | otherwise = filter' p t

-- ex: filter (==2) [1,2,3,4,5,6,2] ------> > [2,2]