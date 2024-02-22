'''
Neste problem pretende-se que defina uma função que, dada uma string com palavras, 
devolva uma lista com as palavras nela contidas ordenada por ordem de frequência,
da mais alta para a mais baixa. Palavras com a mesma frequência devem ser listadas 
por ordem alfabética.
'''

def frequencia(texto):
    palavras = texto.split(" ")
    tupleArray = []
    readWords = []
    res = []
    
    for palavra in palavras:
        count = 0
        for i in range(0,len(palavras)):
            if palavras[i] == palavra:
                count += 1
        
        if palavra not in readWords:
            readWords.append(palavra)
            tupleArray.append((palavra,count))
            
    
    tupleArray.sort(key=lambda x: (-x[1],x[0]))
    
    for i in tupleArray:
        res.append(i[0])

    return res