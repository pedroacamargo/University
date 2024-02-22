"""

Implemente uma função que formata um programa em C.
O código será fornecido numa única linha e deverá introduzir
um '\n' após cada ';', '{', ou '}' (com excepção da última linha).
No caso do '{' as instruções seguintes deverão também estar identadas
2 espaços para a direita.

"""

def formata(codigo):
    blocks = codigo.split(";")
    blocks2 = [i.strip() for i in blocks]
    blocksStrip = list(filter(lambda x: x != '',blocks2))
    print(blocksStrip)
        
    lenFirst = len(blocksStrip[0])
    hasBraces = False
    res = ""
    
    for i,elem in enumerate(blocksStrip):
        string = []
        stringFinal = ""
        
        if i != 0 and i != len(blocks) - 1 and hasBraces == True:
            string.append("  ")
    
        for letter in range(0,len(elem)):
            
            if elem[letter] == "{":
                hasBraces = True
                newStr = "{\n  "
                string.append(str(newStr))
            else:
                string.append(str(elem[letter]))
                
            if letter == len(elem) - 1 and elem[letter] != "}":
                string.append(";\n")
        
        if i == len(blocksStrip) - 1 and hasBraces == False:
            string[len(string) - 1] = ";"

        
        for a in range(0, len(string)):
            stringFinal += string[a]
        
        res += stringFinal


    print(res)
    
    return res
    
    
    # int x;\n  x=0;\n  x=x+1;\n 
    # int x;\nx=0;\nx=x+1;
    