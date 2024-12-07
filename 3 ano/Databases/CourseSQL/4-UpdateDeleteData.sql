UPDATE employees
    SET hourly_pay = 10.25
    WHERE employee_id = 1;

UPDATE employees
    SET hourly_pay = 10.25,
        hire_date = NULL
    WHERE employee_id = 1;

-- This will update all the rows in the employees table
UPDATE employees
    SET hourly_pay = 10.25,
        hire_date = NULL

DELETE FROM employees
    WHERE employee_id = 1;