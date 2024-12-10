----------------------------------------------- 1) -----------------------------------------------
--- Uma das etapas de um processo de desenvolvimento de uma base de dados relacional considera o
--- estabelecimento da chave primária de cada uma das suas tabelas. Porém, a sua definição nem sempre é
--- concretizada de forma correta, originando por vezes o aparecimento de super-chaves. Explique o que é uma
--- super-chave e indique uma possível razão para o seu aparecimento.

--- Resposta:
--- Uma super-chave é um conjunto de um ou mais atributos que identificam uma linha numa tabela de dados.
--- Embora todas as super chaves possam garantir a unicidade de uma linha, algumas vezes podem se tornar
--- redundantes, podendo incluir atributos desnecessários. As super-chaves podem aparecer quando existe
--- uma má normalização do sistema de base de dados ou ocorre uma escolha incorreta dos atributos de uma
--- chave, que embora únicos, não sejam necessários. Para evitar que uma super-chave apareça, o sistema
--- deve ser normalizado pelo menos até a terceira forma normal (3FN), que acaba com a redundância de
--- dados e a dependência transitiva.

----------------------------------------------- 2) -----------------------------------------------
--- Em que tipo de situações se utilizam processos de combinação de dados entre duas tabelas utilizando operações
--- de junção externa. Quais os tipos de junção externa é que existem.

--- Resposta:
--- Existem 3 tipos de outer join: LEFT, RIGHT, FULL. Utilizamos o OUTER JOIN para relacionar 2 tabelas entre
--- si de acordo com uma coluna, e retornar todas as linhas que estão relacionadas entre si. No caso do LEFT
--- OUTER JOIN, a tabela que irá ser retornada será a junção da tabela da esquerda com a direita e todos os
--- dados que não foram relacionados, irão ter como NULL os atributos da tabela da direita. Por exemplo:
--- Caso queiramos juntar a tabela da esquerda (produtos) e a da direita (operações), podemos utilizar
--- um LEFT OUTER JOIN para listar os produtos que possuem operações e os que não possuem operações (nesse
--- caso, os campos serão NULL).

----------------------------------------------- 4) -----------------------------------------------
--- Numa base de dados relacional a definição de chaves estrangeiras é uma ação bastante regular. Explique em que
--- consiste uma chave estrangeira e qual a sua utilidade.

--- Resposta:
--- Uma chave estrangeira identifica uma relação entre duas entidades (similares ou diferentes), a chave estrangeira
--- aponta para uma chave primária de outra entidade, podendo as relações serem de 1 para 1, 1 para N ou N para N.
--- Além disso, o atributo (ou atributos) da chave estrangeira não deve depender de nenhum atributo da tabela e vice-versa.
--- As chaves estrangeiras são úteis para a normalização de tabelas, bem como a relação entre 2 tabelas, garantir
--- a integridade referencial (assegurar que os valores em uma tabela estão consistentemente relacionados com os 
--- valores em outra tabela) além de facilitar o delete e update de dados no sistema.

----------------------------------------------- 6) -----------------------------------------------
--- A integridade dos dados de uma base de dados pode ser assegurada através da definição de um conjunto
--- específico de restrições. De forma sucinta, apresente e explique dois tipos dessas restrições.

--- Resposta:
--- As restrições ajudam a modelas os dados, garantidos que eles sejam válidos e consistentes. Uma das restrições é 
--- a restrição NOT NULL, que garante que uma coluna não seja nula, assegurando que as colunas tenham sempre um
--- valor válido. Outra restrição, por exemplo, é a restrição default, que garante que um atributo terá um valor
--- predefinido caso na inserção dessa linha na tabela, não seja designado algum valor, o que assegura, mais uma
--- vez, a integridade dos dados, evitando que essa coluna possua um valor NULL logo na criação da linha.

----------------------------------------------- 7) -----------------------------------------------
--- πnr,nome (Alunos) ∪ πnr,nome ((Alunos) ⨝nr=aluno (σnota≥18 (Notas)))

--- Considere a expressão em Álgebra Relacional cima apresentada. Utilizando a linguagem SQL, estabeleça uma
--- query correspondente à query apresentada
SELECT DISTINCT Alunos.nr, Alunos.nome FROM Alunos
UNION
SELECT DISTINCT Alunos.nr, Alunos.nome 
    FROM Alunos AS a
    INNER JOIN Notas AS n ON a.nr = n.aluno;
    WHERE n.nota >= 18;
 
----------------------------------------------- 9) -----------------------------------------------
--- Tendo em consideração o esquema lógico da base de dados apresentado na Figura 1, pretende-se que apresente
--- em SQL as instruções necessárias para realizar as seguintes operações:

--- acrescentar na tabela “Investigador” dois novos atributos, “DataNascimento” e “eMail”, caracterizando-os de
--- forma adequada;
ALTER TABLE Investigador 
    ADD DataNascimento DATE NOT NULL,
        eMail VARCHAR(100);


--- obter uma lista com os projetos que tenham um orçamento superior a ‘100.000,00’€, cujos investigadores
--- responsáveis sejam da categoria ‘A’;
SELECT * FROM Projeto AS p
    INNER JOIN Investigador AS i ON p.Id = i.Projeto
    WHERE i.Categoria = 'A' AND p.Orcamento > 100000;


--- criar uma vista que forneça uma lista com os nomes dos investigadores dos projetos, ordenada
--- decrescentemente por orçamento dos projetos;
CREATE VIEW q3 AS
    SELECT i.Nome, p.Orcamento FROM Investigador AS i
    INNER JOIN Projeto AS p ON i.Projeto = p.Id
    ORDER BY p.Orcamento DESC


--- remover da base de dados toda a informação relativa à tarefa ‘Limpeza de Microscópio’;
DELETE FROM InvestigadorTarefa
    WHERE Tarefa IN (SELECT Id FROM Tarefa WHERE Designacao = 'Limpeza de Microscópio');

DELETE FROM Tarefa
    WHERE Designacao = 'Limpeza de Microscópio';

--- desenvolver uma função que permita obter o tempo total relativo à realização das tarefas associadas com um
--- dado investigador.
CREATE FUNCTION tempo_total(
    IdInvestigador INT
) RETURNS INT AS 
BEGIN
    DECLARE TotalTempo INT;

    SELECT
        SUM(IT.Duracao) INTO TotalTempo FROM InvestigadorTarefa AS IT
        WHERE IT.Investigador = IdInvestigador;

    RETURN IFNULL(TotalTempo, 0);
END;

