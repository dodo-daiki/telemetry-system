from pydantic import BaseModel, Field
from typing import Literal, Optional
from datetime import datetime


# 受信データ（API受信用）
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


# DB登録用（内部用）
class TelemetryLogCreate(BaseModel):
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

    model_config = {
        "from_attributes": True
    }


# 応答用（外部出力用）
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

    model_config = {
        "from_attributes": True
    }


# UplinkCommand 登録用
class UplinkCommandCreate(BaseModel):
    target_id: str
    command: str


# UplinkCommand 出力用
class UplinkCommandOut(UplinkCommandCreate):
    id: int
    created_at: datetime

    model_config = {
        "from_attributes": True
    }
