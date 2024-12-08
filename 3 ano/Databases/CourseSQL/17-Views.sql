CREATE VIEW employee_attendance AS 
    SELECT first_name, last_name FROM employees;

SELECT * FROM employee_attendance;

DROP VIEW employee_attendance;

ALTER TABLE customers
    ADD COLUMN email VARCHAR(50);

UPDATE customers
    SET email = 'FFish@gmail.com'
    WHERE id = 1;

UPDATE customers
    SET email = 'ola@gmail.com'
    WHERE id = 2;

CREATE VIEW customer_emails AS
    SELECT email FROM customers;

SELECT * FROM customer_emails;

-- Views are virtual tables that are generated from a SELECT statement.

INSERT INTO customers (first_name, last_name, email) VALUES 
    ('John', 'Doe', 'hello@gmail.com');

SELECT * FROM customer_emails;

-- Views are not physical tables, they are virtual tables that are generated from a SELECT statement.