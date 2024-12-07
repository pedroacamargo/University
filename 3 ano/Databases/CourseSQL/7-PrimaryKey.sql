CREATE TABLE transactions (
    transaction_id INT PRIMARY KEY,
    amount DECIMAL(5,2)
);

SELECT * FROM transactions;

-- This will give an error, since multiple primary keys in a table isn't allowed
ALTER TABLE transactions
    ADD CONSTRAINT PRIMARY KEY(amount);

INSERT INTO transactions VALUES
    (1000, 4.99);

DROP TABLE transactions;

-- AUTO INCREMENT will increase the id automatically
CREATE TABLE transactions (
    transaction_id INT PRIMARY KEY AUTO_INCREMENT,
    amount DECIMAL(5,2),
);

SELECT * FROM transactions;