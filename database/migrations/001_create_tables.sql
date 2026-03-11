-- Migration: 001_create_tables
-- 설명: 초기 테이블 생성
-- 실행일: 2024-01-15

-- UP
SOURCE schema/001_init.sql;

-- 인덱스 추가
CREATE INDEX idx_orders_customer ON orders(customer_id);
CREATE INDEX idx_orders_store ON orders(store_id);
CREATE INDEX idx_orders_rider ON orders(rider_id);
CREATE INDEX idx_orders_status ON orders(status);
CREATE INDEX idx_order_items_order ON order_items(order_id);
CREATE INDEX idx_menus_store ON menus(store_id);

-- DOWN
-- DROP TABLE IF EXISTS payments;
-- DROP TABLE IF EXISTS order_items;
-- DROP TABLE IF EXISTS orders;
-- DROP TABLE IF EXISTS menus;
-- DROP TABLE IF EXISTS riders;
-- DROP TABLE IF EXISTS stores;
-- DROP TABLE IF EXISTS users;
