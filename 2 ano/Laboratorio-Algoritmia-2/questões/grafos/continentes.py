def dfs(adj,o):
    return dfs_aux(adj,o,set(),{})

def dfs_aux(adj,o,vis,pai):
    vis.add(o)
    for d in adj[o]:
        if d not in vis:
            pai[d] = o
            dfs_aux(adj,d,vis,pai)
    return pai

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

O objectivo deste problema é determinar o tamanho do maior continente de um planeta.
Considera-se que pertencem ao mesmo continente todos os países com ligação entre si por terra. 
Irá receber uma descrição de um planeta, que consiste numa lista de fronteiras, onde cada fronteira
é uma lista de países que são vizinhos entre si. 
A função deverá devolver o tamanho do maior continente.

'''
#100%

def maior(vizinhos):
    if len(vizinhos) == 0:
        return 0
    
    adj = {}
    
    for arestas in vizinhos:
        
        for i in range(0, len(arestas)):
            
            if arestas[i] not in adj:
                adj[arestas[i]] = set()
                
            for j in range(0, len(arestas)):
                
                if arestas[i] != arestas[j]:
                    adj[arestas[i]].add(arestas[j])
            
        
        
    print("Grafo: ")
    print(adj)
    
    
    maxLen = 0
    for elem in adj:
        atual = len(dfs(adj,elem))
        maxLen = max(atual, maxLen)
    
    return maxLen + 1
    
    
    
    
    
    
    
    
    