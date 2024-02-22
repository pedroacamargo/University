'''
Defina uma função que, dada uma lista de nomes de pessoas, devolva essa lista ordenada 
por ordem crescente do número de apelidos (todos menos o primeiro nome). No caso de pessoas com o mesmo número de apelidos,
devem ser listadas por ordem lexicográfica do nome completo.
'''

# 

def apelidos(nomes):
    finalData = []
    for nome in nomes:
        splitted = nome.split(" ")
        sobrenomes = splitted[1:]
        
        name = ""
        for i in splitted:
            name += i + " "
        
        name = name.strip()
        data = (name, len(sobrenomes))
        
        finalData.append(data)
        

    finalData.sort(key = lambda t: (t[1],t[0]))
    
    result = []
    for t in finalData:
        result.append(t[0])
    
    return result