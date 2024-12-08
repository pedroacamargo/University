----------------------------------------------- 1) -----------------------------------------------
--- Usualmente, um administrador de um sistema de bases de dados tem sob a sua alçada vários sistemas de bases
--- de dados. Indique duas atividades de gestão do sistema de bases de dados que ele pode realizar no seu
--- quotidiano profissional, indicando o objetivo de cada uma delas.

--- Resposta:
--- Uma das atividades que o administrador pode fazer é o backup dos dados diariamente e, caso for necessário,
--- o rollback do sistema de base de dados. Isso beneficia a segurança e a confiabilidade do sistema, caso algum
--- dado seja perdido, uma table seja apagada, ou todo o sistema fique corrompido, o administrador poderá uti-
--- lizar o backup que foi gerado previamente e fazer o rollback da base de dados.
--- Além disso, o administrador faz o monitoramento do desempenho do sistema, assim poderá saber e ajudar o cliente
--- informando onde melhorar, o que melhorar e qual o prejuízo que uma empresa tem de acordo com o desempenho do
--- sistema, se está sobrecarregado ou as queries não estão eficientes. O foco principal nessa atividade é otimizar
--- o uso dos recursos e reduzir o tempo de resposta da queries SQL.

----------------------------------------------- 2) -----------------------------------------------
--- Indique quais as etapas que integram o ciclo de vida do desenvolvimento de um sistema de bases de dados.
--- Caracterize-as de forma sumária.

--- Resposta:
--- O primeiro passo no ciclo de vida de um sistema de base de dados é a definição do sistema, nessa etapa é feita
--- a contextualização do problema que o sistema irá resolver, a fiabilidade e questões como "Por que?", "Como?",
--- "Quem?", "Em quanto tempo?". Após essa etapa, temos o levantamente de requisitos, após a contextualização do
--- problema temos que documentar tudo que será necessário para o desenvolvimento do sistema, de forma que mais
--- tarde nas próximas etapas já esteja tudo regulamentado e pronto para pôr em prática. A terceira etapa é a
--- Modelação Conceptual, que cria um modelo conceptual que representa a estrutura lógica dos dados levantados
--- na etapa anterior, como a criação de Entidades, seus atributos e suas relações. Logo após isso o desenvolvimento 
--- entra na Modelação Lógica, que transforma o modelo conceptual em um modelo lógico, definindo tabelas, o desenho
--- do modelo lógico, e sua normalização. Feita a modelação lógica, podemos implementar fisicamente o sistema de base
--- de dados, com a criação dos scripts de povoamento, criação das tabelas e suas relações, privilégios para usuários
--- e muitas outras coisas. Após a implementação física, a exploração do sistema começa, são feitos diversos testes
--- para testar a consistência, desempenho e funcionalidade, assegurando que atende aos requisitos levantados em
--- etapas anteriores. Por fim, a última etapa é a manutenção do sistema implementado junto com o monitoramento da
--- evolução, caso o cliente queira expandir mais ainda o sistema ou melhorá-lo de acordo com os dados recuperados
--- do monitoramento nessa mesma etapa.

----------------------------------------------- 3) -----------------------------------------------
--- RD1 – Um jogador é caracterizado por um número, nome, idade e uma lista de preferências de jogo.
--- RD2 – Uma equipa é caracterizada por um número, designação, localidade.
--- RD3 – Uma equipa tem um responsável técnico.
--- RD4 – Uma equipa é constituída por 6 jogadores.
--- RD5 – Um jogador apenas pode pertencer a uma equipa.

--- Considere os requisitos de descrição acima apresentados. Com base nesses requisitos desenvolva um esquema
--- concetual para uma base de dados capaz de acolher a informação que neles figura.

--- Resposta: Eu fiz um lógico ao invés de conceptual, o conceptual ta no papel

----------------------------------------------- 4) -----------------------------------------------
--- Num processo de desenvolvimento de uma base de dados relacional a identificação e a caracterização da chave
--- primária de cada uma das suas tabelas é um processo bastante importante, que deve ser realizado de forma
--- cuidada. Defina e caracterize o que é uma chave primária e revele como procederia para fazer a sua identificação
--- e consequente caracterização. Complemente a sua explicação com um pequeno exemplo.

--- Resposta:
--- Uma chave primária é um conjunto de um ou mais atributos em uma tabela, que identifica de forma única cada
--- registo. Elas devem ser únicas, não nulas, imutáveis (para nao causar inconsistências nas relações) e cada
--- tabela deve possuir somente uma chave. Para identificar uma chave primária, devemos primeiro analisar todos
--- os atributos que possuímos ao nosso dispor na entitade em causa, caso exista um atributo que é naturalmente
--- único, esse pode ser a chave primária, caso nenhum atributo isolado garanta unicidade, poderá ser escolhida
--- uma chave composta. Caso o atributo naturalmente único não seja adequado, poderá ser criado um atributo
--- adicional específicamente para a chave primária. A escolha da chave primária devera ser a mais conveniente
--- para uso, de menor tamanho, com menor probabilidade de perder sua unicidade no futuro, menos possibilidade
--- de ter os seus atributos modificados e o menor conjunto possível de atributos da tabela.
--- Exemplo: 

