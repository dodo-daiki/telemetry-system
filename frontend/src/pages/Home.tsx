// Home.tsx
import { useTelemetryWebSocket } from '../hooks/useTelemetryWebSocket';

const Home = () => {
  const telemetry = useTelemetryWebSocket();

  console.log("受信データ:", telemetry); // ここを追加！

  return (
    <div>
      <h1>リアルタイムテレメトリ表示</h1>
      {telemetry ? (
        <div>
          <p>緯度: {telemetry.latitude}</p>
          <p>経度: {telemetry.longitude}</p>
          <p>高度: {telemetry.altitude_km} km</p>
          <p>気温: {telemetry.temperature_celsius} ℃</p>
        </div>
      ) : (
        <p>データ待機中...</p>
      )}
    </div>
  );
};

export default Home;
