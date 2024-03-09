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

def saltos(o,d):
    if o[0] == d[0] and o[1] == d[1]: return 0
    
    adj = {}
    
    origin = [o[0], o[1]]
    x = origin[0]
    y = origin[1]
    
    adj[(origin[0], origin[1])] = set()
    
    while x != d[0] and y != d[1]:
        
        for i in range(-2,3):
            for j in range(-2,3):
                if (i != 0 and j != 0) and abs(i) != abs(j):
                    adj[x,y].add((i,j))
                    adj[(i,j)] = set()
                    
        
        
            
        #adj[(2,-1)] = set()
        #adj[(2,-1)].add((1,1))
        
        adj[(1,1)] = set()
            
        x = d[0]
        y = d[1]
        
        
    #res = bfs(adj,(0,0))
    print(adj)
    #print(res)
    
    
    return -1