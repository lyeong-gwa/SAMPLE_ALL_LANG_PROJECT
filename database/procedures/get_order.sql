-- 주문 상세 조회 프로시저
DELIMITER //

CREATE PROCEDURE sp_get_order_detail(IN p_order_id INT)
BEGIN
    SELECT
        o.id AS order_id,
        o.status,
        o.total_price,
        o.delivery_fee,
        o.delivery_address,
        o.request_note,
        o.created_at,
        u.username AS customer_name,
        u.phone AS customer_phone,
        s.name AS store_name,
        s.address AS store_address,
        r.id AS rider_id
    FROM orders o
    LEFT JOIN users u ON o.customer_id = u.id
    LEFT JOIN stores s ON o.store_id = s.id
    LEFT JOIN riders r ON o.rider_id = r.id
    WHERE o.id = p_order_id;

    SELECT
        oi.id,
        m.name AS menu_name,
        oi.quantity,
        oi.price,
        oi.options
    FROM order_items oi
    LEFT JOIN menus m ON oi.menu_id = m.id
    WHERE oi.order_id = p_order_id;
END //

DELIMITER ;


-- 가맹점 매출 조회 프로시저
DELIMITER //

CREATE PROCEDURE sp_get_store_sales(IN p_store_id INT, IN p_start_date DATE, IN p_end_date DATE)
BEGIN
    SELECT
        DATE(o.created_at) as sale_date,
        COUNT(*) as order_count,
        SUM(o.total_price) as total_sales
    FROM orders o
    WHERE o.store_id = p_store_id
    AND o.status = 'COMPLETED'
    AND o.created_at BETWEEN p_start_date AND p_end_date
    GROUP BY DATE(o.created_at)
    ORDER BY sale_date;
END //

DELIMITER ;


-- 주문 검색 (파라미터 바인딩 사용)
DELIMITER //

CREATE PROCEDURE sp_search_orders(IN p_keyword VARCHAR(100))
BEGIN
    SET @search_keyword = CONCAT('%', p_keyword, '%');
    SET @sql = 'SELECT * FROM orders WHERE delivery_address LIKE ?';
    PREPARE stmt FROM @sql;
    EXECUTE stmt USING @search_keyword;
    DEALLOCATE PREPARE stmt;
END //

DELIMITER ;
