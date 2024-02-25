'''
Neste problema prentede-se que implemente uma função que calcula o rectângulo onde se movimenta um robot.

Inicialmente o robot encontra-se na posição (0,0) virado para cima e irá receber uma sequência de comandos numa string.
Existem quatro tipos de comandos que o robot reconhece:
  'A' - avançar na direcção para o qual está virado
  'E' - virar-se 90º para a esquerda
  'D' - virar-se 90º para a direita 
  'H' - parar e regressar à posição inicial virado para cima
  
Quando o robot recebe o comando 'H' devem ser guardadas as 4 coordenadas (minímo no eixo dos X, mínimo no eixo dos Y, máximo no eixo dos X, máximo no eixo dos Y) que definem o rectângulo 
onde se movimentou desde o início da sequência de comandos ou desde o último comando 'H'.

A função deve retornar a lista de todas os rectangulos (tuplos com 4 inteiros)
'''

def robot(comandos):
    res = []
    coord = [0,0]
    maxX = 0
    minX = 0
    maxY = 0
    minY = 0
    direction = 0 # [UP, RIGHT, DOWN, LEFT]
    for comando in comandos:
        if comando == 'D':
            direction = (direction + 1) % 4
        elif comando == 'E':
            direction = (direction - 1) % 4
        elif comando == 'H':
            coord = [0,0] 
            direction = 0
            res.append((minX,minY,maxX,maxY))
            minX = minY = maxY = maxX = 0
        elif comando == 'A':
            if direction == 0:
                coord[1] += 1
            elif direction == 1:
                coord[0] += 1
            elif direction == 2:
                coord[1] -= 1
            elif direction == 3:
                coord[0] -= 1
            
        maxX = max(maxX, coord[0])
        maxY = max(maxY, coord[1])
        minX = min(minX, coord[0])
        minY = min(minY, coord[1])
    
    return res