#pragma once
#include "BinaryPacket.h"
#include "CRC16.h"
#include <stdint.h>

class DownlinkData
{
public:
    DownlinkData();

    void clear();

    // セッター
    void setHeader(uint16_t value);
    void setPacketType(uint16_t value);
    void setID(uint32_t value);
    void setTimestamp(uint32_t value);
    void setLatitude(float value);
    void setLongitude(float value);
    void setAltitude(float value);
    void setTemperature(int16_t value);
    void setPressure(uint16_t value);
    void setHumidity(uint8_t value);
    void setIMURoll(int16_t value);
    void setIMUPitch(int16_t value);
    void setIMUYaw(int16_t value);

    // ゲッター
    uint16_t getHeader() const;
    uint16_t getPacketType() const;
    uint32_t getID() const;
    uint32_t getTimestamp() const;
    float getLatitude() const;
    float getLongitude() const;
    float getAltitude() const;
    int16_t getTemperature() const;
    uint16_t getPressure() const;
    uint8_t getHumidity() const;
    int16_t getIMURoll() const;
    int16_t getIMUPitch() const;
    int16_t getIMUYaw() const;

    // パケット生成 (送信用データ出力)
    const uint8_t *generatePacket(uint8_t &out_size);

    // パケット解析 (受信時)
    bool parsePacket(const uint8_t *data, uint8_t size);

    // CRC確認のみ
    bool verifyCRC(const uint8_t *data, uint8_t size);

private:
    BinaryPacket packet;
};
