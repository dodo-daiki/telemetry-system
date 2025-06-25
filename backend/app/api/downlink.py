from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from app import crud, schemas, database
from app.api.websocket_endpoint import manager  # WebSocket管理インスタンスのimport

import json

router = APIRouter()

@router.post("/downlink_data")
async def create_telemetry_data(
    payload: schemas.TelemetryLogCreate,
    db: Session = Depends(database.get_db)
):
    try:
        # DBへの保存
        crud.create_telemetry_log(db=db, data=payload)

        # WebSocketに送信（例外処理あり）
        try:
            await manager.broadcast(json.dumps({
                "type": "downlink",
                "data": payload.dict()
            }))
        except Exception as e:
            print(f"WebSocket broadcast failed: {e}")

        return {"status": "success", "message": "Telemetry data received and broadcasted."}
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Failed to store telemetry: {e}")
