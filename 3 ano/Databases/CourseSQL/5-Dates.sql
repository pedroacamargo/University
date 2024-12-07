CREATE TABLE date (
    my_date DATE,
    my_time TIME,
    my_datetime DATETIME,
);

INSERT INTO date (my_date, my_time, my_datetime)
    VALUES ('2020-01-01', '12:00:00', '2020-01-01 12:00:00');

INSERT INTO date (my_date, my_time, my_datetime) VALUES
    CURRENT_DATE(), CURRENT_DATE(), NOW();

SELECT * FROM date;
DROP TABLE date;