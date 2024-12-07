
-- % is a wildcard character that matches zero or more characters
SELECT * FROM employees
    WHERE first_name LIKE 'J%';

SELECT * FROM employees
    WHERE first_name LIKE '%e';

-- _ is a wildcard character that matches exactly one character
SELECT * FROM employees
    WHERE first_name LIKE 'J_ne';

SELECT * FROM employees
    WHERE hire_date LIKE '____-01-__';

