#include "UplinkData.h"
#include <string.h> // memcpy

UplinkData::UplinkData()
{
    clear();
}

void UplinkData::clear()
{
    packet.clear();

    // データ初期化
    header = 0;
    packetType = 0;
    id = 0;
    commandID = 0;
    arg1 = 0;
    arg2 = 0;
}

// セッター
void UplinkData::setHeader(uint16_t value) { header = value; }
void UplinkData::setPacketType(uint16_t value) { packetType = value; }
void UplinkData::setID(uint32_t value) { id = value; }
void UplinkData::setCommandID(uint16_t value) { commandID = value; }
void UplinkData::setArg1(uint32_t value) { arg1 = value; }
void UplinkData::setArg2(uint32_t value) { arg2 = value; }

// ゲッター
uint16_t UplinkData::getHeader() const { return header; }
uint16_t UplinkData::getPacketType() const { return packetType; }
uint32_t UplinkData::getID() const { return id; }
uint16_t UplinkData::getCommandID() const { return commandID; }
uint32_t UplinkData::getArg1() const { return arg1; }
uint32_t UplinkData::getArg2() const { return arg2; }

// パケット生成
const uint8_t *UplinkData::generatePacket(uint8_t &out_size)
{
    packet.clear();

    packet.appendUint16(header);
    packet.appendUint16(packetType);
    packet.appendUint32(id);
    packet.appendUint16(commandID);
    packet.appendUint32(arg1);
    packet.appendUint32(arg2);

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
bool UplinkData::parsePacket(const uint8_t *data, uint8_t size)
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
        commandID = packet.getUint16(8);
        arg1 = packet.getUint32(10);
        arg2 = packet.getUint32(14);

        return true;
    }
    else
    {
        return false;
    }
}

// CRC確認のみ
bool UplinkData::verifyCRC(const uint8_t *data, uint8_t size)
{
    if (size < 2) return false;

    uint16_t dataLength = size - 2;
    uint16_t crc_calc = CRC16::generate(data, dataLength);
    uint16_t crc_recv = data[dataLength] | (data[dataLength + 1] << 8);

    return (crc_calc == crc_recv);
}
