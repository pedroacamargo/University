--- INDEX (BTree data structure)
--- Indexes are used to find values within a specific column more quickly
--- MySQL normally searches sequentially through a column
--- The longer the column, the more expensive the operation is
--- UPDATE takes more time, SELECT takes less time

SELECT * FROM customers;

-- This will show the indexes of the customers table
SHOW INDEXES FROM customers;

CREATE INDEX last_name_index
    ON customers (last_name);

SHOW INDEXES FROM customers;

SELECT * FROM customers
    WHERE last_name = 'Doe';

CREATE INDEX last_name_first_name_index
    ON customers (last_name, first_name);

ALTER TABLE customers
    DROP INDEX last_name_index;

SHOW INDEXES FROM customers;

SELECT * FROM customers
    WHERE last_name = 'Doe' AND first_name = 'John';