ALTER TABLE employees
    ADD COLUMN job VARCHAR(25) AFTER hourly_pay;

UPDATE employees
    SET job = 'manager'
    WHERE employee_id = 1;

UPDATE employees
    SET job = 'cashier'
    WHERE employee_id = 2;

UPDATE employees
    SET job = 'cook'
    WHERE employee_id = 3;

UPDATE employees
    SET job = 'cook'
    WHERE employee_id = 4;

UPDATE employees
    SET job = 'asst. manager'
    WHERE employee_id = 5;

UPDATE employees
    SET job = 'janitor'
    WHERE employee_id = 6;

SELECT * FROM employees
    WHERE hire_date < '2019-01-01' AND job = 'cook';

SELECT * FROM employees
    WHERE hire_date < '2019-01-01' AND job = 'cook' OR job = 'cashier';

SELECT * FROM employees
    WHERE NOT job = 'manager' AND NOT job = 'asst. manager';

SELECT * FROM employees
    WHERE job IN ('cook', 'cashier');

SELECT * FROM employees
    WHERE job NOT IN ('cook', 'cashier');

SELECT * FROM employees
    WHERE first_name LIKE 'J%';

SELECT * FROM employees
    WHERE first_name LIKE 'J%e';

SELECT * FROM employees
    WHERE hire_date BETWEEN '2019-01-01' AND '2019-12-31';

