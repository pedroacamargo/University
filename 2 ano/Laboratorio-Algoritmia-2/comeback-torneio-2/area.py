'''

Implemente uma função que calcula a área de um mapa que é acessível por
um robot a partir de um determinado ponto.
O mapa é quadrado e representado por uma lista de strings, onde um '.' representa
um espaço vazio e um '*' um obstáculo.
O ponto inicial consistirá nas coordenadas horizontal e vertical, medidas a 
partir do canto superior esquerdo.
O robot só consegue movimentar-se na horizontal ou na vertical. 

'''

mapa = ["..*..",
        ".*.*.",
        "*...*",
        ".*.*.",
        "..*.."]

p = (3,2)

# Travessia em profundidade
def dfs(adj,o):
    return dfs_aux(adj,o,set(),{})

def dfs_aux(adj,o,vis,pai):
    vis.add(o)
    for d in adj[o]:
        if d not in vis:
            pai[d] = o
            dfs_aux(adj,d,vis,pai)
    return vis


def build(mapa, l):
    adj = {}
    for i, row in enumerate(mapa):
        for j, col in enumerate(row):
            if ((j,i) not in adj):
                adj[(j,i)] = set ()
                
            for vertical, horizontal in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                newI, newJ = i + vertical, j + horizontal
                if 0 <= newI < l and 0 <= newJ < l and mapa[newI][newJ] == ".":
                    adj[(j, i)].add((newJ, newI))

    return adj

def area(p, mapa):
    tamanho = len(mapa)
    grafo = build(mapa, tamanho)
    print(grafo)
    return len(dfs(grafo, p))

area(p,mapa)