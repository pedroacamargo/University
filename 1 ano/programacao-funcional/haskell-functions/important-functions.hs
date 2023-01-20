{-

• length l: o número de elementos da lista l
• head l: a cabeça da lista (não vazia) l
• tail l: a cauda da lista (não vazia) l
• last l: o último elemento da lista (não vazia) l
• sqrt x: a raiz quadrada de x
• div x y: a divisãoo inteira de x por y
• mod x y: o resto da divisão inteira de x por y
    fst -> couple first element  ----> given (x,y) || fst (x,y) = x
    snd -> couple second element ----> given (x,y) || snd (x,y) = y

max -> The max value between 2 parameters
init -> Remove the last element of a list
all -> Returns true if every element in the list fulfill the condition
dropWhile -> deletes the elements that don't fulfill the condition until the element that fulfill
takeWhile -> gives the elements that don't fulfill the condition until the element that fulfull
sortOn -> sortOn :: Ord b => (a -> b) -> [a] -> [a]
          sortOn length ["hello", "world", "hi", "goodbye"]
          > ["hi","world","hello","goodbye"]


zipWith -> zip 2 lists in a list given a certain condition
filter                  ]
foldr, foldl, foldl'    ] ----> Already explained in another files
map                     ]


-}


-- ex para entender as listas
type Polinomio = [Monomio]
type Monomio = (Float,Int)
p1 :: Polinomio
p1 = [(2,3), (3,4), (5,3), (4,5),(0,10)] 

selgrau :: Int -> Polinomio -> Polinomio
selgrau n ps = filter (\x -> snd x == n) ps 

normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza ((b,e):ps) = [(sum [bs | (bs,es) <- selgrau e ps],e)]