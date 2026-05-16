#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

-- =========================
-- PHẦN 1: THIẾT KẾ CSDL
-- =========================

DROP DATABASE IF EXISTS HotelBookingDB;
CREATE DATABASE HotelBookingDB;
USE HotelBookingDB;

-- =========================
-- TABLE: Guests
-- =========================
CREATE TABLE Guests (
    guest_id INT PRIMARY KEY,
    full_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    phone VARCHAR(20) NOT NULL UNIQUE,
    loyalty_points INT DEFAULT 0 CHECK (loyalty_points >= 0)
);

-- =========================
-- TABLE: Guest_Profiles
-- =========================
CREATE TABLE Guest_Profiles (
    profile_id INT PRIMARY KEY,
    guest_id INT,
    address VARCHAR(255) NOT NULL,
    birthday DATE NOT NULL,
    national_id VARCHAR(20) NOT NULL UNIQUE,

    FOREIGN KEY (guest_id) REFERENCES Guests(guest_id)
);

-- =========================
-- TABLE: Rooms
-- =========================
CREATE TABLE Rooms (
    room_id INT PRIMARY KEY,
    room_name VARCHAR(100) NOT NULL,
    room_type ENUM('Standard', 'Deluxe', 'Suite') NOT NULL,
    price_per_night DECIMAL(15,2) NOT NULL CHECK (price_per_night > 0),
    room_status ENUM('Available', 'Occupied', 'Maintenance') NOT NULL
);

-- =========================
-- TABLE: Bookings
-- =========================
CREATE TABLE Bookings (
    booking_id INT PRIMARY KEY,
    guest_id INT,
    check_in_date DATETIME NOT NULL,
    check_out_date DATETIME NOT NULL,
    total_charge DECIMAL(15,2) NOT NULL CHECK (total_charge > 0),
    booking_status ENUM('Pending', 'Completed', 'Cancelled') NOT NULL,
    room_id INT,

    CHECK (check_out_date > check_in_date),

    FOREIGN KEY (guest_id) REFERENCES Guests(guest_id),
    FOREIGN KEY (room_id) REFERENCES Rooms(room_id)
);

-- TABLE: Room_Log

CREATE TABLE Room_Log (
    log_id INT PRIMARY KEY,
    room_id INT,
    action_type ENUM('Check-in', 'Check-out', 'Maintenance', 'Cancelled') NOT NULL,
    change_note VARCHAR(255) NOT NULL,
    logged_at DATETIME DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (room_id) REFERENCES Rooms(room_id)
);

-- =========================
-- PHẦN 1.2: INSERT DỮ LIỆU
-- =========================

-- Guests
INSERT INTO Guests
VALUES
(1, 'Nguyen Van A', 'anv@gmail.com', '901234567', 150),
(2, 'Tran Thi B', 'btt@gmail.com', '912345678', 500),
(3, 'Le Van C', 'cle@yahoo.com', '922334455', 0),
(4, 'Pham Minh D', 'dpham@hotmail.com', '933445566', 1000),
(5, 'Hoang Anh E', 'ehoang@gmail.com', '944556677', 20);

-- Guest Profiles
INSERT INTO Guest_Profiles
VALUES
(101, 1, '123 Le Loi, Q1, HCM', '1990-05-15', '12345'),
(102, 2, '456 Nguyen Hue, Q1, HCM', '1985-10-20', '23456'),
(103, 3, '789 Phan Chu Trinh, Da Nang', '1995-12-01', '34567'),
(104, 4, '101 Hoang Hoa Tham, Ha Noi', '1988-03-25', '45678'),
(105, 5, '202 Tran Hung Dao, Can Tho', '2000-07-10', '56789');

-- Rooms
INSERT INTO Rooms
VALUES
(1, 'Room 101', 'Standard', 100000, 'Available'),
(2, 'Room 202', 'Deluxe', 5000000, 'Occupied'),
(3, 'Room 303', 'Suite', 300000, 'Available'),
(4, 'Room 104', 'Standard', 200000, 'Occupied'),
(5, 'Room 205', 'Deluxe', 2000000, 'Maintenance');

-- Bookings
INSERT INTO Bookings
VALUES
(1001, 1, '2023-11-15 10:30:00', '2023-11-18 12:00:00', 300000, 'Completed', 1),
(1002, 2, '2023-12-01 14:20:00', '2023-12-04 12:00:00', 20000000, 'Completed', 2),
(1003, 1, '2021-01-10 09:15:00', '2021-01-11 12:00:00', 5000000, 'Pending', 2),
(1004, 3, '2023-05-20 16:45:00', '2023-05-22 12:00:00', 900000, 'Cancelled', 3),
(1005, 4, '2024-01-18 11:00:00', '2024-01-20 12:00:00', 8000000, 'Completed', 4);

-- Room Log
INSERT INTO Room_Log
VALUES
(1, 1, 'Check-in', 'Guest checked in', '2023-10-01 08:00:00'),
(2, 1, 'Check-out', 'Guest checked out', '2023-11-15 10:35:00'),
(3, 4, 'Maintenance', 'Room reported as damaged', '2023-11-20 15:00:00'),
(4, 2, 'Check-in', 'New guest arrival', '2023-11-25 09:00:00'),
(5, 3, 'Maintenance', 'Schedule maintenance', '2023-12-01 13:00:00');

-- =========================
-- UPDATE
-- =========================
UPDATE Guests
SET loyalty_points = loyalty_points + 200
WHERE email LIKE '%@gmail.com';

