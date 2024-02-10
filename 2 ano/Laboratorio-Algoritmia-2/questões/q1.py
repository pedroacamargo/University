def auxFunc(data):
    return data[1]
    
def aloca(prefs):
    
    d = list(prefs.items())
    d.sort(key=auxFunc)
    
    trash = []
    naoAlocados = []
    
    for student in d:

        for garbage in trash:
            if garbage in student[1]:
                student[1].remove(garbage)
        
        if student[1] == []:
            naoAlocados.append(student[0])
        elif student[1] != []:
            trash.append(int(student[1].pop(0)))
    
    return naoAlocados