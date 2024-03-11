'''

Implemente uma função que calcula um dos caminhos mais curtos para atravessar
um labirinto. O mapa do labirinto é quadrado e representado por uma lista 
de strings, onde um ' ' representa um espaço vazio e um '#' um obstáculo.
O ponto de entrada é o canto superior esquerdo e o ponto de saída o canto
inferior direito. A função deve devolver uma string com as instruções para
atravesar o labirinto. As instruções podem ser 'N','S','E','O'.

'''

def isEmpty(x,y,mapa):
    if x > 0 and x < len(mapa[0]) and y > 0 and y < len(mapa):
        if mapa[y][x] == " ":
            return true
    return false


def caminho(mapa):
    if len(mapa) == 0 or len(mapa) == 1:
        return ""
    
    adj = {}
    adj[(0,0)] = set()
    
    width = len(mapa[0])
    height = len(mapa)
    
    
    x = 0
    y = 0
    print(adj)
    while (x,y) != (width, height):
        
        if isEmpty(x + 1, y, mapa):
            continue
        if isEmpty(x - 1, y, mapa):
            continue
        if isEmpty(x, y + 1, mapa):
            continue
        if isEmpty(x, y - 1, mapa):
            continue
            
        y += 1
        x += 1
    
    return "NSEO"
