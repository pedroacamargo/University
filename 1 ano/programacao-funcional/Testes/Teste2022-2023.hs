--1) unlines ["Prog", "Func"] == "Prog\nFunc"
unlines' :: [String] -> String
unlines' [] = ""
unlines' (str:t) = str ++ "\n" ++ unlines' t

--2)
--a)
type Mat = [[Int]]

{-

"2,3,6,4\n12,3,12,4\n3,-4,5,7" = [2  3  6  4]
                                 [12 3  12 4]       
                                 [3 -4  5  7]
-}

--stringToMat :: String -> Mat
--stringToMat s = map stringToVector (lines s)

-- A função stringToVector irá pegar as linhas transformadas da string e transformar elas em vetores, que serão as colunas da matriz.

-- Tipo da função ----->  stringToVector :: [String] -> Mat




--b)

-- Transposta em formato textual: "2,12,3 \n 3,3,-4 \n 6,12,5 \n 4,4,7"

--transposta :: String -> String
--transposta m = toString (transform m)

-- temos de pegar a string e transformar em Mat, enquanto também pegamos a cabeça de cada lista da Mat e fazemos uma lista de cabeças (para ser a transposta)
--transform :: String -> Mat
--transform [] = []
--transform (h:t) = map (head) (stringToMat (h:t)) : transform (map (tail) (stringToMat (h:t)))

-- Depois transformamos a data Mat em string de volta, de forma que fique igual ao formato textual. O show irá transformar os ints em string 
toString :: Mat -> String
toString m = show (head m) ++ "\n" ++ toString (tail m)




----------------------------------------------------------------------------
--3) Feita por Pedro Augusto Camargo :)
data Lista a = Esq a (Lista a) | Dir (Lista a) a | Nula 

lista' :: Num a => Lista a
lista' = Dir (Esq 1 (Dir (Dir Nula 2) 5)) 2
--a)
-- função main
semUltimo :: Lista a -> Lista a
semUltimo Nula = Nula
semUltimo (Dir l x) = aux (Dir l x) (somaesubtrai (Dir l x)) 0

-- Quando vai para direita +1, esquerda -1. Serve para saber quando é que a lista fica mais a direita possível
somaesubtrai :: Lista a -> Int
somaesubtrai Nula = 0
somaesubtrai (Dir l x) = 1 + somaesubtrai l
somaesubtrai (Esq x l) = -1 + somaesubtrai l

-- Função auxiliar com o acumulador para saber quando deletar o elemento da árvora quando está mais a direita.
aux :: Lista a -> Int -> Int -> Lista a
aux Nula _ _ = Nula
aux (Dir l x) n acc = if n /= acc then (Dir (aux l n (acc+1)) x)
                                  else Nula
aux (Esq x l) n acc = if n /= acc then (Esq x (aux l n (acc)))
                                  else Nula


--b) Esq 1 (Dir (Dir (Esq 9 Nula) 3) 4) seja apresentada como [1, 9, 3, 4].
arv ::(Num a) => Lista a
arv = (Esq 1 (Dir (Dir (Esq 9 Nula) 3) 4))

instance Show a => Show (Lista a) where
    show (Esq x Nula) = show x
    show (Esq x l) = show x ++ "," ++ show l
    show (Dir Nula x) = show x
    show (Dir l x) = show l ++ "," ++ show x
    show (Nula) = ""

showArv :: Show a => Lista a -> String
showArv a = "[" ++ show a ++ "]"

-----------------------------------------------------------------------------------------
--4)
{-
TRAVESSIAS
esq - pai - dir ===> infixa
esq - dir - pai ===> posfixa
pai - esq - dir ===> perfixa
-}

data BTree a = Empty | Node a (BTree a) (BTree a)

--a) Não tenho certeza se está certa
numera :: BTree a -> BTree (a,Int)
numera (Empty) = Empty
numera (Node r ae ad) = (Node (r, fst (numeraAux 1 (Node r ae ad))) (numera ae) (numera ad))

numeraAux :: Int -> BTree a -> (Int,BTree (a,Int))
numeraAux x (Empty) = (x,Empty)
numeraAux x (Node r Empty ad) = (1, (Node (r,x) Empty (continuarArv (x+1) ad)))
numeraAux x (Node r ae Empty) = (1, (Node (r,x) (continuarArv (x+1) ae) Empty))
numeraAux x (Node r ae ad) = (1 - contarAux ae + contarAux ad, (Node (r,x) (continuarArv (x-1) ae) (continuarArv (x+1) ad)))

contarAux :: BTree a -> Int
contarAux Empty = 0
contarAux (Node r ae ad) = 1 + contarAux ae + contarAux ad

continuarArv :: Int -> BTree a -> BTree (a,Int)
continuarArv x (Empty) = Empty
continuarArv x (Node r ae ad) = (Node (r,x) (continuarArv (x-1) ae) (continuarArv (x+1) ad))

--b)
inorder :: BTree a -> [a]
inorder Empty = []
inorder (Node r e d) = (inorder e) ++ (r:inorder d)

unInorder :: [a] -> [BTree a]
unInorder (h:t) | 