'''
Pretende-se que implemente uma função que detecte códigos ISBN inválidos. 
Um código ISBN é constituído por 13 digitos, sendo o último um digito de controlo.
Este digito de controlo é escolhido de tal forma que a soma de todos os digitos, 
cada um multiplicado por um peso que é alternadamente 1 ou 3, seja um múltiplo de 10.
A função recebe um dicionário que associa livros a ISBNs,
e deverá devolver a lista ordenada de todos os livros com ISBNs inválidos.
'''

def isbn(livros):
    res = []
    
    for livro in livros:
        digits = [int(digit) for digit in livros[livro]]
        alternate = 1
        
        for i in range(0, len(digits)):
            digits[i] *= alternate
            if alternate == 1: alternate = 3
            else: alternate = 1
            
        if sum(digits) % 10 != 0:
            res.append(livro)
        
    res.sort()
    return res