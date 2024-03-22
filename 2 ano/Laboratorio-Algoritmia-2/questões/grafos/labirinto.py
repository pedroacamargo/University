def bfs(adj, o, d):
    pai = {}
    vis = {o}
    queue = [o]
    while queue:
        v = queue.pop(0)
        if (d == v):
            return pai
        x, y = v
        for ponto in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            xx = x + ponto[0]
            yy = y + ponto[1]
            adjacente = (xx, yy)
            if adjacente not in vis and 0 <= xx < len(adj) and 0 <= yy < len(adj[0]) and adj[xx][yy] != "#":
                vis.add(adjacente)
                print(vis)
                pai[adjacente] = v
                queue.append(adjacente)
    return pai


def lista(dicionario, dest):
    direcoes = []
    atual = dest
    while atual in dicionario.keys():
        pai = dicionario[atual]
        if pai[0] == atual[0] and pai[1] < atual[1]:
            direcoes.append('E')
        elif pai[0] == atual[0] and pai[1] > atual[1]:
            direcoes.append('O')
        elif pai[0] > atual[0] and pai[1] == atual[1]:
            direcoes.append('N')
        elif pai[0] < atual[0] and pai[1] == atual[1]:
            direcoes.append('S')
        atual = pai
    return "".join(direcoes[::-1])


def caminho(mapa):
    o = (0, 0)
    d = (len(mapa)-1, len(mapa[0])-1)
    if o == d:
        return ""
    busca = bfs(mapa, o, d)
    resultado = lista(busca, d)
    return resultado


mapa = ["  ########",
        "# # #    #",
        "# # #### #",
        "# #      #",
        "# # # ####",
        "# # #    #",
        "#   # #  #",
        "##### ####",
        "#        #",
        "########  "]
print(caminho(mapa))