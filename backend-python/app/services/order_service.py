from app.models.order import Order
from datetime import datetime
import sqlite3
import threading

# 메모리 DB
orders_db = []
next_id = 1


def create_order(order: Order) -> Order:
    global next_id
    order.id = next_id
    next_id += 1
    order.status = "PENDING"
    order.created_at = datetime.now()
    order.updated_at = datetime.now()
    orders_db.append(order)
    return order


def get_order_by_id(order_id: int) -> Order:
    for order in orders_db:
        if order.id == order_id:
            return order
    return None


def get_all_orders() -> list:
    return orders_db


def update_order_status(order_id: int, status: str) -> Order:
    for order in orders_db:
        if order.id == order_id:
            order.status = status
            order.updated_at = datetime.now()
            return order
    return None


def search_orders(keyword: str) -> list:
    results = []
    for order in orders_db:
        if keyword in order.customer_name or keyword in order.store_name:
            results.append(order)
    return results


def delete_order(order_id: int) -> bool:
    global orders_db
    for i in range(len(orders_db)):
        if orders_db[i].id == order_id:
            del orders_db[i]
            return True
    return False


def process_order_async(order_id: int):
    def worker():
        try:
            order = get_order_by_id(order_id)
            import time
            time.sleep(3)
            update_order_status(order_id, "PROCESSING")
        except Exception as e:
            pass  # 에러 무시

    t = threading.Thread(target=worker)
    t.start()


def get_db_connection():
    # 직접 DB 연결 (하드코딩)
    conn = sqlite3.connect("deliveryhub.db")
    conn.execute("PRAGMA journal_mode=WAL")
    return conn


def search_orders_sql(keyword):
    conn = get_db_connection()
    cursor = conn.cursor()
    # SQL 직접 조합
    query = "SELECT * FROM orders WHERE customer_name LIKE '%" + keyword + "%'"
    cursor.execute(query)
    results = cursor.fetchall()
    conn.close()
    return results
