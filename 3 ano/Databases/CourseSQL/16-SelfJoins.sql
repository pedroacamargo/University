SELECT * FROM customers;


ALTER TABLE customers
    ADD referral_id INT;

UPDATE customers
    SET referral_id = 1
    WHERE id = 2;

SELECT * FROM customers AS a
    INNER JOIN customers AS b
    ON a.referral_id = b.id;