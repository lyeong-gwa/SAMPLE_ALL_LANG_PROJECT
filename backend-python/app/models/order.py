from pydantic import BaseModel
from typing import Optional
from datetime import datetime


class Order(BaseModel):
    id: Optional[int] = None
    customer_name: str
    customer_phone: str
    delivery_address: str
    store_name: str
    menu_items: str
    total_price: int
    status: str = "PENDING"
    created_at: Optional[datetime] = None
    updated_at: Optional[datetime] = None


# 주문 상태 - 그냥 문자열로 관리
ORDER_STATUS_PENDING = "PENDING"
ORDER_STATUS_CONFIRMED = "CONFIRMED"
ORDER_STATUS_DELIVERING = "DELIVERING"
ORDER_STATUS_COMPLETED = "COMPLETED"
ORDER_STATUS_CANCELLED = "CANCELLED"
