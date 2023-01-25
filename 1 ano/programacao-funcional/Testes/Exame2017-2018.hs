{- 1. Apresente uma definição recursiva da função (pré-definida) (!!) :: [a] -> Int -> a que dada uma lista e um inteiro, calcula o elemento da 
lista que se encontra nessa posição (assume-se que o primeiro elemento se encontra na posição 0). Por exemplo, (!!) [10,20,30] 1 corresponde a 20.
Ignore os casos em que a função não se encontra definida (i.e., em que a posição fornecida não corresponde a nenhuma posição válida da lista). -}
(!!!) :: [a] -> Int -> a
(!!!) 