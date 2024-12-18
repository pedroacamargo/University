
import ply.lex as lex
import sys

tokens = (
    'LPAREN',
    'RPAREN',
    'VIRG',
    'ID',
    'Nint',
    'Nreal',
    'IGUAL',
    'MAIS',
    'EXCL',
    'MENOS',
    'VEZES',
    'LISTAD',
    'LISTAE',
    'PONeVIR',
    'E'   
)

t_LPAREN = r'\('
t_RPAREN = r'\)'
t_VIRG   = r','
t_IGUAL  = r'='
t_MAIS = r'\+'
t_EXCL = r'!'
t_MENOS = r'-'
t_VEZES = r'\*'
t_PONeVIR = r';'
t_E = r'e'
t_LISTAD = r'\['
t_LISTAE = r'\]'
t_ID = r'[a-zA-Z]+'

def t_Nint(t):
    r'[0-9]+'
    t.value = int(t.value)
    return t
    
def t_Nreal(t):
    r'[0-9]+\.[0-9]+'
    t.value = float(t.value)
    return t
    
def t_Str(t):
    r'\"[^"]*\"'
    return t
    
t_ignore = ' \r\n\t'

def t_error(t):
    print('Illegal character: ' + t.value[0])
    t.lexer.skip(1)
    return

lexer = lex.lex() # cria um AnaLex especifico a partir da especificação acima usando o gerador 'lex' do objeto 'lex'

# Reading input
for linha in sys.stdin:
    lexer.input(linha) 
    tok = lexer.token()
    while tok:
        print(tok)
        tok = lexer.token()

