import ply.lex as lex
import sys

literals = [';']

tokens = (
    'INT',
    'ISBN',
    'TEXTO'
)

def t_TEXTO(t):
    r'\"[^"]*\"'
    return t

def t_ISBN(t):
    r'\d{4}\-\d{3}\/\d{3}'
    return t  
    
def t_INT(t):
    r'\d{4}'
    return t
    
t_ignore = ' \n\t'

def t_error(t):
    print('Illegal character: ', t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()

# Reading input
for linha in sys.stdin:
    lexer.input(linha) 
    for tok in lexer:
        print(tok)
