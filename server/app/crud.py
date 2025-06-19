from sqlalchemy.orm import Session
from app import models, schemas

def create_telemetry_log(db: Session, data: schemas.DownlinkData):
    """Downlinkデータをtelemetry_logテーブルに保存する"""
    db_entry = models.TelemetryLog(
        station_id=data.station_id,
        flight_id="default_flight",  # 今後の拡張用
        timestamp=data.timestamp,
        latitude=data.latitude,
        longitude=data.longitude,
        altitude_km=data.altitude_km,
        temperature_celsius=data.temperature_celsius,
        pressure_hpa=data.pressure_hpa,
        humidity_percent=data.humidity_percent,
        imu_roll_deg=data.imu_roll_deg,
        imu_pitch_deg=data.imu_pitch_deg,
        imu_yaw_deg=data.imu_yaw_deg,
    )

    db.add(db_entry)
    db.commit()
    db.refresh(db_entry)
    return db_entry

def get_all_telemetry_logs(db: Session, limit: int = 100):
    return db.query(models.TelemetryLog).order_by(models.TelemetryLog.timestamp.desc()).limit(limit).all()
