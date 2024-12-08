SELECT * FROM transactions;

SELECT SUM(amount), order_date FROM transactions
    GROUP BY order_date;

SELECT MAX(amount), order_date FROM transactions
    GROUP BY order_date;

SELECT AVG(amount), order_date FROM transactions
    GROUP BY order_date;

SELECT COUNT(amount), order_date FROM transactions
    GROUP BY order_date;

SELECT SUM(amount), customer_id FROM transactions
    GROUP BY customer_id;


--- HAVING is the same as WHERE, but it is used with GROUP BY
SELECT SUM(amount), order_date FROM transactions
    GROUP BY order_date
        HAVING SUM(amount) > 1000 AND customer_id IS NOT NULL;

--- GROUP BY will aggregate all rows by a specific column
--- often used with aggregate functions like SUM, COUNT, AVG, MAX, MIN