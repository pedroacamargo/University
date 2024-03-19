'''
Podemos usar um (multi) grafo para representar um mapa de uma cidade: 
cada nó representa um cruzamento e cada aresta uma rua.
Pretende-se que implemente uma função que calcula o tamanho de uma cidade, 
sendo esse tamanho a distância entre os seus cruzamentos mais afastados.
A entrada consistirá numa lista de nomes de ruas (podendo assumir que os 
nomes de ruas são únicos). Os identificadores dos cruzamentos correspondem a 
letras do alfabeto, e cada rua começa (e acaba) no cruzamento 
identificado pelo primeiro (e último) caracter do respectivo nome.
'''

# no cruzamento
# aresta rua
# tamanho de uma cidade -> distancia entre os cruzamentos mais afastados
# cruzamentos -> letras do alfabeto
# abc -> a ---------- c

# {'l': {'c': 7, 'e': 9}, 'o': {'r': 4, 'a': 4, 's': 5}, 'e': {'l': 9, 's': 10}, 
#'s': {'r': 9, 'c': 5, 'o': 5, 'e': 10, 's': 11}, 'r': {'o': 4, 's': 9}, 'c': {'l': 7, 's': 5},
#'t': {'a': 4}, 'a': {'t': 4, 'o': 4}
#}
# {'t': 23, 'r': 19, 's': 10, 'o': 15, 'l': 9, 'e': 0, 'c': 16, 'a': 19} -> Dijkstra

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
    return dist

def create(ruas):
    retorno = {}
    for x in ruas:
        if ((x[0], x[-1]) not in retorno.keys()):
            retorno[(x[0], x[-1])] = len(x)
    final = []
    
    for x in retorno:
        final.append((x[0], x[1], retorno[x]))
    return final
    
def transform(tuples):
    adj = {}
    
    for origin,destination,weight in tuples:
        if origin not in adj:
            adj[origin] = {}
        if destination not in adj:
            adj[destination] = {}
            
        adj[origin][destination] = weight
        adj[destination][origin] = weight
    
    return adj

def getCitySize(adj):
    maxRes = 0
    for dot in adj:
        data = dijkstra(adj,dot)
        maxLoop = max(data.values())
        maxRes = max(maxRes,maxLoop)
    
    return maxRes


def tamanho(ruas):
    # I will get the first letter, last letter and word's len
    tripleTupleArray = create(ruas)
    
    # Then create the graph
    transformTupleToGraphData = transform(tripleTupleArray)
    
    # Get the city size
    calculateDistanceData = getCitySize(transformTupleToGraphData)
    
    
    
    return calculateDistanceData
