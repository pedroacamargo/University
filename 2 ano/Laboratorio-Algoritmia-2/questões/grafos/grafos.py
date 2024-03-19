# Grafos não pesados

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

# Grafos pesados

# Algoritmo de Dijkstra
def dijkstra(adj,o):
    pai = {}
    dist = {}
    dist[o] = 0
    orla = {o}
    while orla:
        v = min(orla,key=lambda x:dist[x])
        orla.remove(v)
        for d in adj[v]:
            if d not in dist:
                orla.add(d)
                dist[d] = float("inf")
            if dist[v] + adj[v][d] < dist[d]:
                pai[d] = v
                dist[d] = dist[v] + adj[v][d]
    return pai

# Algoritmo de Prim
def prim(adj):
    pai = {}
    cost = {}
    o = sorted(adj)[0]
    cost[o] = 0
    orla = {o}
    while orla:
        v = min(orla,key=lambda x:cost[x])
        orla.remove(v)
        for d in adj[v]:
            if d not in cost:
                orla.add(d)
                cost[d] = float("inf")
            if adj[v][d] < cost[d]:
                pai[d] = v
                cost[d] = adj[v][d]
    return pai

# Algoritmo de Floyd-Warshall
def fw(adj):
    dist = {}
    for o in adj:
        dist[o] = {}
        for d in adj:
            if o == d:
                dist[o][d] = 0
            elif d in adj[o]:
                dist[o][d] = adj[o][d]
            else:
                dist[o][d] = float("inf")
    for k in adj:
        for o in adj:
            for d in adj:
                if dist[o][k] + dist[k][d] < dist[o][d]:
                    dist[o][d] = dist[o][k] + dist[k][d]
    return dist