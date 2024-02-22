"""

Implemente uma função que calcula o horário de uma turma de alunos.
A função recebe dois dicionários, o primeiro associa a cada UC o
respectivo horário (um triplo com dia da semana, hora de início e
duração) e o segundo associa a cada aluno o conjunto das UCs em
que está inscrito. A função deve devolver uma lista com os alunos que
conseguem frequentar todas as UCs em que estão inscritos, indicando
para cada um desses alunos o respecto número e o número total de horas
semanais de aulas. Esta lista deve estar ordenada por ordem decrescente
de horas e, para horas idênticas, por ordem crescente de número.

"""
# uc: (diaDaSemana, inicio, duração)
# aluno: { string, string, string }

def isBetween(uc, uc2):
    res = False
    for ucHistory in uc2:
        startTime = ucHistory[0]
        endTime = ucHistory[1]
        
        ucStartTime = uc[1]
        ucEndTime = uc[1] + uc[2]
        
        if ucStartTime >= startTime and ucStartTime < endTime:
            return True
    
        for i in range(1, ucEndTime - ucStartTime + 1):
            if ucStartTime + i >= startTime and ucStartTime + i < endTime:
                return True
            
    

def horario(ucs,alunos):
    givenUcs = [uc for uc in ucs]
    print(ucs)
    print(alunos)
    
    res = []
    
    for aluno in alunos:
        scheduleOverwrite = False
        enrolledUcs = alunos[aluno]
        incorrectUc = False
        
        for uc in enrolledUcs:
            if uc not in givenUcs:
                incorrectUc = True
        
        if incorrectUc == True:
            continue
        
        ucsInfo = [ucs[uc] for uc in enrolledUcs if uc in givenUcs]
        
        sumTime = 0
        weekDays = {
            
        }
        
        for uc in ucsInfo:
            if uc[0] not in weekDays:
                weekDays[uc[0]] = [(uc[1], uc[1] + uc[2])]
            else:
                if(isBetween(uc, weekDays[uc[0]])):
                    scheduleOverwrite = True
                    break
                else:
                    weekDays[uc[0]].append((uc[1],uc[1] + uc[2]))
    
        
        if scheduleOverwrite == False:
            
            for data in weekDays:
                time = weekDays[data]
                for h in time:
                    sumTime += h[1] - h[0]
                    
            res.append((aluno, sumTime))
        
            
            
    res.sort(key=lambda x: (-x[1],x[0]))
    
    return res