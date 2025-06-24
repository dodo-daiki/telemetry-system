#include <WiFiManager.h>
#include <Arduino.h>

#define RESET_PIN 34
#define LONG_PRESS_TIME 3000  // 3秒

unsigned long pressStart = 0;

void checkButtonAndReset() {
  if (digitalRead(RESET_PIN) == HIGH) {  // HIGH = 押下
    if (pressStart == 0) {
      pressStart = millis();
    } else if (millis() - pressStart > LONG_PRESS_TIME) {
      Serial.println("長押し検出！WiFi設定をリセットします");
      WiFiManager wm;
      wm.resetSettings();
      delay(1000);  // Serial確認用
      ESP.restart();
    }
  } else {
    pressStart = 0;  // 押していないときはカウントリセット
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(RESET_PIN, INPUT);  // 外部プルダウンに対応（内部PULLUPは使わない）
  
  // WiFiManagerで自動接続
  WiFiManager wm;
  if (!wm.autoConnect("ESP32_SetupAP", "12345678")) {
    Serial.println("接続失敗、またはタイムアウト。再起動します。");
    delay(3000);
    ESP.restart();
  }

  Serial.println("WiFiに接続されました。");
}

void loop() {
  checkButtonAndReset();
  // 本来の処理
}
