#include "DownlinkData.h"
#include <string.h>

DownlinkData::DownlinkData()
{
    clear();
}

void DownlinkData::clear()
{
    packet.clear();

    // データ初期化
    header = 0;
    packetType = 0;
    id = 0;
    timestamp = 0;
    latitude = 0.0f;
    longitude = 0.0f;
    altitude = 0.0f;
    temperature = 0;
    pressure = 0;
    humidity = 0;
    imuRoll = 0;
    imuPitch = 0;
    imuYaw = 0;
}

// セッター
void DownlinkData::setHeader(uint16_t value) { header = value; }
void DownlinkData::setPacketType(uint16_t value) { packetType = value; }
void DownlinkData::setID(uint32_t value) { id = value; }
void DownlinkData::setTimestamp(uint32_t value) { timestamp = value; }
void DownlinkData::setLatitude(float value) { latitude = value; }
void DownlinkData::setLongitude(float value) { longitude = value; }
void DownlinkData::setAltitude(float value) { altitude = value; }
void DownlinkData::setTemperature(int16_t value) { temperature = value; }
void DownlinkData::setPressure(uint16_t value) { pressure = value; }
void DownlinkData::setHumidity(uint8_t value) { humidity = value; }
void DownlinkData::setIMURoll(int16_t value) { imuRoll = value; }
void DownlinkData::setIMUPitch(int16_t value) { imuPitch = value; }
void DownlinkData::setIMUYaw(int16_t value) { imuYaw = value; }

// ゲッター
uint16_t DownlinkData::getHeader() const { return header; }
uint16_t DownlinkData::getPacketType() const { return packetType; }
uint32_t DownlinkData::getID() const { return id; }
uint32_t DownlinkData::getTimestamp() const { return timestamp; }
float DownlinkData::getLatitude() const { return latitude; }
float DownlinkData::getLongitude() const { return longitude; }
float DownlinkData::getAltitude() const { return altitude; }
int16_t DownlinkData::getTemperature() const { return temperature; }
uint16_t DownlinkData::getPressure() const { return pressure; }
uint8_t DownlinkData::getHumidity() const { return humidity; }
int16_t DownlinkData::getIMURoll() const { return imuRoll; }
int16_t DownlinkData::getIMUPitch() const { return imuPitch; }
int16_t DownlinkData::getIMUYaw() const { return imuYaw; }

// パケット生成
const uint8_t *DownlinkData::generatePacket(uint8_t &out_size)
{
    packet.clear();

    packet.appendUint16(header);
    packet.appendUint16(packetType);
    packet.appendUint32(id);
    packet.appendUint32(timestamp);
    packet.appendFloat(latitude);
    packet.appendFloat(longitude);
    packet.appendFloat(altitude);
    packet.appendInt16(temperature);
    packet.appendUint16(pressure);
    packet.appendUint8(humidity);
    packet.appendInt16(imuRoll);
    packet.appendInt16(imuPitch);
    packet.appendInt16(imuYaw);

    const uint8_t *baseData = packet.getPacketData();
    uint8_t baseSize = packet.getPacketSize();

    uint16_t crc = CRC16::generate(baseData, baseSize);

    static uint8_t sendBuffer[BinaryPacket::PACKET_MAX_SIZE + 2];
    memcpy(sendBuffer, baseData, baseSize);
    sendBuffer[baseSize] = crc & 0xFF;
    sendBuffer[baseSize + 1] = (crc >> 8) & 0xFF;

    out_size = baseSize + 2;
    return sendBuffer;
}

// パケット解析
bool DownlinkData::parsePacket(const uint8_t *data, uint8_t size)
{
    if (size < 2) return false;

    uint16_t dataLength = size - 2;
    uint16_t crc_calc = CRC16::generate(data, dataLength);
    uint16_t crc_recv = data[dataLength] | (data[dataLength + 1] << 8);

    if (crc_calc == crc_recv)
    {
        packet.setReceivedPacket(data, dataLength);

        // BinaryPacket → データフィールドに展開
        header = packet.getUint16(0);
        packetType = packet.getUint16(2);
        id = packet.getUint32(4);
        timestamp = packet.getUint32(8);
        latitude = packet.getFloat(12);
        longitude = packet.getFloat(16);
        altitude = packet.getFloat(20);
        temperature = packet.getInt16(24);
        pressure = packet.getUint16(26);
        humidity = packet.getUint8(28);
        imuRoll = packet.getInt16(29);
        imuPitch = packet.getInt16(31);
        imuYaw = packet.getInt16(33);

        return true;
    }
    else
    {
        return false;
    }
}

// CRC確認のみ
bool DownlinkData::verifyCRC(const uint8_t *data, uint8_t size)
{
    if (size < 2) return false;

    uint16_t dataLength = size - 2;
    uint16_t crc_calc = CRC16::generate(data, dataLength);
    uint16_t crc_recv = data[dataLength] | (data[dataLength + 1] << 8);

    return (crc_calc == crc_recv);
}
