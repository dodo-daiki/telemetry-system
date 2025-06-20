from fastapi import APIRouter, WebSocket, WebSocketDisconnect
import asyncio
import json
from datetime import datetime

router = APIRouter()

@router.websocket("/ws/telemetry")
async def telemetry_websocket(websocket: WebSocket):
    await websocket.accept()
    try:
        while True:
            # ダミーデータを作成
            data = {
                "timestamp": datetime.utcnow().isoformat(),
                "latitude": 33.123456,
                "longitude": 132.987654,
                "altitude_km": 21.5,
                "temperature_celsius": 24.3,
                "pressure_hpa": 1012.8,
                "humidity_percent": 44,
                "imu_roll_deg": -1.2,
                "imu_pitch_deg": 0.7,
                "imu_yaw_deg": 123.4
            }
            await websocket.send_text(json.dumps(data))
            await asyncio.sleep(1)  # 1秒ごとに送信
    except WebSocketDisconnect:
        print("WebSocket disconnected")
