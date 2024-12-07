-- This will return the count of the amount column in the transactions table
SELECT COUNT(amount) AS count  FROM transactions;

-- This will return the maximum value of the amount column in the transactions table
SELECT MAX(amount) AS max FROM transactions;

SELECT AVG(amount) AS avg FROM transactions;

SELECT SUM(amount) AS sum FROM transactions;

SELECT CONCAT(first_name, " ", last_name) AS full_name FROM employees;

SELECT UPPER(first_name) AS upper_case FROM employees;

SELECT LOWER(first_name) AS lower_case FROM employees;

SELECT LENGTH(first_name) AS length FROM employees;
