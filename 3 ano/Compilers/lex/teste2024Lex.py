import ply.lex as lex
import sys

tokens = ( 
            'NUM',
            'OPEN_BRACES',
            'CLOSE_BRACES',
            'DOT',
            'SEMI_COLON'
        )

t_DOT = r'\.'
t_ignore = ' \n\t\r' 

def t_SEMI_COLON(t):
    r';'
    t.lexer.semi_colon -= 1
    return t

def t_NUM(t):
    r'\d+\.?\d*'
    t.lexer.numbers -= 1
    return t

def t_OPEN_BRACES(t):
    r'\['
    t.lexer.colon += 1
    t.lexer.numbers += 2
    t.lexer.semi_colon += 1
    return t

def t_CLOSE_BRACES(t):
    r'\]'
    t.lexer.colon -= 1
    return t

def t_error(t):
    print('Illegal character: ' + t.value[0])
    t.lexer.skip(1)
    return

lexer = lex.lex()

for linha in sys.stdin:
    lexer.colon = 0
    lexer.numbers = 0
    lexer.semi_colon = 0
    lexer.input(linha)
    for tok in lexer:
        print(tok)
    if lexer.semi_colon != 0:
        print('Error: missing semi-colon')
        sys.exit(1)
    if lexer.numbers != 0:
        print('Error: missing numbers in brackets')
        sys.exit(1)
    if lexer.colon != 0:
        print('Error: missing brackets')
        sys.exit(1)
