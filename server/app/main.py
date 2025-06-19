from fastapi import FastAPI, Depends
from sqlalchemy.orm import Session
from app import models, database
from app.api import downlink, telemetry_log_json

# アプリケーションインスタンス（← これが最初に必要！）
app = FastAPI(
    title="Telemetry Server",
    version="1.0.0"
)

# データベース初期化（テーブルが存在しなければ作成）
models.Base.metadata.create_all(bind=database.engine)

# DBセッション依存性（必要なら再利用可能）
def get_db():
    db = database.SessionLocal()
    try:
        yield db
    finally:
        db.close()

# APIルーターの登録
app.include_router(downlink.router, prefix="/api")
app.include_router(telemetry_log_json.router, prefix="/api")

# 動作確認用のルート
@app.get("/")
def read_root():
    return {"message": "Telemetry API is running"}
