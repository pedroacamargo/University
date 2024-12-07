-- Inserting data into Producers table
INSERT INTO Producers (Producer_Id, First_Name, Last_Name, Gender, Country_Id,Date_Of_Birth, eMail, Facebook, Instagram, Notes) VALUES
    ('21','Jonh','Well-Done','M','103','1978-01-01','jonhw@email.com',NULL,NULL,NULL);

-- Inserting data into Producers without all the columns
INSERT INTO Producers (Producer_Id, First_Name, Last_Name, Gender) VALUES
    ('22','Anne','Carson','F');

INSERT INTO Agents VALUES
    ('1','Mary','Smith-James',NULL);

INSERT INTO Agents (Agent_Id, First_Name, Last_Name) VALUES
    ('2','Ralf','Spencer'),
    ('3','Anne','Lopez'),
    ('4','Joseph','Pane');

