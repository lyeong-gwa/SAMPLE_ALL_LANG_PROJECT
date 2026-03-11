import os
from dotenv import load_dotenv
from fastapi import FastAPI
from app.routers import order_router

load_dotenv()

app = FastAPI(title="DeliveryHub API", version="0.1.0")

# DB 설정 (환경변수에서 로드)
DB_HOST = os.getenv("DB_HOST", "localhost")
DB_USER = os.getenv("DB_USER", "admin")
DB_PASSWORD = os.getenv("DB_PASSWORD", "")
DB_NAME = os.getenv("DB_NAME", "deliveryhub")

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
