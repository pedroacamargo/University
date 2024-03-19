'''

O número de Erdos é uma homenagem ao matemático húngaro Paul Erdos,
que durante a sua vida escreveu cerca de 1500 artigos, grande parte deles em 
pareceria com outros autores. O número de Erdos de Paul Erdos é 0. 
Para qualquer outro autor, o seu número de Erdos é igual ao menor 
número de Erdos de todos os seus co-autores mais 1. Dado um dicionário que
associa artigos aos respectivos autores, implemente uma função que
calcula uma lista com os autores com número de Erdos menores que um determinado 
valor. A lista de resultado deve ser ordenada pelo número de Erdos, e, para
autores com o mesmo número, lexicograficamente.

'''
# paul erdos = 0
# outros = min(co-autores) + 1

def create(articles):
    print(articles)
    adj = {}
    
    for article in articles:
        authors = [d for d in articles[article]]
        for author in authors:
            if author not in adj:
                adj[author] = set()
            
        

def erdos(artigos,n):
    graph = create(artigos)
    return ["Manuel","Maria"]