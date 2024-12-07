CREATE TABLE customers (
    customer_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50),
    last_name VARCHAR(50)
);

INSERT INTO customers VALUES
    ('John', 'Doe'),
    ('Jane', 'Doe'),
    ('Alice', 'Smith'),
    ('Bob', 'Smith');

DROP TABLE transactions;

CREATE TABLE transactions (
    transaction_id INT PRIMARY KEY AUTO_INCREMENT,
    amount DECIMAL(10, 2),
    customer_id INT,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

ALTER TABLE transactions
    DROP FOREIGN KEY transactions_ibfk_1;

ALTER TABLE transactions
    ADD CONSTRAINT fk_customer_id FOREIGN KEY (customer_id) REFERENCES customers(customer_id);

DELETE FROM transactions;
SELECT * FROM transactions;

ALTER TABLE transactions
    AUTO_INCREMENT = 1000;

INSERT INTO transactions (amount, customer_id) VALUES
    (100.00, 1),
    (200.00, 2),
    (300.00, 3),
    (400.00, 4);