from fastapi import APIRouter, Depends, Response
from sqlalchemy.orm import Session
from app.database import get_db
from app import crud

router = APIRouter(tags=["telemetry_log_kml"])

@router.get("/telemetry_log.kml", response_class=Response)
def get_telemetry_log_kml(limit: int = 100, db: Session = Depends(get_db)):
    """
    テレメトリログをKML形式で取得（最大 `limit` 件まで）
    """
    logs = crud.get_all_telemetry_logs(db, limit=limit)

    kml_header = """<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://www.opengis.net/kml/2.2">
  <Document>
    <name>Telemetry Log</name>
    <description>Flight path and telemetry data</description>
"""

    placemarks = ""
    for log in logs:
        placemarks += f"""
    <Placemark>
      <name>{log.timestamp}</name>
      <description><![CDATA[
        Station: {log.station_id}<br/>
        Altitude: {log.altitude_km} km<br/>
        Temp: {log.temperature_celsius} °C<br/>
        Pressure: {log.pressure_hpa} hPa<br/>
        Humidity: {log.humidity_percent} %<br/>
        IMU: Roll={log.imu_roll_deg}°, Pitch={log.imu_pitch_deg}°, Yaw={log.imu_yaw_deg}°
      ]]></description>
      <Point>
        <coordinates>{log.longitude},{log.latitude},{log.altitude_km * 1000}</coordinates>
      </Point>
    </Placemark>
"""

    kml_footer = """
  </Document>
</kml>
"""

    kml_data = kml_header + placemarks + kml_footer
    return Response(content=kml_data, media_type="application/vnd.google-earth.kml+xml")
