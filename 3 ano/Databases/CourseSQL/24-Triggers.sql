--- Trigger is a special type of stored procedure that is automatically executed when an event occurs in the database server
--- -> Example: Before an insert, after an update, etc.
--- -> Checks data, handles erros, auditing tables, etc.

ALTER TABLE employees
    ADD COLUMN salary DECIMAL(10, 2) 
        AFTER hourly_pay;

UPDATE employees
    SET salary = hourly_pay * 2080;

CREATE TRIGGER before_hourly_pay_update
    BEFORE UPDATE ON employees
    FOR EACH ROW
    SET NEW.salary = (NEW.hourly_pay * 2080);


UPDATE employees
    SET hourly_pay = 50
    WHERE id = 1;

CREATE TRIGGER before_hourly_pay_insert
    BEFORE INSERT ON employees
    FOR EACH ROW
    SET NEW.salary = (NEW.hourly_pay * 2080);

CREATE TABLE expenses (
    expense_id INT PRIMARY KEY AUTO_INCREMENT,
    expense_name VARCHAR(50),
    expense_total DECIMAL(10, 2)
);

SELECT * FROM expenses;

INSERT INTO expenses (expense_name, expense_total) VALUES
    ('salaries', 0),
    ('Utilities', 0),
    ('Food', 0);

UPDATE expenses
    SET expense_total = (SELECT SUM(hourly_pay) FROM employees)
    WHERE expense_name = 'salaries';

CREATE TRIGGER after_salary_delete
    AFTER DELETE ON employees
    FOR EACH ROW
    UPDATE expenses
        SET expense_total = expense_total - OLD.salary
        WHERE expense_name = 'salaries';

CREATE TRIGGER after_salary_insert
    AFTER INSERT ON employees
    FOR EACH ROW
    UPDATE expenses
        SET expense_total = expense_total + NEW.salary
        WHERE expense_name = 'salaries';

CREATE TRIGGER after_salary_update
    AFTER UPDATE ON employees
    FOR EACH ROW
    UPDATE expenses
        SET expense_total = expense_total + (NEW.salary - OLD.salary)
        WHERE expense_name = 'salaries';