from random import randint
from tabulate import tabulate
from ortools.linear_solver import pywraplp

solver = pywraplp.Solver.CreateSolver('SCIP')

# d -> dias
# minTime -> tempo minimo
# maxTime -> tempo maximo
def createSlots(d, minTime, maxTime):
    slots = []
    for i in range(1, d + 1):
        for j in range(minTime, maxTime + 1):
            slots.append((i,j))
    return slots


# For each collaborator, we have to create a dictionary with the availability of each slot 
# 1 -> available
# 0 -> not available
def createColaboratorsAvailability(C, T):
    availability = {}
    for c in range(C):
        availability[c] = {}
        for t in T:
            availability[c][t] = randint(0,1)
    return availability


# For each project, we have to create a dictionary with the collaborators that are in the project
def createCollabsInProjectsDictionary(CP, C):
    projectsMap = {}
    for c in range(C):
        projectsMap[c] = {}

        for p in CP:
            if c in CP[p]:
                projectsMap[c][p] = 1
            else:
                projectsMap[c][p] = 0

    return projectsMap


def print_slots(slots):
    print(tabulate(slots, headers=['Day', 'Time'], tablefmt='orgtbl'))
    
def print_table(hMin, hMax, dMax, A, R):
    table = [[x] for x in range(hMin, hMax)]
    fst_line = ["Slots"]
    
    # Add days to the first line
    for slot in slots:
        if ("Dia " + str(slot[0])) not in fst_line:
            fst_line.append("Dia " + str(slot[0]))
    table.insert(0,fst_line)
    
    
    
    for d in range(0,dMax): # day
        for t in range(hMin, hMax): # time
            table[t+1-hMin].insert(d+1, "")

            for p in range(0, P): # project
                for s in range(0, S): # room

                    if int(A[p][s][(d+1,t)].solution_value()) == 1: # if there is a meeting
                        table[t+1-hMin][d+1] += ("\nProjeto: %i - Sala: %i\nCols: " % (p,s)) # add project and room
                        for c in range(0, C):
                            if int(R[c][p][s][(d+1,t)].solution_value()) == 1:
                                table[t+1-hMin][d+1] += f"{c} "                        
    print(tabulate(table))


def print_disponibilidade(disp, hMin, hMax, dMax):
    for c in disp:
        print('\nDisponibilidade do colaborador '+str(c))

        table = [[x] for x in range(hMin, hMax)]
        fst_line = ["Slots"]
        for slot in slots:
            if ("Dia " + str(slot[0])) not in fst_line:
                fst_line.append("Dia " + str(slot[0]))
        table.insert(0,fst_line)
        
        for d in range(0,dMax):
            for slot in range(hMin, hMax):
                table[slot+1-hMin].insert(d+1, "")
                if (disp[c][(d+1,slot)]) == 0:
                    table[slot+1-hMin][d+1] = "X"
        
        print(tabulate(table))

S = 4 # rooms number
P = 5 # projects number
C = 7 # collaborators number

# Collaborators in each project, {project: [collaborators]}
CP = {
    0: [0,1,2,3,6],
    1: [0,1,4,5],
    2: [2,3],
    3: [4,5,6],
    4: [1,3,4,5]
}

# Leader of each project, {project: collaborator}
LP = {
    0: 1,
    1: 4,
    2: 2,
    3: 5,
    4: 3
}


minTime = 9 # min time slot
maxTime = 19 # max time slot
days = 5 # days

slots = createSlots(days, minTime, maxTime) # slots
projects_in = createCollabsInProjectsDictionary(CP, C)
disp = createColaboratorsAvailability(C, slots)
reunioes_semanais = 10

print(slots)

print_disponibilidade(createColaboratorsAvailability(C,slots), minTime, maxTime, days)

# Matriz de alocação de reuniões
A = {}
for p in range(P):
    A[p] = {}
    for s in range(S):
        A[p][s] = {}
        for slot in slots:
            A[p][s][slot] = solver.BoolVar(f'A[{p}],[{s}],[{slot}]')


# Matriz de alocação de colaboradores a uma reunião
R = {}
for c in range(C):
    R[c] = {}
    for p in range(P):
        R[c][p] = {}
        for s in range(S):
            R[c][p][s] = {}
            for slot in slots:
                R[c][p][s][slot] = solver.BoolVar(f'R[{c},{p},{s},{slot}]')

# ----------------- Constraints -----------------
# 1 - Disponibilidade dos colaboradores
for c in range(C):
    for p in range(P):
        for s in range(S):
            for slot in slots:
                solver.Add( R[c][p][s][slot] <= disp[c][slot])
                
# 2 - Cada projeto tem x reuniões semanais
for p in range(P):
    solver.Add( sum(A[p][s][slot] for s in range(S) for slot in slots) >= reunioes_semanais)
    
# 3 - Não pode haver mais do que 1 reunião numa sala num slot
for s in range(S):
    for slot in slots:
        solver.Add( (sum(A[p][s][slot] for p in range(P))) <= 1)
        
# 4 - O colaborador só pode ir à reunião se tiver alocado ao projeto 
for p in range(P):
    for c in range(C):
        for s in range(S):
            for slot in slots:
                solver.Add( R[c][p][s][slot] <= A[p][s][slot] * projects_in[c][p])
                
# 5 - Um colaborador só pode estar em reunião se esta estiver marcada 
for slot in slots:
    for s in range(S):
        for p in range(P):
            for c in range(C):
                solver.Add( R[c][p][s][slot] <= A[p][s][slot])
                
# 6 - O Líder tem que ir a todas as reuniões do projeto no qual é líder
for p in range(P):
    for s in range(S):
        for slot in slots:
            solver.Add( R[LP[p]][p][s][slot] == A[p][s][slot] )
            
# 7 - A assiduidade a cada reunião tem de ser superior a 50%
for p in range(P):
    for s in range(S):
        for slot in slots:
            solver.Add((sum(R[c][p][s][slot] for c in range(C)) / len(CP[p])) >= 0.5*R[LP[p]][p][s][slot] )
            
# 8 - Um colaborador não pode estar em duas reuniões em simultâneo
for c in range(C):
    for slot in slots:
        solver.Add( (sum(R[c][p][s][slot] for s in range(S) for p in range(P))) <= 1)
        
# Maximizar o número de reuniões realizadas
solver.Maximize( sum(A[p][s][slot] for p in range(P) for s in range(S) for slot in slots) )

# Minimizar o número de reuniões por participante
for c in range(C):
    solver.Minimize(sum(R[c][p][s][slot] for p in range(P) for s in range(S) for slot in slots))

# ------------------------------------------------    
    
status = solver.Solve()

if status == pywraplp.Solver.OPTIMAL:
    print_table(slots[0][1], slots[-1][1] +1, days, A, R)
else:
    print("No solution found")


