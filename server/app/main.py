from fastapi import FastAPI, Depends
from sqlalchemy.orm import Session
from app import models, database
from app.api import downlink, telemetry_log_json
from app.api import telemetry_log_kml
from app.api import telemetry_log_csv
from app.api import uplink_command
from app.api import uplink_log
from app.api import websocket_endpoint


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
app.include_router(telemetry_log_kml.router, prefix="/api")
app.include_router(telemetry_log_csv.router, prefix="/api")
app.include_router(uplink_command.router, prefix="/api")
app.include_router(uplink_log.router, prefix="/api")
app.include_router(websocket_endpoint.router)

# 動作確認用のルート
@app.get("/")
def read_root():
    return {"message": "Telemetry API is running"}
