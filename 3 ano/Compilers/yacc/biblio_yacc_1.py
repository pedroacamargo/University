#Reconhecedor de Bibliografia simples
#Frase Exemplo:
'''
 "maias" "eça de queirós" 1890 1234-123/456.
 "cidade e as serras" "eça de queirós" 1899 1234-456/789.
 "amor de perdição"
              "camilo castelo branco"
                          1888
                                7890-987/654.
"tudo o que sei aprendi no jardim de infância" "Robert Fulgham"
               1985  1234-567/890.
'''

import ply.yacc as yacc
import sys

from biblio_lex import tokens

def p_biblio(p):
    "Biblio : Livros"
    print("Total de livros: ", parser.counter)
    print("Autores: ", parser.autores)
    print("Livros por autor: ", parser.livroAutor)
       
def p_livros1(p):   
    "Livros : Livro"
    parser.counter = 1
    
def p_livros2(p):
    "Livros : Livros Livro"
    parser.counter += 1
    
def p_livro(p):
    "Livro  : Titulo Autor Ano ISBN '.'"
    #parser.counter += 1
    parser.livroAutor[p[2]] = parser.livroAutor.setdefault(p[2], 0) + 1
    
def p_titulo(p):    
    "Titulo : TEXTO"
    
def p_autor(p):
    "Autor  : TEXTO"
    p[0] = p[1]
    parser.autores.add(p[1])
    print(p[1])
    
def p_ano(p):    
    "Ano    : INT"
    
    
# T ={ INT, TEXTO, ISBN, '.' }
# NT ={ Biblio(S), Livros, Livro, Titulo, Autor, Ano }    
def p_error(p):
    print("Erro Sintático! Reescreva a frase")
    parser.exito = False

parser = yacc.yacc()
parser.exito = True
parser.counter = 0
parser.autores = set()
parser.livroAutor = {}

fonte = ""
for linha in sys.stdin:
    fonte = linha
    parser.parse(fonte)


if parser.exito:
    print ("Parsing terminou com sucesso!")
