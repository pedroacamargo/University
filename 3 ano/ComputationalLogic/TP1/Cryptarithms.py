# completar
from pysmt.shortcuts import Symbol, LE, GE, Int, And, Equals, Plus, Solver, Times, AllDifferent
from pysmt.typing import INT

two = [Symbol(s, INT) for s in "two"]
four = [Symbol(s, INT) for s in "four"]

letters = set(two + four)

range = And([LE(Int(0), l) for l in letters] + [LE(l, Int(9)) for l in letters])

words = [two, four]
nonzero = And([Not(Equals(word[0], Int(0))) for word in words])

domain = And(range,nonzero)

def word_eval(word):
    total_value = Int(0)
    for i, c in enumerate(word[::-1]):
        factor = int(10**i)
        factor = Int(factor)
        char_value = Times(factor, c)
        total_value += char_value
    
    return total_value

with Solver(logic="QF_LIA") as solver:
    solver.add_assertion(domain)
    solver.add_assertion(AllDifferent(letters))
    if not solver.solve():
        print("Domain is not SAT!!!")
        exit()
        
    LHS = Times(word_eval(two), Int(2))
    RHS = word_eval(four)
    solver.add_assertion(Equals(LHS, RHS))
    
    if solver.solve():
        for l in letters:
            print("%s = %s" %(l, solver.get_value(l)))
    else:
        print("No solution found")
    