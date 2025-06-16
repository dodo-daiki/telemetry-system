from pydantic import BaseModel, Field
from typing import Literal

class DownlinkData(BaseModel):
    packet_type: Literal["telemetry"]
    station_id: str
    timestamp: int
    latitude: float
    longitude: float
    altitude_km: float
    temperature_celsius: float
    pressure_hpa: float
    humidity_percent: int
    imu_roll_deg: float
    imu_pitch_deg: float
    imu_yaw_deg: float

class TelemetryLogResponse(BaseModel):
    station_id: str
    flight_id: str
    timestamp: int
    latitude: float
    longitude: float
    altitude_km: float
    temperature_celsius: float
    pressure_hpa: float
    humidity_percent: int
    imu_roll_deg: float
    imu_pitch_deg: float
    imu_yaw_deg: float

    class Config:
        orm_mode = True  # ← SQLAlchemyモデルを変換可能にする！
