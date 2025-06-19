from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from app.database import get_db
from app import crud

router = APIRouter(tags=["telemetry_log_json"])

@router.get("/telemetry_log.json")
def get_telemetry_log_json(limit: int = 100, db: Session = Depends(get_db)):
    """
    テレメトリログをJSON形式で取得するAPI。
    最大 `limit` 件（デフォルト100件）まで取得。
    """
    logs = crud.get_all_telemetry_logs(db, limit=limit)
    
    # ORMオブジェクトを辞書に変換
    result = []
    for log in logs:
        result.append({
            "station_id": log.station_id,
            "flight_id": log.flight_id,
            "timestamp": log.timestamp,
            "latitude": log.latitude,
            "longitude": log.longitude,
            "altitude_km": log.altitude_km,
            "temperature_celsius": log.temperature_celsius,
            "pressure_hpa": log.pressure_hpa,
            "humidity_percent": log.humidity_percent,
            "imu_roll_deg": log.imu_roll_deg,
            "imu_pitch_deg": log.imu_pitch_deg,
            "imu_yaw_deg": log.imu_yaw_deg
        })

    return result
