# Travessia em profundidade
def dfs(adj,o):
    return dfs_aux(adj,o,set(),{})

def dfs_aux(adj,o,vis,pai):
    vis.add(o)
    for d in adj[o]:
        if d not in vis:
            pai[d] = o
            dfs_aux(adj,d,vis,pai)
    return pai

# Travessia em largura
def bfs(adj,o):
    pai = {}
    vis = {o}
    queue = [o]
    while queue:
        v = queue.pop(0)
        for d in adj[v]:
            if d not in vis:
                vis.add(d)
                pai[d] = v
                queue.append(d)
    return pai


'''

O objectivo deste problema é determinar quantos movimentos são necessários para 
movimentar um cavalo num tabuleiro de xadrez entre duas posições.
A função recebe dois pares de coordenadas, que identificam a origem e destino pretendido,
devendo devolver o número mínimo de saltos necessários para atingir o destino a partir da origem.
Assuma que o tabuleiro tem tamanho ilimitado.

'''

def caminho(adj,o,d):
    pai = bfs(adj,o)
    caminho = [d]
    
    while d in pai:
        print(d)
        d = pai[d]
        caminho.insert(0,d)
    
    return caminho 

def adjacentes(x,y,adj,queue):
    for i in range(-2,3):
        for j in range(-2,3):
            if (i != 0 and j != 0) and abs(i) != abs(j):
                adj[(x,y)].add((i + x, j + y))
                
                if (i + x, j + y) not in adj:
                    adj[(i + x, j + y)] = set()
                if (i + x, j + y) not in queue:
                    queue.append((i + x, j + y))
    

def saltos(o,d):
    if o[0] == d[0] and o[1] == d[1]: return 0
    
    adj = {}
    x = o[0]
    y = o[1]
    
    adj[(o[0], o[1])] = set()
    queue = []
    
    while x != d[0] or y != d[1]:
        adjacentes(x,y,adj,queue)
        removed_element = queue.pop(0)
        x = removed_element[0]
        y = removed_element[1]
        
    adjacentes(x,y,adj,queue)
        
    res = caminho(adj,o,d)
    
    
    return len(res) - 1