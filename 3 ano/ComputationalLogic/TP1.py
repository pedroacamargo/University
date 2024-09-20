from pysmt.shortcuts import Symbol, And, Not, is_sat, get_model, LE, GE, GT, Int
from pysmt.typing import INT

# varA = Symbol("A")
# varB = Symbol("B")
# f = And(varA, Not(varB))

#print(f) # Prints: (A & (! B))
#print(is_sat(f, solver_name="z3")) # Prints: True
# print(f"Model: \n{get_model(f)} \nFunction: {f}")

# ------------------------------------------------------------------------------------------------------------------------

x = Symbol("x", INT)
y = Symbol("y", INT)

# formula = And(1<=x , x<=10 , 1<=y , y<=10 , x+y>10 , x-y<=5)
formula = And(
              LE(Int(1),x), 
              GE(Int(10),x),
              LE(Int(1),y),
              GT(x+y,Int(10)),
              LE(x-y,Int(5))
             )

print(f"Formula: {formula} \nIs SAT: {is_sat(formula, solver_name='z3')} \n{get_model(formula)}")
