--1)

data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show

arv :: (Num a) => BTree a
arv = Node 7 (Node 5 (Node 3 Empty Empty) (Node 2 Empty Empty))
             (Node 6 (Node 1 Empty (Node 8 Empty Empty)) Empty)

arv2 :: (Num a) => BTree a
arv2 = Node 14 (Node 2 (Node 9 Empty Empty) (Node 4 Empty Empty))
               (Node 24 (Node 14 Empty Empty) Empty)

arv3 :: (Num a) => BTree a
arv3 = Node 2 (Empty) (Node 4 (Empty) (Empty))

--a)
altura :: BTree a -> Int
altura Empty = 0
altura (Node _ x y) = 1 + max ( altura x ) (altura y) 

--b)
contaNodos :: BTree a -> Int
contaNodos Empty = 0
contaNodos (Node x ae ad) = 1 + contaNodos ae + contaNodos ad

--c)
folhas :: BTree a -> Int
folhas Empty = 0
folhas (Node x Empty Empty) = 1
folhas (Node x ae ad) = folhas ae + folhas ad

--d)
prune :: Int -> BTree a -> BTree a
prune _ (Empty) = Empty
prune 0 _ = Empty
prune x (Node c ae ad) = Node c (prune (x-1) ae) (prune (x-1) ad)

--e) False -> Esquerda || True -> direita
path :: [Bool] -> BTree a -> [a]
path (h:t) (Empty) = []
path [] (Node x ae ad) = [x]
path (h:t) (Node x ae ad) | h == False = x : path t ae
                          | h == True = x : path t ad

--f)
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node r ae ad) = Node r (mirror ad) (mirror ae)

--g)
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT f (Node x1 ae1 ad1) (Node x2 ae2 ad2) = let a = zipWithBT f ae1 ae2
                                                      b = zipWithBT f ad1 ad2
                                                  in (Node (x1 `f` x2) a b)
zipWithBT _ _ _ = Empty

--h)
unzipBT :: BTree (a,b,c) -> (BTree a,BTree b,BTree c)
unzipBT Empty = (Empty,Empty,Empty)
unzipBT (Node (r1,r2,r3) ae ad) = let (ae1,ae2,ae3) = unzipBT ae
                                      (ad1,ad2,ad3) = unzipBT ad
                                  in ((Node r1 ae1 ad1),(Node r2 ae2 ad2),(Node r3 ae3 ad3))

--------------------------------------------------------------------------------------------------------
--2)
--a)
minimo :: Ord a => BTree a -> a
minimo (Node x Empty _) = x
minimo (Node x ae ad) = minimo ae

--b)
semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node x Empty d) = d
semMinimo (Node x ae ad) = (Node x (semMinimo ae) ad)

--c)
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node r Empty Empty) = (r,Empty)
minSmin (Node r Empty ad) = (r,ad)
minSmin (Node r ae ad) = let (min, ae') = minSmin ae
                         in (min, Node r ae' ad)

--d)
remove :: Ord a => a -> BTree a -> BTree a
remove _ Empty = Empty
remove x (Node r ae ad) | x > r = Node r ae (remove x ad)
                        | x < r = Node r (remove x ae) ad
                        | otherwise = aux ad ae
                        where aux :: Ord a => BTree a -> BTree a -> BTree a
                              aux Empty ad = ad
                              aux ae Empty = ae
                              aux ae ad = let ( m,ad') = minSmin ad
                                          in Node m ae ad'

----------------------------------------------------------------------------------
--3)
type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL deriving Show
data Classificacao = Aprov Int | Rep | Faltou deriving Show
type Turma = BTree Aluno -- árvore binária de procura (ordenada por número)
-- data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show

lcc_tp2 :: Turma
lcc_tp2 =  Node (7, "Ana", ORD, Aprov 16)
                (Node (4, "Rui", TE, Faltou)
                    Empty
                    (Node (6, "To", TE, Aprov 14) Empty Empty)
                )
                (Node (9, "Zé", ORD, Aprov 12)
                    (Node (8, "João", ORD, Aprov 14) Empty Empty)
                    (Node (11, "Maria", ORD, Aprov 18) Empty Empty)
                )

--a)
inscNum :: Numero -> Turma -> Bool
inscNum x Empty = False
inscNum x (Node (n,_,_,_) e d) | x == n = True
                               | otherwise = inscNum x e || inscNum x d

--b)
inscNome :: Nome -> Turma -> Bool
inscNome n Empty = False
inscNome n (Node (_,x,_,_) d e) | n == x = True
                                | otherwise = inscNome n e || inscNome n d

--c)
trabEst :: Turma -> [(Numero,Nome)]
trabEst Empty = []
trabEst (Node (n,nome,reg,classificacao) e d) = case reg of 
                                        TE -> [(n,nome)] ++ trabEst e ++ trabEst d
                                        _ -> trabEst e ++ trabEst d

--d)
nota :: Numero -> Turma -> Maybe Classificacao
nota x Empty = Nothing
nota x (Node (n,_,_,grade) e d) | x > n = nota x d
                                | x < n = nota x e
                                | otherwise = Just grade

--e)
--percFaltas :: Turma -> Float
--percFaltas Empty = 0
--percFaltas (Node (a,b,c,grade) e d) = (fromIntegral (aux 0 (Node (a,b,c,grade) e d))) / 100
--                                    where aux :: (Eq Classificacao) => Int -> Turma -> Int
--                                          aux acc Empty = acc
--                                          aux acc (Node (_,_,_,grade) e d) | grade == Faltou = (aux (acc+1) e) + (aux (acc+1) d)

percFaltas' :: Turma -> Float
percFaltas' Empty = 0
percFaltas' t = ((fromIntegral(faltas t))/(fromIntegral(contaNodos t)))*100
                                       where faltas :: Turma -> Int
                                             faltas Empty = 0
                                             faltas (Node (_,_,_,clas) ae ad) = (case clas of Faltou -> 1 + faltas ae + faltas ad; otherwise -> 0 + faltas ae + faltas ad)

--f)
mediaAprov :: Turma -> Float
mediaAprov Empty = 0
mediaAprov t = sumNotas t / total t
               where sumNotas :: Turma -> Float
                     sumNotas Empty = 0
                     sumNotas (Node (_,_,_,clas) ae ad) = (case clas of Aprov nota -> fromIntegral nota + sumNotas ae + sumNotas ad; otherwise -> sumNotas ae + sumNotas ad)
                     total :: Turma -> Float
                     total Empty = 0
                     total (Node (_,_,_,clas) ae ad) = (case clas of Aprov nota -> 1 + total ae + total ad; otherwise -> 0)

--g)
aprovAv :: Turma -> Float
aprovAv Empty = 0
aprovAv t = a/b
            where (a,b) = aux t
                  aux Empty = (0,0)
                  aux (Node (_,_,_,clas) ae ad) = (case clas of Aprov nota -> (x+1,y); Rep -> (x,y+1); otherwise -> (x,y))
                                                   where (x,y) = (aprovesq + aprovdir, repesq + repdir)
                                                         (aprovesq,repesq) = aux ae
                                                         (aprovdir,repdir) = aux ad
{-
TRAVESSIAS
esq - pai - dir ===> infixa
esq - dir - pai ===> posfixa
pai - esq - dir ===> perfixa
-}
