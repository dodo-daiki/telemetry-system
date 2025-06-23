import { useEffect, useState } from 'react';
import type { TelemetryData } from '../types/telemetry';

export const useTelemetryWebSocket = () => {
  const [data, setData] = useState<TelemetryData | null>(null);

  useEffect(() => {
    const ws = new WebSocket('ws://localhost:8000/ws/telemetry');

    ws.onmessage = (event) => {
      try {
        const message = JSON.parse(event.data);

        // "data" フィールドに実データが含まれている構造への対応
        if (message.type === "downlink" && message.data) {
          setData(message.data);
        } else {
          console.warn("無効なデータ形式:", message);
        }
      } catch (err) {
        console.error("JSON解析エラー:", err);
      }
    };

    ws.onerror = (err) => {
      console.error("WebSocket エラー:", err);
    };

    return () => {
      ws.close();
    };
  }, []);

  return data;
};
