from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String, Float, DateTime
from datetime import datetime

Base = declarative_base()

class TelemetryLog(Base):
    __tablename__ = "telemetry_log"

    id = Column(Integer, primary_key=True, index=True)
    station_id = Column(String)
    flight_id = Column(String, default="default_flight")  # 今後拡張予定
    timestamp = Column(Integer, unique=True, index=True)
    latitude = Column(Float)
    longitude = Column(Float)
    altitude_km = Column(Float)
    temperature_celsius = Column(Float)
    pressure_hpa = Column(Float)
    humidity_percent = Column(Integer)
    imu_roll_deg = Column(Float)
    imu_pitch_deg = Column(Float)
    imu_yaw_deg = Column(Float)

class UplinkCommand(Base):
    __tablename__ = "uplink_commands"

    id = Column(Integer, primary_key=True, index=True)
    target_id = Column(String, index=True)  # 宛先装置ID
    command = Column(String)                # コマンド文字列
    created_at = Column(DateTime, default=datetime.utcnow)  # 登録時刻