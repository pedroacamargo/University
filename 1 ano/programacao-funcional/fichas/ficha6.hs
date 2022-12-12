-- 1)
data BTree a = Empty
             | Node a (BTree a) (BTree a)
             deriving Show

arv :: BTree Int
arv = Node 7 (Node 5 (Node 3 Empty Empty) (Node 2 Empty Empty))
             (Node 6 (Node 1 Empty (Node 8 Empty Empty)) Empty)

arv2 :: BTree Int
arv2 = Node 14 (Node 2 (Node 9 Empty Empty) (Node 4 Empty Empty))
               (Node 24 (Node 14 Empty (Node 10 Empty Empty)) Empty)

altura :: BTree a -> Int
altura Empty = 0
altura (Node _ e d) = 1 + max (altura e) (altura d)

contaNodos :: BTree a -> Int
contaNodos Empty = 0
contaNodos (Node _ e d) = 1 + contaNodos e + contaNodos d

folhas :: BTree a -> Int
folhas Empty = 0
folhas (Node _ Empty Empty) = 1
folhas (Node _ e d) = folhas e + folhas d

prune :: Int -> BTree a -> BTree a
prune 0 (Node _ _ _) = Empty
prune x Empty = Empty
prune x (Node y e d) = Node y (prune (x-1) e) (prune (x-1) d)

-- False: esquerda || True: direita
path :: [Bool] -> BTree a -> [a]
path [] (Node r e d) = [r]
path (h:t) (Node r e d) | h == False = r : (path t e)
                        | otherwise = r : (path t d)

mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node r e d) = Node r (mirror d) (mirror e)

zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT _ _ Empty = Empty
zipWithBT _ Empty _ = Empty
zipWithBT f (Node r e d) (Node r2 e2 d2) =
     Node (f r r2) (zipWithBT f e e2) (zipWithBT f d d2)

unzipBT :: BTree (a,b,c) -> (BTree a, BTree b, BTree c)
unzipBT Empty = (Empty, Empty, Empty)
unzipBT (Node (a, b, c) e d) = ((Node a e1 d1),(Node b e2 d2), (Node c e3 d3))
    where (e1, e2, e3) = unzipBT e
          (d1, d2, d3) = unzipBT d


-- 3)
type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL deriving Show
data Classificacao = Aprov Int
                   | Rep
                   | Faltou
                   deriving Show

type Turma = BTree Aluno -- árvore binária de procura (ordenada por números)

lcc_tp2 :: Turma
lcc_tp2 =  Node (7, "Ana", ORD, Aprov 16)
                (Node (4, "Rui", TE, Faltou)
                    Empty
                    (Node (6, "To", ORD, Aprov 14) Empty Empty)
                )
                (Node (9, "Zé", ORD, Aprov 12)
                    (Node (8, "João", ORD, Aprov 14) Empty Empty)
                    (Node (11, "Maria", ORD, Aprov 18) Empty Empty)
                )

inscNum :: Numero -> Turma -> Bool
inscNum x Empty = False
inscNum x (Node (a,b,c,f) e d) | x == a = True
                               | x < a = inscNum x e
                               | x > a = inscNum x d

inscNome :: Nome -> Turma -> Bool
inscNome  _ Empty = False
inscNome (h:t) (Node (a,b,c,f) e d) | (h:t) == b = True
                                    | otherwise = inscNome (h:t) e || inscNome (h:t) d

trabEst :: Turma -> [(Numero, Nome)]
trabEst Empty = []
trabEst (Node (na,no,te,nt) e d) = trabEst e ++ [(na,no)] ++ trabEst d 

nota :: Numero -> Turma -> Maybe Classificacao
nota x (Node (na,no,te,nt) e d) | x == no = Just nt
                                | x < no = nota x e
                                | x > no = nota x d


-- *** [PEGAR COM ALGUÉM]
percFaltas :: Turma -> Float
percFaltas t = percFaltas' t

percFaltas' :: Turma -> (Int, Int)
percFaltas' Empty = (0,0)
percFaltas' (Node (na,no,ra,nt) e d)
        | nt == Faltou = (percFaltas' e + percFaltas' d, percFaltas' e + percFaltas' d + 1)
        | otherwise = (percFaltas' e + percFaltas' d + 1, percFaltas' e + percFaltas' d)
--- *** [PEGAR COM ALGUÉM]



{-
        TRAVESSIAS
esq - pai - dir ===> infixa
esq - dir - pai ===> posfixa
pai - esq - dir ===> perfixa

-}