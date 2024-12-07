
-- ASC is the default order
SELECT * FROM employees
    ORDER BY first_name DESC;

SELECT * FROM employees
    ORDER BY hire_date ASC;

SELECT * FROM transactions
    ORDER BY amount DESC, customer_id;