def cruzamentos(ruas):
    primeiraUltima = [i[0] + i[-1] for i in ruas]
    letras = {}
    for i in primeiraUltima:
        for j in range(0,2):
            if i[j] not in letras:
                letras[i[j]] = 1
            elif i[j] in letras:
                letras[i[j]] += 1
            if i[0] == i[1]: break
    
    res = [(i, letras[i]) for i in letras]
    res.sort(key=lambda t: (t[1],t[0]))
    
    return res
