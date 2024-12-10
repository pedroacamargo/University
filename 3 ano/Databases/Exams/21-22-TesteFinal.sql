----------------------------------------------- 3) -----------------------------------------------
--- Uma das “regras” de verificação da teoria da normalização é reconhecida como a segunda forma normal – 2FN.
--- De forma sucinta explique essa forma normal, ilustrando a sua explicação com um pequeno exemplo prático da
--- sua aplicação. Complemente a sua resposta indicando que tipos de anomalias podem surgir quando uma base de
--- dados não está na 2FN.

--- Resposta:
--- Primeiramente, para uma tabela estar na Segunda Forma Normal, a tabela deve estar na Primeira Forma Normal,
--- ou seja, não deve conter grupos repetidos ou atributos multivalorados. Além disso, todos os atributos que
--- não são chaves, devem depender totalmente da chave primária e não apenas de uma parte dela.

----------------------------------------------- 6) -----------------------------------------------
--- Considere o esquema lógico apresentado na Figura 1, relativo a uma base de dados de montagem de modelos de
--- brinquedos. Desenvolva em SQL as instruções necessárias para realizar as seguintes operações:

--- Fazer a criação das tabelas “Modelos”, “ModelosPeças” e “Peças”.
CREATE TABLE Modelos (
    idModelo INT NOT NULL AUTO_INCREMENT,
    Designação VARCHAR(100) NOT NULL,
    Custo DECIMAL(8,2),
    TempoMontagem DECIMAL(8,2),
    Observações TEXT
    PRIMARY KEY(idModelo)
);

CREATE TABLE Peças (
    IdPeça INT NOT NULL,
    Cor VARCHAR(50) NOT NULL,
    Tipo INT NOT NULL,
    Imagem VARCHAR(150),
    PRIMARY KEY(IdPeça)
);

CREATE TABLE ModelosPeças (
    idModelo INT NOT NULL,
    IdPeça INT NOT NULL,
    NrPeças INT NOT NULL,
    PRIMARY KEY(idModelo, IdPeça),
    FOREIGN KEY (idModelo) REFERENCES Modelos(IdModelo),
    FOREIGN KEY (IdPeças) REFERENCES Peças(IdPeça)
);

--- Desenvolver um script que insira um registo na tabela “ModelosPeças”, bem como a informação
--- requerida para a operação de inserção ser realizada com sucesso.
INSERT INTO ModelosPeças VALUES
    (1, 1, 10),
    (1, 2, 5),
    (1, 3, 9);

--- Remover da tabela “Passos” todos os registos que foram guardados para modelos (“Modelos”) com um
--- tempo de montagem (“TempoMontagem”) inferior a 2 minutos.
DELETE FROM Passos 
    WHERE IdModelo IN (
        SELECT IdModelo FROM Modelos
        WHERE TempoMontagem < 2
    );

--- Criar uma vista (view) que disponibilize informação de todos os modelos registados na base de dados,
--- agrupados por “Custo” e ordenados por “Tempo de montagem”.
CREATE VIEW modelos_custo AS
    SELECT * FROM Modelos
    GROUP BY Custo
    ORDER BY TempoMontagem ASC;

--- Desenvolver um procedimento (stored procedure) que receba, como parâmetro de entrada o
--- identificador de um modelo e apresente uma lista com todas as peças (“Id”, “Cor” e “Tipo”) que esse
--- modelo considera na sua montagem.
DELIMITER $$
CREATE PROCEDURE list_pieces(
    IN in_idModelo INT
)
BEGIN
    SELECT MP.idModelo, P.Cor, P.Tipo FROM ModelosPeças AS MP
    INNER JOIN Peças AS P ON MP.IdPeça = P.idPeça
    WHERE MP.IdModelo = in_idModelo;
END $$
DELIMITER;