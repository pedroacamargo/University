--1. Considere o tipo MSet a para representar multi-conjuntos de tipo a

type MSet a = [(a,Int)]

{- Considere ainda que nestas listas não há pares cuja primeira componente coincida, nem cuja segunda
componente seja menor ou igual a zero. Para além disso, os multi-conjuntos estão organizados
por ordem decrescente da muiltplicidade. O multi-conjunto {’b’,’a’,’c’,’b’,’b’,’a’,’b’} é
representado pela lista [(’b’,4),(’a’,2),(’c’,1)], por exemplo. -}

{-(a) Defina a função cardMSet :: MSet a -> Int que calcula a cardinalidade de um multiconjunto. 
Por exemplo, cardMSet [(’b’,4),(’a’,2),(’c’,1)] devolve 7. -}

cardMSet :: MSet a -> Int
cardMSet [] = 0
cardMSet ((c,n):t) = n + cardMSet t

{- (b) Defina a função moda :: MSet a -> [a] que devolve a lista dos elementos com maior número
de ocorrências. -}

moda :: MSet a -> [a]
moda = fst .foldr (\(a,num) (acc,maior) -> if num >= maior then (if num > maior then [a] else a : acc ,num) else (acc,maior) ) ([],0)

{- (c) Defina a função converteMSet :: MSet a -> [a] que converte um multi-conjunto numa
lista. Por exemplo, converteMSet [(’b’,4),(’a’,2),(’c’,1)] devolve ‘‘bbbbaac’’. -}

converteMSet :: MSet a -> [a]
converteMSet [] = []
converteMSet ((a,num):t) | num == 0 = converteMSet t
                         | num > 0 = a : converteMSet ((a, num-1):t)

{- (d) Defina a função addNcopies :: Eq a => MSet a -> a -> Int -> MSet a que faz a inserção
de um dado número de ocorrências de um elemento no multi-conjunto, mantendo a ordenação
por ordem decrescente da multiplicidade. Não use uma função de ordenação. -}

addNcopies :: Eq a => MSet a -> a -> Int -> MSet a
addNcopies ((a,num):t) b n | num > n = (a,num) : addNcopies t b n 
                           | a == b = [(a,num + n)] ++ t
                           | otherwise = (b,n) : ((a,num):t)
addNcopies [] b n = [(b,n)]
-------------------------------------------------------------------------------------------------------
--2)
data SReais = AA Double Double | FF Double Double | AF Double Double | FA Double Double | Uniao SReais SReais

{- (AA x y) representa o intervalo aberto ]x, y[, (FF x y) representa o intervalo fechado [x, y], (AF x
y) representa ]x, y], (FA x y) representa [x, y[ e (Uniao a b) a união de conjuntos. -}

{- (a) Defina a SReais como instância da classe Show, de forma a que, por exemplo, a apresentação
do termo Uniao (Uniao (AA 4.2 5.5) (AF 3.1 7.0)) (FF (-12.3) 30.0) seja
((]4.2,5.5[ U ]3.1,7.0]) U [-12.3,30.0]) -}

instance Show SReais where
    show (AA d1 d2) = "]" ++ show d1 ++ " , " ++ show d2 ++ "["
    show (FF d1 d2) = "[" ++ show d1 ++ " , " ++ show d2 ++ "]"
    show (AF d1 d2) = "]" ++ show d1 ++ " , " ++ show d2 ++ "]"
    show (FA d1 d2) = "[" ++ show d1 ++ " , " ++ show d2 ++ "["
    show (Uniao n1 n2) = "(" ++ show n1 ++ " U " ++ show n2 ++ ")"

{- (b) Defina a função pertence :: Double-> SReais -> Bool que testa se um elemento pertence
a um conjunto. -}
pertence :: Double -> SReais -> Bool
pertence x (AA d1 d2) = d1 > x && d2 < x
pertence x (FF d1 d2) = d1 >= x && d2 <= x
pertence x (FA d1 d2) = d1 >= x && d2 <= x
pertence x (AF d1 d2) = d1 > x && d2 < x
pertence x (Uniao d1 d2) = pertence x d1 && pertence x d2

--(c) Defina a função tira :: Double -> SReais -> SReais que retira um elemento de um conjunto.
tira :: Double -> SReais -> SReais
tira x (Uniao a b) = Uniao (tira x a) (tira x b)
tira x (AA a b) | pertence x (AA a b) = Uniao (AA a x) (AA x b)
                | otherwise = (AA a b)

tira x (FF a b) | pertence x (FF a b) = Uniao (FA a x) (AF x b)
                | otherwise = (FF a b)

tira x (AF a b) | pertence x (AF a b) = Uniao (AA a x) (AF x b)
                | otherwise = (AF a b)

tira x (FA a b) | pertence x (FA a b) = Uniao (FA a x) (AA x b)
                | otherwise = (FA a b)

----------------------------------------------------------------------------------------
--3. Considere o seguinte tipo para representar árvores irregulares (rose trees).

data RTree a = R a [RTree a]

arv ::(Num a) => RTree a
arv = (R 10 [(R 20 [(R 10 [])]), (R 40 []), (R 30 [])])

{- (a) Defina a função percorre :: [Int] -> RTree a -> Maybe [a] que recebe um caminho e
uma árvore e dá a lista de valores por onde esse caminho passa. Se o caminho não for válido
a função deve retornar Nothing. O caminho é representado por uma lista de inteiros (1 indica
seguir pela primeira sub-árvore, 2 pela segunda, etc). -} 

percorre :: [Int] -> RTree a -> Maybe [a]
percorre [] (R x _) = Just [x]
percorre _ (R x []) = Nothing
percorre (h:t) (R x l) = Just (aux (h:t) (R x l) [])
                    where aux :: [Int] -> RTree a -> [a] -> [a]
                          aux [] (R x l) acc = acc
                          aux (h:t) (R x l) acc = aux t (l !! (h-1)) (x : acc)