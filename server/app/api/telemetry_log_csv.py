from fastapi import APIRouter, Depends, Response
from sqlalchemy.orm import Session
from io import StringIO
import csv

from app.database import get_db
from app import crud

router = APIRouter(tags=["telemetry_log_csv"])

@router.get("/telemetry_log.csv", response_class=Response)
def get_telemetry_log_csv(limit: int = 100, db: Session = Depends(get_db)):
    """
    テレメトリログをCSV形式で取得（最大 `limit` 件まで）
    """
    logs = crud.get_all_telemetry_logs(db, limit=limit)

    output = StringIO()
    writer = csv.writer(output)

    # ヘッダ
    writer.writerow([
        "station_id", "flight_id", "timestamp",
        "latitude", "longitude", "altitude_km",
        "temperature_celsius", "pressure_hpa", "humidity_percent",
        "imu_roll_deg", "imu_pitch_deg", "imu_yaw_deg"
    ])

    # データ行
    for log in logs:
        writer.writerow([
            log.station_id,
            log.flight_id,
            log.timestamp,
            log.latitude,
            log.longitude,
            log.altitude_km,
            log.temperature_celsius,
            log.pressure_hpa,
            log.humidity_percent,
            log.imu_roll_deg,
            log.imu_pitch_deg,
            log.imu_yaw_deg
        ])

    return Response(content=output.getvalue(), media_type="text/csv")
