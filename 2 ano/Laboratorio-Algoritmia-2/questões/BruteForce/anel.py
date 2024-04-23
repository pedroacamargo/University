'''

Um anel de tamanho n (um número par) consiste numa permutação do números de 1 
até n em que a soma de quaisquer dois números adjacentes é um número primo
(considera-se que o primeiro elemento da sequência é adjacente do último).
Implemente uma função que calcule um destes aneis de tamanho n.

'''

from itertools import permutations

# anel de tamanho n
# permutação do 1 até n em que a soma de qqr 2 numeros adjacentes é um numero primo

def isPrime(num):
    
    if num == 1:
        return False
    
    flag = True
    for i in range(2, num):
        if num % i == 0:
            flag = False
            break
    
    return flag

def isValid(p):
    tupleSize = len(p)
    
    if not isPrime(p[0] + p[tupleSize - 1]):
        return False
    
    flag = True
    for i in range(0,tupleSize - 1):
        if not isPrime(p[i] + p[i+1]):
            flag = False
            break
        
    return flag

def anel(n):
    num = [a for a in range(1,n + 1)]
    for p in permutations(num):
        if isValid(p):
            res = [aa for aa in p]
            return res
    return []