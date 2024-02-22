'''
Implemente uma função que calcula a tabela classificativa de um campeonato de
futebol. A função recebe uma lista de resultados de jogos (tuplo com os nomes das
equipas e os respectivos golos) e deve devolver a tabela classificativa (lista com 
as equipas e respectivos pontos), ordenada decrescentemente pelos pontos. Em
caso de empate neste critério, deve ser usada a diferença entre o número total
de golos marcados e sofridos para desempatar, e, se persistir o empate, o nome
da equipa.
'''

def tabela(jogos):
    res = []
    
    # [name,goals,points]
    teams = []
    tabela = []
    
    for jogo in jogos:
        # (name, goals, points)
        firstTeam = {"name": jogo[0], "goals": jogo[1], "points": 0, "against": jogo[3]}
        secondTeam = {"name": jogo[2], "goals": jogo[3], "points": 0, "against": jogo[1]}
        
        if firstTeam["goals"] > secondTeam["goals"]:
            firstTeam["points"] = 3
        elif firstTeam["goals"] < secondTeam["goals"]:
            secondTeam["points"] = 3
        else:
            firstTeam["points"] = 1
            secondTeam["points"] = 1
        
        
        indexFirstTeam = 0
        if firstTeam["name"] not in teams:
            teams.append(firstTeam["name"])
            tabela.append([firstTeam["name"],firstTeam["goals"] - secondTeam["goals"], firstTeam["points"]])
        else:
            for i in tabela:
                if i[0] == firstTeam["name"]: 
                    break
                else:
                    indexFirstTeam += 1
            
            tabela[indexFirstTeam][1] += (firstTeam["goals"] - secondTeam["goals"])
            tabela[indexFirstTeam][2] += firstTeam["points"]
        
            
        indexSecondTeam = 0
        if secondTeam["name"] not in teams:
            teams.append(secondTeam["name"])
            tabela.append([secondTeam["name"],secondTeam["goals"] - firstTeam["goals"], secondTeam["points"]])
        else:
            for i in tabela:
                if i[0] == secondTeam["name"]: 
                    break
                else:
                    indexSecondTeam += 1
            
            tabela[indexSecondTeam][1] += (secondTeam["goals"] - firstTeam["goals"])
            tabela[indexSecondTeam][2] += secondTeam["points"]
            
    
    tabela.sort(key=lambda x: (-x[2], -x[1], x[0]))
    for i in tabela:
        res.append((i[0],i[2]))
        
    return res