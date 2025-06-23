import { useTelemetryWebSocket } from '../hooks/useTelemetryWebSocket';

const Home = () => {
  const telemetry = useTelemetryWebSocket();

  return (
    <div className="min-h-screen bg-gray-100 px-4 py-8">
      <div className="max-w-4xl mx-auto bg-white shadow-lg rounded-lg p-6">
        <h1 className="text-3xl font-bold text-center text-gray-800 mb-6">
          🌐 リアルタイムテレメトリ表示
        </h1>

        {telemetry ? (
          <div className="grid grid-cols-1 md:grid-cols-3 gap-6 text-gray-700">
            {/* 📍 位置情報 */}
            <div className="bg-blue-50 rounded-lg p-4 shadow-inner">
              <h2 className="font-semibold text-lg mb-2">📍 位置情報</h2>
              <p>緯度: {telemetry.latitude}</p>
              <p>経度: {telemetry.longitude}</p>
              <p>高度: {telemetry.altitude_km} km</p>
            </div>

            {/* 🌡️ 環境情報 */}
            <div className="bg-green-50 rounded-lg p-4 shadow-inner">
              <h2 className="font-semibold text-lg mb-2">🌡️ 環境情報</h2>
              <p>気温: {telemetry.temperature_celsius} ℃</p>
              <p>湿度: {telemetry.humidity_percent} %</p>
              <p>気圧: {telemetry.pressure_hpa} hPa</p>
            </div>

            {/* 🧭 姿勢情報 */}
            <div className="bg-yellow-50 rounded-lg p-4 shadow-inner">
              <h2 className="font-semibold text-lg mb-2">🧭 姿勢情報</h2>
              <p>Roll: {telemetry.imu_roll_deg}°</p>
              <p>Pitch: {telemetry.imu_pitch_deg}°</p>
              <p>Yaw: {telemetry.imu_yaw_deg}°</p>
            </div>
          </div>
        ) : (
          <p className="text-center text-gray-500">データ待機中...</p>
        )}
      </div>
    </div>
  );
};

export default Home;
