import ply.lex as lex

code = """
def fatorial(num):
    if num == 0:
        return 1
    else:
        return num * fatorial(num - 1)
"""

tokens = (
    'INT', 'RETURN', 'DEF', 'FUNC', 'NUMBER', 'IF', 'ELSE', 'VAR', 
    'WHILE', 'FOR', 'BREAK', 'CONTINUE', 'IN', 'AND', 'OR', 'NOT', 
    'TRUE', 'FALSE', 'NONE', 'CLASS', 'IMPORT', 'AS', 'FROM', 'WITH',
)

keywords = {
    'int': 'INT',
    'return': 'RETURN',
    'def': 'DEF',
    'if': 'IF',
    'else': 'ELSE',
    'while': 'WHILE',
    'for': 'FOR',
    'break': 'BREAK',
    'continue': 'CONTINUE',
    'in': 'IN',                                                                                                                                         
    'and': 'AND',
    'or': 'OR',
    'not': 'NOT',
    'True': 'TRUE',
    'False': 'FALSE',
    'None': 'NONE',
    'class': 'CLASS',
    'import': 'IMPORT',
    'as': 'AS',
    'from': 'FROM',
    'with': 'WITH',
}

literals = ['(', ')', ':', '=', '*', '+', '-', '/', '<', '>', '[', ']', '{', '}', ',', '.', ';']

t_ignore = ' \t\r\n'

t_NUMBER = r'\d+'

def t_FUNC(t):
    r'[A-Za-z_][A-Za-z0-9_]*'
    if t.value in keywords:
        t.type = keywords[t.value]  # Verifica se é uma palavra-chave
    else:
        next_char = t.lexer.lexdata[t.lexer.lexpos:t.lexer.lexpos+1]
        if next_char == '(':
            t.type = 'FUNC'  # Se for seguido de '(', é uma função
        else:
            t.type = 'VAR'  
    return t

def t_error(t):
    print(f'Illegal character: {t.value[0]}')
    t.lexer.skip(1)

anaLexer = lex.lex()


for linha in code.splitlines():
    anaLexer.input(linha)
    for terminal in anaLexer:
        print(terminal)