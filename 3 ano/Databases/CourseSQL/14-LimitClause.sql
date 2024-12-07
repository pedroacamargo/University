SELECT * FROM customers
    ORDER BY last_name DESC LIMIT 5;

SELECT * FROM customers
    ORDER BY last_name DESC LIMIT 5 OFFSET 5;

SELECT * FROM customers
    ORDER BY last_name DESC LIMIT 5, 1; -- LIMIT 5, 1 is the same as LIMIT 5 OFFSET 1

-- This is useful for pagination
