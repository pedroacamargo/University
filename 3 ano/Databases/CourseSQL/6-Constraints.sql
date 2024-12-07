CREATE TABLE products (
    product_id INT AUTO_INCREMENT,
    product_name VARCHAR(50),
    price DECIMAL(5,2),
    PRIMARY KEY (product_id),
);

ALTER TABLE products
    ADD CONSTRAINT UNIQUE(product_name);

SELECT * FROM products;

INSERT INTO products VALUES
    (NULL, 'Apple', 1.00),
    (NULL, 'Banana', 0.50),
    (NULL, 'Orange', 0.75),
    (NULL, 'Apple', 1.00);

SELECT * FROM products;
DROP TABLE products;

-- The UNIQUE constraint ensures that all values in a column are different.
-- Both the UNIQUE and PRIMARY KEY constraints provide a guarantee for uniqueness for a column or set of columns.
-- A PRIMARY KEY constraint automatically has a UNIQUE constraint.

ALTER TABLE products
    MODIFY price DECIMAL(5,2) NOT NULL;

-- This will raise an error because the price column does not accept NULL values
INSERT INTO products (product_name) VALUES
    ('Apple'),
    ('Banana'),
    ('Orange'),
    ('Apple');

-- The NOT NULL constraint enforces a column to NOT accept NULL values.
-- This enforces a field to always contain a value, which means that you cannot insert a new record, or update a record without adding a value to this field.

CREATE TABLE employees (
    employee_id INT,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    hourly_pay DECIMAL(5,2), -- DECIMAL(maximum amount of digits, precision)
    hire_date DATE,
    CONSTRAINT chk_hourly_pay CHECK (hourly_pay >= 10.00),
);

ALTER TABLE employees
    ADD CONSTRAINT chk_hire_date CHECK (hire_date >= '2000-01-01');

-- This will raise an error because the hourly_pay is less than 10.00
INSERT INTO employees VALUES
    (1, 'John', 'Doe', 9.50, '2020-01-01'),
    (2, 'Jane', 'Doe', 10.50, '2020-01-01');


-- The CHECK constraint is used to limit the value range that can be placed in a column.

INSERT INTO products VALUES
    (NULL, 'Apple', 0.00),
    (NULL, 'Banana', 0.00),
    (NULL, 'Orange', 0.00),
    (NULL, 'Apple', 0.00);

CREATE TABLE products (
    product_id INT AUTO_INCREMENT,
    product_name VARCHAR(50),
    price DECIMAL(5,2) DEFAULT 0.00,
    PRIMARY KEY (product_id),
    CONSTRAINT chk_price CHECK (price >= 0.00),
);

-- With the DEFAULT constraint, you don't have to specify a value when inserting data into the table.
INSERT INTO products (product_name) VALUES
    ('Apple'),
    ('Banana'),
    ('Orange'),
    ('Apple');

CREATE TABLE transactions (
    transaction_id INT,
    amount DECIMAL(5,2),
    transaction_date DATETIME DEFAULT NOW(),
);

INSERT INTO transactions (transaction_id, amount) VALUES
    (3, 8.37);

DROP TABLE transactions;