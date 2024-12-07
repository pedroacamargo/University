SELECT * FROM income 
UNION
SELECT * FROM expenses;

-- In order to union two tables, the tables must have the same number of columns and the columns must have the same data types.
SELECT first_name, last_name FROM employees
UNION
SELECT first_name, last_name FROM customers;

-- The UNION operator selects only distinct values by default. To allow duplicate values, use UNION ALL.

SELECT first_name, last_name FROM employees
UNION ALL
SELECT first_name, last_name FROM customers;

-- The number of columns and the data types of the columns must be the same in all SELECT statements.
SELECT first_name, last_name FROM employees
UNION
SELECT first_name FROM customers;
