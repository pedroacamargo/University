--- ON DELETE SET NULL -> if the parent record is deleted, the child record will be set to NULL
--- ON DELETE CASCADE -> if the parent record is deleted, the child record will be deleted as well

SET foreign_key_checks = 0;

DELETE FROM customers
    WHERE customer_id = 4;

SET foreign_key_checks = 1;

CREATE TABLE transactions (
    transaction_id INT AUTO_INCREMENT PRIMARY KEY,
    amount DECIMAL(10, 2),
    customer_id INT,
    order_date DATE,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
        ON DELETE SET NULL
);