CREATE TABLE Cliente (
    id_cliente INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(100) NOT NULL,
    data_nascimento DATE,
    email VARCHAR(100) UNIQUE
);

--- Nesse caso, id_cliente será a chave primária e junto com ela existe o AUTO_INCREMENT, que assiste na unicidade
--- da chave, evitando que o usuário insira uma row na tabela com o mesmo id, assim o id será automatizado.

----------------------------------------------- 5) -----------------------------------------------
SELECT * FROM (
    SELECT DISTINCT Disciplina FROM Notas
        WHERE Aluno = 1
    UNION
    SELECT DISTINCT Disciplina FROM Notas
        WHERE Aluno = 2) AS A
    INNER JOIN Disciplinas AS D
        ON A.Disciplina=D.Id;

--- Considere a query SQL acima apresentada. Utilizando Álgebra Relacional, estabeleça uma expressão que
--- corresponda à query apresentada.

--- Resposta: Exams/imgs/22-23-Q5-AlgebraRelacional.png
--- A print é do chatGPT mas eu fiz a mão e ta aprovada por mim

----------------------------------------------- 6) -----------------------------------------------
--- Uma das “regras” de verificação da teoria da normalização é reconhecida como a terceira forma normal – 3FN. De
--- forma sucinta explique em que consiste, ilustrando a sua explicação com um pequeno exemplo prático de
--- aplicação.

--- Resposta:
--- A 3FN é uma das etapas de normalização projetada para eliminar dependências transitivas, ou seja, todo
--- atributo não-primário deve depender somente da chave primária e não de outro atributo não-primário.
--- Além disso, para um sistema de base de dados estar na 3FN, ele deverá atender aos critérios da 2FN.
--- Com a 3FN, reduzimos a redundância dos dados, evitamos anomalias de atualização (se o coordenador de
--- um curso mudar, basta atualizar a tabela Curso e não a tabela Aluno) e evitamos anomalias de inserção.

----------------------------------------------- 7) -----------------------------------------------
--- Considere o esquema lógico apresentado na Figura 1, relativo a uma base de dados para suporte a um sistema de
--- produção de artigos. Desenvolva em SQL as instruções necessárias para realizar as seguintes operações:

--- Fazer a criação das tabelas “Artigos” e “Componentes”
CREATE TABLE Artigos (
    Id INT NOT NULL PRIMARY KEY,
    Designação VARCHAR(100),
    Referência VARCHAR(55),
    Preço DECIMAL(8,2),
    Stock DECIMAL(8,2),
    Observações TEXT
);

CREATE TABLE Componentes (
    Artigo INT NOT NULL,
    Componente INT NOT NULL,
    Quantidade INT NOT NULL,
    PRIMARY KEY (Artigo, Componente),
    FOREIGN KEY Artigo REFERENCES Artigos(Id)
);

--- Inserir dois novos registos na tabela “Produção”.
INSERT INTO Produção VALUES 
    (1, 1, 1, 1, 1, 12.9),
    (1, 2, 1, 2, 2, 11.9);

--- Listar todos os registos da tabela “Produção” relativos às máquinas ‘1’ e ‘2’, que tenham realizado as
--- operações ‘O1’, ‘O2’ e ‘O3’.

--- Como O1, O2, O3 são designações das operações, temos q primeiro dar get da designação das operações
--- relacionadas com as máquinas 1 e 2, e depois fazer um SELECT com essas designações
SELECT * FROM (
        SELECT * FROM Produção AS P
            INNER JOIN Operações AS O ON P.Operação = O.Id
    )
    WHERE Máquina IN (1, 2) AND Designação IN ('O1', 'O2', 'O3');


--- Indicar qual foi o tempo médio que foi gasto na realização das operações necessárias para produzir os artigos
--- ‘1’ e ‘2’.
SELECT AVG(HorasOperação), Artigo FROM Produção
    WHERE Artigo IN (1, 2)
    GROUP BY Artigo;

--- Desenvolver um procedimento (stored procedure) que receba, como parâmetro de entrada o identificador de
--- um artigo e apresente a lista completa de todos os seus componentes.
DELIMITER $$
CREATE PROCEDURE componentes_por_artigo(
    IN in_id INT
)
BEGIN
    SELECT Artigos.Id, C.Componente, C.Quantidade FROM Artigos
        INNER JOIN Componentes AS C ON Artigos.Id = C.Artigo
        WHERE Artigos.Id = in_id;
END $$
DELIMITER;