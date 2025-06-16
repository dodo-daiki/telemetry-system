from fastapi import FastAPI, Depends, HTTPException
from sqlalchemy.orm import Session
from app import models, schemas, crud, database
from app.api import downlink

# モデルのメタデータをもとにDBを初期化
models.Base.metadata.create_all(bind=database.engine)

# アプリケーションインスタンス
app = FastAPI(
    title="Telemetry Server",
    version="1.0.0"
)

# downlink_dataルーターの登録
app.include_router(downlink.router, prefix="/api")

# DBセッション依存性（必要なら再利用可能）
def get_db():
    db = database.SessionLocal()
    try:
        yield db
    finally:
        db.close()

# ルート確認用（オプション）
@app.get("/")
def read_root():
    return {"message": "Telemetry API is running"}
