'''
Implemente uma função que calcula a área de um mapa que é acessível por
um robot a partir de um determinado ponto.
O mapa é quadrado e representado por uma lista de strings, onde um '.' representa
um espaço vazio e um '*' um obstáculo.
O ponto inicial consistirá nas coordenadas horizontal e vertical, medidas a 
partir do canto superior esquerdo.
O robot só consegue movimentar-se na horizontal ou na vertical. 
'''

def create(p,mapa):
    visited = []
    queue = [(p[0],p[1])]
    actual = [(p[0],p[1])]
    count = 0
    
    while len(queue) > 0:
        actual = queue.pop(0)
        for d in [(1,0),(-1,0),(0,1),(0,-1)]:
            if len(mapa) > d[0] + actual[0] >= 0 and 0 <= d[1] + actual[1] < len(mapa):
                data = (actual[0] + d[0], actual[1] + d[1])
                
                if data not in visited:
                    visited.append(data)
                    if mapa[data[1]][data[0]] == '.':
                        count += 1
                        queue.append(data)
                        print(data)
        
        
    return count

def area(p,mapa):
    if len(mapa) == 0:
        return 0
    canPass = False
    for d in [(1,0),(-1,0),(0,1),(0,-1)]:
        if len(mapa) > d[0] + p[0] >= 0 and 0 <= d[1] + p[1] < len(mapa):
            data = (p[0] + d[0], p[1] + d[1])
            
            if mapa[data[1]][data[0]] == '.':
                canPass = True
        
    if canPass == False: return 1
        
    
    
    # MAPA[Y][X]
    graphData = create(p,mapa)
    print(graphData)
    
    
    
    return graphData