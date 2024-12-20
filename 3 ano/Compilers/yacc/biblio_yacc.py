#Reconhecedor de Bibliografia simples
#Frase Exemplo:
'''
 "maias" "eça de queirós" 1890 1234-123/456.
 "cidade e as serras" "eça de queirós" 1899 1234-456/789.
 "amor de perdição"
              "camilo castelo branco"
                          1888
                                7890-987/654.
'''

import ply.yacc as yacc
import sys

from biblio_lex import tokens

def p_biblio_grammar(p):
    """
    Biblio : Livros
    Livros : Livro '.'
           | Livros Livro '.'
    Livro  : Titulo Autor Ano ISBN '!'
    Titulo : TEXTO
    Autor  : TEXTO
    Ano    : INT
    """
# T ={ INT, TEXTO, ISBN, '!' }
# NT ={ Biblio(S), Livros, Livro, Titulo, Autor, Ano }    
def p_error(p):
    print("Erro Sintático! Reescreva a frase")
    parser.exito = False

parser = yacc.yacc()
parser.exito = True

fonte = ""
for linha in sys.stdin:
    fonte += linha
    parser.parse(fonte)


if parser.exito:
    print ("Parsing teminou com sucesso!")
