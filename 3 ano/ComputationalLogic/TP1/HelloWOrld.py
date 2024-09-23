from pysmt.shortcuts import Symbol, LE, GE, Int, And, Equals, Plus, Solver, is_sat, get_model
from pysmt.typing import INT

hello = [Symbol(s, INT) for s in "hello"]
world = [Symbol(s, INT) for s in "world"]

letters = set(hello + world) # {h, e, l, o, w, r, d}

domains = And(And(LE(Int(1), l),
                  GE(Int(10), l)) for l in letters)

sum_hello = Plus(hello) # (h + e + l + l + o)
sum_world = Plus(world) # (w + o + r + l + d)

problem = And(
    Equals(sum_hello, sum_world),
    Equals(sum_hello, Int(25)),
) # (h + e + l + l + o = w + o + r + l + d) & (h + e + l + l + o = 25)

with Solver(name="z3") as solver:
    solver.add_assertion(domains)
    if not solver.solve():
        print("Domain is not SAT!!!")
        exit()
    solver.add_assertion(problem)
    if solver.solve():
        for l in letters:
            print("%s = %s" %(l, solver.get_value(l)))
    else:
        print("No solution found")