{- 1. Apresente uma definição recursiva da função (pré-definida) (!!) :: [a] -> Int -> a que dada uma lista e um inteiro, calcula o elemento da 
lista que se encontra nessa posição (assume-se que o primeiro elemento se encontra na posição 0). Por exemplo, (!!) [10,20,30] 1 corresponde a 20.
Ignore os casos em que a função não se encontra definida (i.e., em que a posição fornecida não corresponde a nenhuma posição válida da lista). -}
(!!!) :: [a] -> Int -> a
(!!!) l 0 = head l
(!!!) l x = (!!!) (tail l) (x-1)

--2. Considere o seguinte tipo para representar movimentos de um robot.

data Movimento = Norte | Sul | Este | Oeste deriving Show

{- Defina a função posicao :: (Int,Int) -> [Movimento] -> (Int,Int) que, dada uma posição inicial (abcissa e ordenada) e uma lista de movimentos 
(um movimento para Norte aumenta a ordenada e para Este aumenta a abcissa), calcula a posição final do robot depois de efectuar essa
sequência de movimentos. -}

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (h:t) = case h of
                    Norte -> posicao (x,y+1) t
                    Sul -> posicao (x,y-1) t
                    Este -> posicao (x+1,y) t
                    Oeste -> posicao (x-1,y) t

{- 3. Apresente uma definição recursiva da função any :: (a -> Bool) -> [a] -> Bool que testa se um predicado é verdade para algum elemento 
de uma lista. Por exemplo, any odd [1..10] == True. -}

any' :: (a -> Bool) -> [a] -> Bool
any' f [] = False
any' f (h:t) = if f h then True else any' f t

{- 4. Considere o sequinte tipo type Mat a = [[a]] para representar matrizes. Defina a função triSup :: Num a => Mat a -> Bool que testa se uma
matriz quadrada é triangular superior (i.e., todos  os elementos abaixo da diagonal são nulos). Esta função deve devolver True para a matriz
[[1,2,3], [0,4,5], [0,0,6]]. -}

type Mat a = [[a]]

-- Continuar (Não está pronta, certamente não era para fazer isso mas dá para continuar e fazer assim!)
{-triSup :: Num a => Mat a -> Bool
triSup [[]] = True
triSup l = aux ((length l) - 1) l
           where aux :: Num a => Int -> Mat a -> Bool
                 aux x l = if x > 0 && x < length l then foldr (\y acc -> if foldr (\z acc2 -> (l !! y) !! z ) (length l - 1) [0..acc2] then acc else False) True [0..(length l - 1)]

-}

triSup :: (Num a,Eq a) => Mat a -> Bool
triSup (h:t) = let l = map head t
                   rm = map tail t
               in all (==0) l && triSup rm


{- 5. Defina um programa movimenta :: IO (Int,Int) que lê uma sequência de comandos do teclado (’N’ para Norte, ’S’ para Sul, ’E’ para Este, ’O’ 
para Oeste e qualquer outro caracter para parar) e devolve a posição final do robot (assumindo que a posição inicial é (0,0)). -}

movimenta :: IO (Int, Int)
movimenta = do
    putStrLn "Escreva uma sequencia de comandos ('N' para Norte, 'S' para Sul, 'E' para Este, 'O' para Oeste e qualquer outro caracter para parar)"
    commands <- getLine
    let finalPosition = foldl move (0, 0) commands
    putStrLn ("Posição final: " ++ show finalPosition)
    return finalPosition

move :: (Int, Int) -> Char -> (Int, Int)
move (x, y) 'N' = (x, y+1)
move (x, y) 'S' = (x, y-1)
move (x, y) 'E' = (x+1, y)
move (x, y) 'O' = (x-1, y)
move pos _ = pos


{- 6. Considere o tipo Imagem para representar imagens compostas por quadrados (apenas com coordenadas positivas).
Ao lado apresenta-se um exemplo de uma destas imagens constituída por três quadrados (cujos
lados têm dimensão 5, 4 e 2). -}

data Imagem = Quadrado Int | Mover (Int,Int) Imagem | Juntar [Imagem]

{- ex :: Imagem
   ex = Mover (5,5) (Juntar [Mover (0,1) (Quadrado 5), Quadrado 4, Mover (4,3) (Quadrado 2)])
(a) Defina a função vazia :: Imagem -> Bool que testa se uma imagem não tem nenhum quadrado. A função devolve False para o exemplo acima. -}

ex :: Imagem
ex = Mover (5,5) (Juntar [Mover (0,1) (Quadrado 5), Quadrado 4, Mover (4,3) (Quadrado 2)])

vazia :: Imagem -> Bool
vazia (Quadrado x) = False
vazia (Mover (_,_) x) = vazia x
vazia (Juntar []) = True
vazia (Juntar x) = all vazia x

{- (b) Defina a função maior :: Imagem -> Maybe Int que calcula a largura do maior quadrado de uma imagem. No exemplo acima, maior ex == Just 5. 
Note que a imagem pode não ter quadrados. -}

maior :: Imagem -> Maybe Int
maior l | vazia l = Nothing
        | otherwise = Just (maximum (quads l))
                    where quads :: Imagem -> [Int]
                          quads (Quadrado x) = [x]
                          quads (Mover (_,_) x) = quads x
                          quads (Juntar l) = concat (map quads l)

{- (c) Defina Imagem como uma instância de Eq de forma a que duas imagens são iguais sse forem compostas pelos mesmos quadrados nas mesmas posições.
Por exemplo, a imagem ex acima deverá ser igual a Juntar [Mover (5,5) (Quadrado 4), Mover (5,6) (Quadrado 5), Mover (9,8) (Quadrado 2)]. -}
instance Eq Imagem where
    x == y = let a = posicoesI (0,0) x
                 b = posicoesI (0,0) y
             in (all (pertence a) b)

posicoesI :: (Int,Int) -> Imagem -> [Imagem]
posicoesI (x,y) (Quadrado a) = [(Mover (x,y) (Quadrado x))]
posicoesI (x,y) (Mover (a,b) l) = posicoesI (x+a,y+b) l
posicoesI (x,y) (Juntar l) = concat (map (posicoesI (x,y)) l)

pertence :: [Imagem] -> Imagem -> Bool
pertence [] _ = False
pertence ((Mover (x1,y1) (Quadrado d1)):t) (Mover (x2,y2) (Quadrado d2)) | x1==x2 && y1==y2 = d1 == d2
                                                                         | otherwise = pertence t (Mover (x2,y2) (Quadrado d2))