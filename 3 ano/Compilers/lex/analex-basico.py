import ply.lex as lex
import sys

## Analisador Léxico para alguns dos símbolos terminias usados 
### num Ling.Programação tipo Python
###  a = X + Yvar;
     #6 Tokens, 2 Identificadores , 0 Palavras Reservadas, 1 Inteiro, 2 Sinais. 1 erro)
###  if ( xyz == 12 ): print( xyz/4 , a )
     #16 Tokens, 4 Identificadores , 1 Palavras Reservadas, 2 Inteiro, 9 Sinais)
###  lst = [ 1, 2, 3 ,4]
###   if a: print else a = *3+-4.5 6.7 9 

tokens = (
    'LPAREN',
    'RPAREN',
    'VIRG',
    'IGUAL',
    'MAIS',
    'MENOS',
    'DIV',
    'VEZES',
    'LISTAD',
    'LISTAE',
    'DOISpt',
    'IF', 
    'ELSE', 
    'ID',
    'Nint',
    'Nreal'
)

t_LPAREN = r'\('
t_RPAREN = r'\)'
t_LISTAD = r'\['
t_LISTAE = r'\]'
t_VIRG   = r'\,'
t_DOISpt = r'\:'
t_IGUAL  = r'\='
t_MAIS   = r'\+'
t_DIV    = r'\/'
t_MENOS  = r'\-'
t_VEZES  = r'\*'

def t_Nreal(t):
    r'[0-9]+\.[0-9]+'
    t.value = float(t.value)
    return t
def t_Nint(t):
    r'[0-9]+'
    lexer.soma += int(t.value)
    t.value = int(t.value)
    return t
    
def t_IF(t):
    r'(?i:if)'
    lexer.contaSE += 1  # Ação Semântica associada à ER
    return t

def t_ELSE(t):
    r'(?i:else)'
    lexer.contaSE -= 1  # Ação Semântica associada à ER
    return t
     
def t_ID(t):
    r'[a-zA-Z]+'
    lexer.conta += 1  # Ação Semântica associada à ER
    return t
    
t_ignore = ' \r\n\t'

def t_error(t):
    print('Illegal character: ' + t.value[0])
    t.lexer.skip(1)
    return


lexer = lex.lex() # cria um AnaLex especifico a partir da especificação acima usando o gerador 'lex' do objeto 'lex'


# Reading input
for linha in sys.stdin:
    lexer.conta = 0
    lexer.contaSE = 0
    lexer.soma  = 0
    lexer.input(linha) 
    simb = lexer.token()
    while simb:
        print(simb)
        simb = lexer.token()
    print("Numero de IDs ---",lexer.conta)
    print("Soma dos inteiros ---",lexer.soma)
    if (lexer.contaSE):
        print("possível ERRO pois o número de IF e ELSE não condiz")
        

