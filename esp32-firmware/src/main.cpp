#include <WiFiManager.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define RESET_PIN 34
#define LONG_PRESS_TIME 3000  // ミリ秒（3秒）

const char* serverURL = "http://192.168.10.102:8000/api/downlink_data";

unsigned long pressStart = 0;
unsigned long lastPostTime = 0;

void checkButtonAndReset() {
  if (digitalRead(RESET_PIN) == HIGH) {
    if (pressStart == 0) {
      pressStart = millis();
    } else if (millis() - pressStart > LONG_PRESS_TIME) {
      Serial.println("長押し検出！WiFi設定をリセットします");
      WiFiManager wm;
      wm.resetSettings();
      delay(1000);
      ESP.restart();
    }
  } else {
    pressStart = 0;
  }
}

void checkServerConnection() {
  const char* host = "192.168.10.102";  // ← serverURL の IP 部分に合わせる
  const uint16_t port = 8000;

  WiFiClient client;
  Serial.printf("サーバー %s:%d に接続中...\n", host, port);

  if (client.connect(host, port)) {
    Serial.println("✅ サーバーに接続成功！");
    client.stop();
  } else {
    Serial.println("❌ サーバーに接続失敗（ポート未開放 or サーバー停止中）");
  }
}

void sendTelemetryData() {
  StaticJsonDocument<512> jsonDoc;
  jsonDoc["packet_type"] = "telemetry";
  jsonDoc["station_id"] = "GS01";
  jsonDoc["timestamp"] = (uint32_t)(millis() / 1000);
  jsonDoc["latitude"] = random(-9000, 9000) / 100.0;
  jsonDoc["longitude"] = random(-18000, 18000) / 100.0;
  jsonDoc["altitude_km"] = random(0, 3000) / 100.0;
  jsonDoc["temperature_celsius"] = random(-2000, 4000) / 100.0;
  jsonDoc["pressure_hpa"] = random(9500, 10500) / 10.0;
  jsonDoc["humidity_percent"] = random(0, 100);
  jsonDoc["imu_roll_deg"] = random(-18000, 18000) / 100.0;
  jsonDoc["imu_pitch_deg"] = random(-9000, 9000) / 100.0;
  jsonDoc["imu_yaw_deg"] = random(0, 36000) / 100.0;

  String jsonStr;
  serializeJson(jsonDoc, jsonStr);

  HTTPClient http;
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(jsonStr);
  Serial.printf("POST結果: %d\n", httpCode);
  if (httpCode > 0) {
    String response = http.getString();
    Serial.println("レスポンス: " + response);
  }
  http.end();
}

void setup() {
  Serial.begin(115200);
  pinMode(RESET_PIN, INPUT);  // 外部プルダウン前提

  WiFiManager wm;
  if (!wm.autoConnect("ESP32_SetupAP", "12345678")) {
    Serial.println("WiFi接続失敗、再起動します。");
    delay(3000);
    ESP.restart();
  }

  Serial.println("WiFiに接続されました");

  Serial.println("WiFi接続先: " + WiFi.SSID());
  Serial.println("ESP32 IP: " + WiFi.localIP().toString());
  Serial.println("接続先URL: " + String(serverURL));

  checkServerConnection();
}

void loop() {
  checkButtonAndReset();

  if (millis() - lastPostTime >= 5000) {
    lastPostTime = millis();
    sendTelemetryData();
  }
}
