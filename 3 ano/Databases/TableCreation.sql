-- Creation of the database exame
CREATE DATABASE IF NOT EXISTS exame
    DEFAULT CHARACTER SET utf8
    DEFAULT COLLATE utf8_general_ci;

-- To drop a database, use the following command:
-- DROP DATABASE exame;

-- Use the database exame
USE exame;

-- Table creation
CREATE TABLE Agents (
    Agent_Id INT NOT NULL AUTO_INCREMENT,
    First_Name VARCHAR(50) NOT NULL,
    Last_Name VARCHAR(50) NOT NULL,
    PRIMARY KEY (Agent_Id)
);

-- There's 2 ways of assigning a foreign key:
CREATE TABLE Promotions (
    Promotion_Nr INT NOT NULL AUTO_INCREMENT,
    Description VARCHAR(255) NOT NULL,
    Initial_Date DATETIME,
    Final_Date DATETIME,
    Category_Id TINYINT UNSIGNED NOT NULL,
        PRIMARY KEY (Promotion_Nr),
        FOREIGN KEY (Category_Id)
            REFERENCES Category(Category_Id)  
);

CREATE TABLE Promotions (
    Promotion_Nr INT NOT NULL,
    Description VARCHAR(50) NOT NULL,
    Initial_Date DATETIME,
    Final_Date DATETIME,
    Category_Id TINYINT UNSIGNED NOT NULL,
        PRIMARY KEY (Promotion_Nr));
ALTER TABLE Promotions
    ADD CONSTRAINT fkPromotionsCategories
        FOREIGN KEY (Category_Id)
        REFERENCES Category(Category_Id);


-- Table creation with attributes restrictions
CREATE TABLE IF NOT EXISTS Producers (
    Producer_Id INT NOT NULL AUTO_INCREMENT,
    First_Name VARCHAR(30) NOT NULL,
    Last_Name VARCHAR(30) NOT NULL,
    Gender CHAR(1) NOT NULL CHECK (Gender IN ('M', 'F')), -- check constraint
    Country_Id SMALLINT UNSIGNED NULL,
    Date_Of_Birth DATE NULL,
    eMail VARCHAR(150) UNIQUE,
    Facebook VARCHAR(200) NULL,
    Instagram VARCHAR(200) NULL,
    Notes TEXT NULL,
        PRIMARY KEY (Producer_Id) ,
        FOREIGN KEY (Country_Id)
            REFERENCES Country (Country_Id)
);

CREATE TABLE IF NOT EXISTS ProducersFilms (
    Producer_Id INT NOT NULL,
    Film_Id SMALLINT UNSIGNED NOT NULL,
        PRIMARY KEY (Producer_Id, Film_Id),
        FOREIGN KEY (Producer_Id)
            REFERENCES Producers (Producer_Id),
        FOREIGN KEY (Film_Id)
            REFERENCES Film (Film_Id)
);

-- Tables Alteration
ALTER TABLE Agents
    ADD Business_Terms VARCHAR(250) NULL;

ALTER TABLE Producers
    ADD Royalties DECIMAL(10,2) NOT NULL DEFAULT 0
        AFTER Instagram,
    ADD Contract TEXT
        FIRST;

ALTER TABLE Producers
    DROP COLUMN Contract;

ALTER TABLE Producers
    MODIFY Contract VARCHAR(250) NOT NULL,
    MODIFY Date_Of_Birth DATE NULL AFTER Last_Name;

-- Table deletion
DROP TABLE ProducersFilms;
-- Simultaneous deletion of tables
DROP TABLE Producers, ProducersFilms;
-- Temporary table deletion
DROP TEMPORARY TABLE Producers;

-- Metadata queries
DESC Producers; -- Show the table structure
SHOW TABLES; -- Show the tables in the database

