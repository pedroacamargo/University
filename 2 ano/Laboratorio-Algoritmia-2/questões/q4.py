"""

Implemente uma função que formata um programa em C.
O código será fornecido numa única linha e deverá introduzir
um '\n' após cada ';', '{', ou '}' (com excepção da última linha).
No caso do '{' as instruções seguintes deverão também estar identadas
2 espaços para a direita.

"""

def formata(codigo):
    blocks = codigo.split(";")
    blocksStrip = [i.strip() for i in blocks]
    
    res = ""
    for i,elem in enumerate(blocksStrip):
        string = []
    
        for letter in range(0,len(elem) - 1):
            
            if elem[letter] == "{":
                newStr = "{\n"
                string.append(str(newStr))
            else:
                string.append(str(elem[letter]))

        res = "".append(string.join())


    print(res)
    
    return "return 0;"