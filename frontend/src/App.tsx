import { useEffect, useState } from "react";
import RealtimeMap from "./components/RealtimeMap";

interface TelemetryData {
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

function App() {
  const [telemetry, setTelemetry] = useState<TelemetryData | null>(null);

  useEffect(() => {
    const ws = new WebSocket("ws://localhost:8000/ws/telemetry");
    ws.onmessage = (event) => {
      const data = JSON.parse(event.data);
      setTelemetry(data);
    };
    return () => ws.close();
  }, []);

  return (
    <div className="h-screen w-screen">
      <RealtimeMap telemetry={telemetry} />
    </div>
  );
}

export default App;
