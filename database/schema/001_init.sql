-- DeliveryHub 초기 스키마
-- 작성자: JungWoojin
-- 작성일: 2024-01-15

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    password VARCHAR(100) NOT NULL,
    email VARCHAR(100),
    phone VARCHAR(20),
    role VARCHAR(20) DEFAULT 'CUSTOMER',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE stores (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    address VARCHAR(200),
    phone VARCHAR(20),
    owner_id INT,
    category VARCHAR(50),
    rating DECIMAL(3,2) DEFAULT 0.00,
    is_open INT DEFAULT 1,
    open_time VARCHAR(5) DEFAULT '09:00',
    close_time VARCHAR(5) DEFAULT '22:00',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE menus (
    id INT AUTO_INCREMENT PRIMARY KEY,
    store_id INT NOT NULL,
    name VARCHAR(100) NOT NULL,
    description VARCHAR(500),
    price INT NOT NULL,
    category VARCHAR(50),
    is_available INT DEFAULT 1,
    image_url VARCHAR(300),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE orders (
    id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT NOT NULL,
    store_id INT NOT NULL,
    rider_id INT,
    total_price INT NOT NULL,
    delivery_fee INT DEFAULT 3000,
    status VARCHAR(20) DEFAULT 'PENDING',
    delivery_address VARCHAR(200) NOT NULL,
    delivery_lat DECIMAL(10,7),
    delivery_lng DECIMAL(10,7),
    request_note VARCHAR(500),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE order_items (
    id INT AUTO_INCREMENT PRIMARY KEY,
    order_id INT NOT NULL,
    menu_id INT NOT NULL,
    quantity INT DEFAULT 1,
    price INT NOT NULL,
    options VARCHAR(500)
);

CREATE TABLE riders (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    vehicle_type VARCHAR(20),
    license_number VARCHAR(30),
    is_available INT DEFAULT 0,
    current_lat DECIMAL(10,7),
    current_lng DECIMAL(10,7),
    total_deliveries INT DEFAULT 0,
    rating DECIMAL(3,2) DEFAULT 0.00,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE payments (
    id INT AUTO_INCREMENT PRIMARY KEY,
    order_id INT NOT NULL,
    amount INT NOT NULL,
    method VARCHAR(20) NOT NULL,
    status VARCHAR(20) DEFAULT 'PENDING',
    transaction_id VARCHAR(100),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 초기 데이터 (비밀번호는 SHA-256 해시 적용)
INSERT INTO users (username, password, email, phone, role) VALUES
('admin', SHA2('admin1234', 256), 'admin@deliveryhub.dev', '010-0000-0000', 'ADMIN'),
('testuser1', SHA2('test1234', 256), 'test1@test.com', '010-1111-1111', 'CUSTOMER'),
('teststore1', SHA2('store1234', 256), 'store1@test.com', '010-2222-2222', 'STORE_OWNER'),
('testrider1', SHA2('rider1234', 256), 'rider1@test.com', '010-3333-3333', 'RIDER');
