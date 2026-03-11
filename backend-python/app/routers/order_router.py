from fastapi import APIRouter, HTTPException
from app.models.order import Order
from app.services import order_service

router = APIRouter()


@router.post("/")
def create_order(order: Order):
    return order_service.create_order(order)


@router.get("/{order_id}")
def get_order(order_id: int):
    order = order_service.get_order_by_id(order_id)
    if order is None:
        raise HTTPException(status_code=404, detail="주문을 찾을 수 없습니다")
    return order


@router.get("/")
def get_all_orders():
    return order_service.get_all_orders()


@router.put("/{order_id}/status")
def update_status(order_id: int, status: str):
    order = order_service.update_order_status(order_id, status)
    if order is None:
        raise HTTPException(status_code=404, detail="주문을 찾을 수 없습니다")
    return order


@router.get("/search/")
def search_orders(keyword: str):
    return order_service.search_orders(keyword)


@router.delete("/{order_id}")
def delete_order(order_id: int):
    result = order_service.delete_order(order_id)
    if not result:
        raise HTTPException(status_code=404, detail="주문을 찾을 수 없습니다")
    return {"message": "삭제 완료"}
