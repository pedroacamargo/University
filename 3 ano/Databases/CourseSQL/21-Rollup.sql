SELECT SUM(amount), order_date FROM transactions
    GROUP BY order_date WITH ROLLUP;

SELECT COUNT(transaction_id), order_date FROM transactions
    GROUP BY order_date WITH ROLLUP;

SELECT COUNT(transaction_id) AS "# of orders", customer_id FROM transactions
    GROUP BY order_date WITH ROLLUP;

SELECT SUM(hourly_pay) AS "Total payroll", job FROM employees
    GROUP BY job WITH ROLLUP;

--- ROLLUP will add subtotals to the result set