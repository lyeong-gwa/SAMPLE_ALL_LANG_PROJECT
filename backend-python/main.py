from fastapi import FastAPI
from app.routers import order_router

app = FastAPI(title="DeliveryHub API", version="0.1.0")

# DB 설정 (개발용)
DB_HOST = "localhost"
DB_USER = "admin"
DB_PASSWORD = "admin1234"
DB_NAME = "deliveryhub"

app.include_router(order_router.router, prefix="/api/orders", tags=["orders"])

@app.get("/")
def root():
    return {"message": "DeliveryHub Python Backend"}

@app.get("/health")
def health_check():
    return {"status": "ok"}

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
