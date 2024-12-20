# ------------------------------------------------------------
# calculador-yacc.py
#   
#   Este exemplo define uma Calculadora com base num Expressão Aritmética com os 
#   4 operadores básicos e operandos numéricos (sem variáveis)
#   A mesma GIC suporta 2 GTs:
#      (- uma que implementa uma calculadora: interpreta a frase de entrada e calcula logo, mostrando o resultado-)
#      - uma que implementa um compilador: reconhece um frase de entrada e gera código Assembly para posteriormente a VM fazer o calculo  
# ------------------------------------------------------------
import sys
import ply.yacc as yacc
from calculadora_lex_1 import tokens

def p_Calculadora(p):
    "Calc : Exp "
    #print('A Expressão introduzida vale: ' , p[1])
    print("START")
    print(p[1])
    print("WRITEI")
    print("STOP")
    
def p_Exp_add(p):
    "Exp : Exp '+' Term"
    #p[0] = p[1] + p[3]
    p[0] = p[1] + p[3] + r'ADD' + '\n'

def p_Exp_sub(p):
    "Exp : Exp '-' Term"
    #p[0] = p[1] - p[3]
    p[0] = p[1] + p[3] + r'SUB' + '\n'

def p_Exp_term(p):
    "Exp : Term"
    p[0] = p[1]

def p_Term_mul(p):
    "Term : Term '*' Factor"
    #p[0] = p[1] * p[3]
    p[0] = p[1] + p[3] + r'MUL' + '\n'

def p_Term_div(p):
    "Term : Term '/' Factor"
    #p[0] = p[1] / p[3]
    p[0] = p[1] + p[3] + r'DIV' + '\n'
 
def p_Term_factor(p):
    "Term : Factor"
    p[0] = p[1]

def p_Factor_number(p):
    "Factor : number"
    #p[0] = p[1]
    p[0] = r'PUSHI ' + str(p[1]) + '\n'

def p_Factor_group(p):
    "Factor : '(' Exp ')'"
    p[0] = p[2]

def p_error(p):
    print('Syntax error: ', p)
    parser.success = False

#inicio do Parser e Calculadora
parser = yacc.yacc()

for line in sys.stdin:
    parser.success = True
    result = parser.parse(line)
