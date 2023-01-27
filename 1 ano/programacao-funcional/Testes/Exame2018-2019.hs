{- 1. Apresente uma definição recursiva das seguintes funções sobre listas:

(a) isSorted :: (Ord a) => [a] -> Bool que testa se uma lista está ordenada por ordem crescente. -}

isSorted :: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [x] = True
isSorted (h:t) = if h < head t then isSorted t else False

{- (b) inits :: [a] -> [[a]] que calcula a lista dos prefixos de uma lista. Por exemplo, inits [11,21,13]
corresponde a [[],[11],[11,21],[11,21,13]]. -}

inits' :: [a] -> [[a]]
inits' [] = [[]]
inits' (h:t) = inits' (init (h:t)) ++ [(h:t)]

{- 2. Defina maximumMB :: (Ord a) => [Maybe a] -> Maybe a que dá o maior elemento de uma lista de
elementos do tipo Maybe a. Considere Nothing o menor dos elementos. -}

maximumMB :: (Ord a) => [Maybe a] -> Maybe a
maximumMB [Just a] = Just a
maximumMB ((Nothing):t) = maximumMB t
maximumMB (h:(Nothing):t) = maximumMB (h:t)
maximumMB ((Just a1):(Just a2):t) = if a1 > a2 then maximumMB ((Just a1:t)) else maximumMB ((Just a2):t)
maximumMB _ = Nothing



maximumMB' :: (Ord a, Num a) => [Maybe a] -> Maybe a
maximumMB' l = Just (maximum (transformToList l))

transformToList :: (Ord a, Num a) => [Maybe a] -> [a]
transformToList [Just x] = [x]
transformToList [Nothing] = [-99999999]
transformToList ((Nothing):t) = -99999999 : transformToList t
transformToList ((Just x):t) = x : transformToList t

--3. Considere o seguinte tipo para representar árvores em que a informação está nas extermidades:

data LTree a = Tip a | Fork (LTree a) (LTree a)

{- (a) Defina a função listaLT :: LTree a -> [a] que dá a lista das folhas de uma árvore (da esquerda
para a direita). -}

listaLT :: LTree a -> [a]
listaLT (Tip a) = [a]
listaLT (Fork ae ad) = listaLT ae ++ listaLT ad

{- (b) Defina uma instância da classe Show para este tipo que apresente uma folha por cada linha, precedida de tantos
pontos quanta a sua profundidade na árvore. Veja o exemplo.
> Fork (Fork (Tip 7) (Tip 1)) (Tip 2)
..7
..1
.2
 -}


instance Show a => Show (LTree a) where
    show (Tip x) = show x  
    show x = show' x 0
            where show' :: LTree a -> Int -> String
                  show' (Tip x) acc = (replicate acc '.') ++ show x 
                  show' (Fork ae ad) acc = show' ae (acc+1) ++ "\n" ++ show' ad (acc+1)

{- 4. Utilizando uma função auxiliar com acumuladores, optimize a seguinte definição que determina a soma
do segmento inicial de uma lista com soma máxima.  -}

{-
maxSumInit' :: (Num a, Ord a) => [a] -> a
maxSumInit' l = maximum [sum m | m <- inits l]

maxSumInit'' :: (Num a, Ord a) => [a] -> a
maxSumInit'' l = foldl (\ acc x -> max(sum x) acc) (sum l) (inits l)
-}

{- 5. Uma relação binária entre elementos de um tipo a pode ser descrita como um conjunto (lista) de pares
[(a,a)]. Outras formas alternativas consistem em armazenar estes pares agrupados de acordo com a sua
primeira componente. Considere os seguintes três tipos para estas representações. -}

type RelP a = [(a,a)]
type RelL a = [(a,[a])]
type RelF a = ([a], a->[a])

{- Por exemplo, a relação representada na figura ao lado pode ser implementada por:
• [(1,3),(1,4),(2,1),(2,4),(2,5),(3,7),(4,7),(5,7),(6,5),(7,6)] :: RelP Int
• [(1,[3,4]),(2,[1,4,5]),(3,[7]),(4,[7]),(5,[7]),(6,[5]),(7,[6])] :: RelL Int
• ([1,2,3,4,5,6,7],f) :: RelF Int, em que f é uma função tal que
f 1 = [3,4], f 2 = [1,4,5], f 3 = [7], f 4 = [7], f 5 = [7], f 6 = [5], e f 7 = [6].
(a) Considere a seguinte função de conversão entre representações: -}

convLP :: RelL a -> RelP a
convLP l = concat (map junta l)
           where junta (x,xs) = map (\y->(x,y)) xs

{- Defina a função de conversão convPL :: (Eq a) => RelP a -> RelL a, inversa da anterior. Isto
é, tal que convPL (convLP r) = r, para todo o r. -}

convPL :: (Eq a) => RelP a -> RelL a
convPL [(x,y)] = [(x,[y])]
convPL (h:t) = junta h (convPL t)
            where junta (x,y) l = if x `elem` map (fst) l then map (\(c,d) -> if c == x then (c,y:d) else (c,d)) l else (x,[y]):l

--ou

convPL' :: (Eq a,Ord a) => RelP a -> RelL a
convPL' l = let a = sortOn fst l
                b = groupBy (\(x,_) (y,_) -> x == y) a
                k = map junta b
                junta :: [(a,a)] -> (a,[a])
                junta x = (fst (head x),(map snd x))
            in k

--
{-
criaRelPint :: Int -> IO (RelP Int)
criaRelPint 0 = return []
criaRelPint n = do
    putStr "Introduz dois numeros (separados por um espaco): "
    (num1,num2) <- fmap (span (/= ' ')) getLine
    fmap ((read num1,read num2) :) $ criaRelPint (n - 1)
-}

{- (c) Defina as funções de conversão entre as representações RelF a e RelP a,
i. convFP :: (Eq a) => RelF a -> RelP a
ii. convPF :: (Eq a) => RelP a -> RelF a
tal que convFP (convPF r) = r, para todo o r. -}

convFP :: (Eq a) => RelF a -> RelP a
convFP (l,f) = convLP $ map (\x -> (x,f x)) l


convPF :: (Eq a) => RelP a -> RelF a
convPF x = ((map fst y),f)
           where y = convPL x
                 f a = foldl (\acc (b,c) -> if a == b then c else acc) [] y