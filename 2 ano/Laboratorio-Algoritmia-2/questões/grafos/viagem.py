'''
Implemente uma função que calcula o preço mais barato para fazer uma viagem de
autocarro entre duas cidades. A função recebe (para além das duas cidades) uma
lista de rotas de autocarro, onde cada rota é uma sequência de cidades por onde
passa o autocarro, intercalada com o custo para viajar entre cada par de cidades.
Assuma que cada rota funciona nos dois sentidos.
'''

def dijkstra(adj,o):
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
                dist[d] = dist[v] + adj[v][d]
    return dist

def create(rotas):
    adj = {}
    
    dest = ""
    origin = ""
    cost = 0
    
    for i in range(0,(len(rotas))):
        for j in range(0,(len(rotas[i]) - 2),2):
            origin = rotas[i][j]
            cost = rotas[i][j+1]
            dest = rotas[i][j+2]
            if origin not in adj:
                adj[origin] = {}
            if dest not in adj:
                adj[dest] = {}
            adj[origin][dest] = cost
            adj[dest][origin] = cost
        
    return adj


def viagem(rotas,o,d):
    if o == d:
        return 0
    
    graph = create(rotas)
    print(graph)
    res = dijkstra(graph,o)
    print(res)
    
    return res[d]