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

transposta :: String -> String
transposta m = toString (transform m)

-- temos de pegar a string e transformar em Mat, enquanto também pegamos a cabeça de cada lista da Mat e fazemos uma lista de cabeças (para ser a transposta)
transform :: String -> Mat
transform [] = []
transform (h:t) = map (head) (stringToMat (h:t)) : transform (map (tail) (stringToMat (h:t)))

-- Depois transformamos a data Mat em string de volta, de forma que fique igual ao formato textual. O show irá transformar os ints em string 
toString :: Mat -> String
toString m = show (head m) ++ "\n" ++ toString (tail m)




----------------------------------------------------------------------------
--3) Feita por Pedro Augusto Camargo :)
data Lista a = Esq a (Lista a) | Dir (Lista a) a | Nula deriving Show

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