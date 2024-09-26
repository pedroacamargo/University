from pysmt.shortcuts import BOOL, EqualsOrIff, Implies, get_model, Symbol, Solver, Not, And, Or

properties = [Symbol(p, BOOL) for p in ["mythical", "immortal", "mammal", "horned", "magical"]]

def get_premises():
    One = Implies(properties[0], properties[1])
    Two = Implies(Not(properties[0]), And(Not(properties[1]), properties[2]))
    Three = Implies(Or(properties[1], properties[2]), properties[3])
    Four = EqualsOrIff(properties[3], properties[4])
    premises = [One, Two, Three, Four]
    return premises

def is_implied(solver, prop):
    solver.push()
    solver.add_assertion(Not(prop))
    if solver.solve():
        print(f"The premises do not imply that unicorns are {prop}.")
    else:
        print(f"The premises imply that unicorns are {prop}.")
    solver.pop()
    

with Solver(name="z3") as solver:
    ps = get_premises()
    for p in ps:
        solver.add_assertion(p)
    for i in [0,3,4]:
        is_implied(solver, properties[i])