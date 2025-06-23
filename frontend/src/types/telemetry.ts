// src/types/telemetry.ts

export interface TelemetryData {
  packet_type: string;
  station_id: string;
  timestamp: number;
  latitude: number;
  longitude: number;
  altitude_km: number;
  temperature_celsius: number;
  pressure_hpa: number;
  humidity_percent: number;
  imu_roll_deg: number;
  imu_pitch_deg: number;
  imu_yaw_deg: number;
}
