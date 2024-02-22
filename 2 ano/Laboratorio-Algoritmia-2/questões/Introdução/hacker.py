"""
Um hacker teve acesso a um log de transações com cartões de
crédito. O log é uma lista de tuplos, cada um com os dados de uma transação,
nomedamente o cartão que foi usado, podendo alguns dos números estar
ocultados com um *, e o email do dono do cartão.

Pretende-se que implemente uma função que ajude o hacker a 
reconstruir os cartões de crédito, combinando os números que estão
visíveis em diferentes transações. Caso haja uma contradição nos números 
visíveis deve ser dada prioridade à transção mais recente, i.é, a que
aparece mais tarde no log.

A função deve devolver uma lista de tuplos, cada um com um cartão e um email,
dando prioridade aos cartões com mais digitos descobertos e, em caso de igualdade
neste critério, aos emails menores (em ordem lexicográfica).
"""

def hacker(log):
    emails = []
    res = []
    for info in log:
        actualEmail = info[1]
        if actualEmail not in emails:
            emails.append(actualEmail)
            password = [char for char in info[0]]
            
            for i in log:
                if i[1] == actualEmail:
                    actualPassword = [char for char in i[0]]
                    for index in range(0,len(password)):
                        if actualPassword[index] != '*':
                            password[index] = actualPassword[index]
                
                
                digits = 0
                for c in password:
                    if c != "*":
                        digits += 1
        
            
            passwordString = ""
            for char in password: passwordString += char
            
            res.append((passwordString, actualEmail, digits))
    
    res.sort(key=lambda x: (-x[2], x[1]))
    finalRes = [(i[0],i[1]) for i in res]
    
    return finalRes