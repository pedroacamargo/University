'''

Implemente uma função que calcula um dos caminhos mais curtos para atravessar
um labirinto. O mapa do labirinto é quadrado e representado por uma lista 
de strings, onde um ' ' representa um espaço vazio e um '#' um obstáculo.
O ponto de entrada é o canto superior esquerdo e o ponto de saída o canto
inferior direito. A função deve devolver uma string com as instruções para
atravesar o labirinto. As instruções podem ser 'N','S','E','O'.

'''

def isEmpty(x,y,mapa):
    if x >= 0 and x < len(mapa[0]) and y >= 0 and y < len(mapa):
        if mapa[y][x] == " ":
            return True
    return False


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
    visited = [(0,0)]
    queue = []
    
    
    while (x,y) != (width, height):
        
        if isEmpty(x + 1, y, mapa) and (x + 1, y) not in visited:
            queue.append((x+1,y, 'E'))   
            visited.append((x + 1,y))
        if isEmpty(x - 1, y, mapa) and (x - 1, y) not in visited:
            queue.append((x-1,y, 'O'))
            visited.append((x - 1,y))
        if isEmpty(x, y + 1, mapa) and (x, y + 1) not in visited:
            queue.append((x,y+1, 'S'))
            visited.append((x,y + 1))
        if isEmpty(x, y - 1, mapa) and (x, y - 1) not in visited:
            queue.append((x,y-1, 'N'))
            visited.append((x,y - 1))
        
        print(queue)
        print(x,y)
        element = queue.pop(0)
        if element[2] == 'E':
            if (x,y) in adj:
                adj[(x,y)].add((x + 1,y))
            else:
                adj[(x,y)] = set()
                adj[(x,y)].add((x + 1,y))
            
            adj[(x + 1, y)] = set()
            x = element[0]
            y = element[1]
        elif element[2] == 'O':
            if (x,y) in adj:
                adj[(x,y)].add((x - 1,y))
            else:
                adj[(x,y)] = set()
                adj[(x,y)].add((x - 1,y))
            
            #adj[(x,y)].add((x - 1,y))
            adj[(x - 1, y)] = set()
            x = element[0]
            y = element[1]
        elif element[2] == 'N':
            if (x,y) in adj:
                adj[(x,y)].add((x,y - 1))
            else:
                adj[(x,y)] = set()
                adj[(x,y)].add((x,y - 1))
                
            #adj[(x,y)].add((x,y - 1))
            adj[(x, y - 1)] = set()
            y = element[1]
            x = element[0]
        elif element[2] == 'S':
            if (x,y) in adj:
                adj[(x,y)].add((x,y + 1))
            else:
                adj[(x,y)] = set()
                adj[(x,y)].add((x,y + 1))
                
            #adj[(x,y)].add((x,y + 1))
            adj[(x, y + 1)] = set()
            y = element[1]
            x = element[0]
    
    print(queue)
    return "NSEO"