-- =========================
-- DELETE
-- =========================
DELETE FROM Room_Log
WHERE logged_at < '2023-11-10';

-- =========================
-- PHẦN 2: TRUY VẤN CƠ BẢN
-- =========================

-- Câu 1
SELECT room_name, price_per_night, room_status
FROM Rooms
WHERE price_per_night > 1000000
   OR room_status = 'Maintenance'
   OR room_type = 'Suite';

-- Câu 2
SELECT full_name, email
FROM Guests
WHERE email LIKE '%@gmail.com'
  AND loyalty_points BETWEEN 50 AND 300;

-- Câu 3
SELECT *
FROM Bookings
ORDER BY total_charge DESC
LIMIT 3 OFFSET 1;

-- =========================
-- PHẦN 3: TRUY VẤN NÂNG CAO
-- =========================

-- Câu 1
SELECT
    g.full_name,
    gp.national_id,
    b.booking_id,
    b.check_in_date,
    b.total_charge
FROM Guests g
JOIN Guest_Profiles gp
    ON g.guest_id = gp.guest_id
JOIN Bookings b
    ON g.guest_id = b.guest_id;

-- Câu 2
SELECT
    g.guest_id,
    g.full_name,
    SUM(b.total_charge) AS total_payment
FROM Guests g
JOIN Bookings b
    ON g.guest_id = b.guest_id
WHERE b.booking_status = 'Completed'
GROUP BY g.guest_id, g.full_name
HAVING SUM(b.total_charge) > 20000000;

-- Câu 3
SELECT *
FROM Rooms
WHERE room_id IN (
    SELECT room_id
    FROM Bookings
    WHERE booking_status = 'Completed'
)
AND price_per_night = (
    SELECT MAX(price_per_night)
    FROM Rooms
    WHERE room_id IN (
        SELECT room_id
        FROM Bookings
        WHERE booking_status = 'Completed'
    )
);

-- =========================
-- PHẦN 4: INDEX & VIEW
-- =========================

-- Câu 1
CREATE INDEX idx_booking_status_cgh
ON Bookings(booking_status, check_in_date);

-- Câu 2
CREATE VIEW vw_guest_booking_stats AS
SELECT
    g.full_name AS guest_name,
    COUNT(b.booking_id) AS total_bookings,
    SUM(
        CASE
            WHEN b.booking_status <> 'Cancelled'
            THEN b.total_charge
            ELSE 0
        END
    ) AS total_paid
FROM Guests g
LEFT JOIN Bookings b
    ON g.guest_id = b.guest_id
GROUP BY g.guest_id, g.full_name;

-- =========================
-- PHẦN 5: TRIGGER
-- =========================

-- Câu 1
DELIMITER $$

CREATE TRIGGER trg_after_update_booking_status
AFTER UPDATE ON Bookings
FOR EACH ROW
BEGIN
    IF NEW.booking_status = 'Completed'
       AND OLD.booking_status <> 'Completed' THEN

        INSERT INTO Room_Log (
            room_id,
            action_type,
            change_note,
            logged_at
        )
        VALUES (
            NEW.room_id,
            'Check-out',
            'Booking Completed',
            NOW()
        );

    END IF;
END $$

DELIMITER ;

-- Câu 2
DELIMITER $$

CREATE TRIGGER trg_update_loyalty_points
AFTER INSERT ON Bookings
FOR EACH ROW
BEGIN
    IF NEW.booking_status = 'Completed' THEN

        UPDATE Guests
        SET loyalty_points = loyalty_points + FLOOR(NEW.total_charge / 1000000) * 2
        WHERE guest_id = NEW.guest_id;

    END IF;
END $$

DELIMITER ;

-- =========================
-- PHẦN 6: STORED PROCEDURE
-- =========================

-- Câu 1
DELIMITER $$

CREATE PROCEDURE sp_get_room_status(IN p_room_id INT)
BEGIN
    DECLARE v_status VARCHAR(20);

    SELECT room_status
    INTO v_status
    FROM Rooms
    WHERE room_id = p_room_id;

    IF v_status = 'Available' THEN
        SELECT 'Phòng trống' AS message;

    ELSEIF v_status = 'Occupied' THEN
        SELECT 'Đang có khách' AS message;

    ELSEIF v_status = 'Maintenance' THEN
        SELECT 'Bảo trì' AS message;

    END IF;
END $$

DELIMITER ;

-- Test
CALL sp_get_room_status(1);

-- =========================
-- Procedure hủy booking
-- =========================

DELIMITER $$

CREATE PROCEDURE sp_cancel_booking(IN p_booking_id INT)
BEGIN
    DECLARE v_room_id INT;

    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
    END;

    START TRANSACTION;

    SELECT room_id
    INTO v_room_id
    FROM Bookings
    WHERE booking_id = p_booking_id;

    UPDATE Bookings
    SET booking_status = 'Cancelled'
    WHERE booking_id = p_booking_id;

    UPDATE Rooms
    SET room_status = 'Available'
    WHERE room_id = v_room_id;

    INSERT INTO Room_Log (
        room_id,
        action_type,
        change_note,
        logged_at
    )
    VALUES (
        v_room_id,
        'Cancelled',
        'Booking Cancelled',
        NOW()
    );

    COMMIT;
END $$

DELIMITER ;

-- Test
CALL sp_cancel_booking(1003);
