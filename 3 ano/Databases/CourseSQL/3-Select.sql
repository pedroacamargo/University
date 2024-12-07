SELECT * FROM employees;
SELECT first_name, last_name FROM employees;

-- This will return all the employees with an hourly pay greater or equal than 20
SELECT * FROM employees
    WHERE hourly_pay >= 20;

SELECT * FROM employees
    WHERE hire_date IS NULL;
SELECT * FROM employees
    WHERE hire_date IS NOT NULL;

