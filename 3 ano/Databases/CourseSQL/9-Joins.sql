-- What we are telling SQL to do is to combine the two tables based on the customer_id column.
SELECT transaction_id, amount, first_name, last_name FROM transactions
    INNER JOIN customers ON transactions.customer_id = customers.customer_id;
-- The INNER JOIN keyword selects records that have matching values in both tables.

-- The LEFT JOIN keyword returns all records from the left table (transactions), and the matched records from the right table (customers). The result is NULL from the right side, if there is no match.
SELECT transaction_id, amount, first_name, last_name FROM transactions
    LEFT JOIN customers ON transactions.customer_id = customers.customer_id;

-- The RIGHT JOIN keyword returns all records from the right table (customers), and the matched records from the left table (transactions). The result is NULL from the left side, when there is no match.
SELECT transaction_id, amount, first_name, last_name FROM transactions
    RIGHT JOIN customers ON transactions.customer_id = customers.customer_id;

