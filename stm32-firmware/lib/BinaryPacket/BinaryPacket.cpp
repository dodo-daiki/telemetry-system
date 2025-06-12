#include "BinaryPacket.h"
#include <string.h>

BinaryPacket::BinaryPacket() : packetLen(0)
{
    memset(packetBuffer, 0, PACKET_MAX_SIZE);
}

void BinaryPacket::clear()
{
    packetLen = 0;
    memset(packetBuffer, 0, PACKET_MAX_SIZE);
}

// 符号なし append
void BinaryPacket::appendUint8(uint8_t value)
{
    if (packetLen + 1 <= PACKET_MAX_SIZE)
        packetBuffer[packetLen++] = value;
}

void BinaryPacket::appendUint16(uint16_t value)
{
    if (packetLen + 2 <= PACKET_MAX_SIZE)
    {
        packetBuffer[packetLen++] = value & 0xFF;
        packetBuffer[packetLen++] = (value >> 8) & 0xFF;
    }
}

void BinaryPacket::appendUint32(uint32_t value)
{
    if (packetLen + 4 <= PACKET_MAX_SIZE)
    {
        for (uint8_t i = 0; i < 4; i++)
            packetBuffer[packetLen++] = (value >> (8 * i)) & 0xFF;
    }
}

// 符号あり append
void BinaryPacket::appendInt8(int8_t value)
{
    appendUint8(*(uint8_t *)&value);
}

void BinaryPacket::appendInt16(int16_t value)
{
    appendUint16(*(uint16_t *)&value);
}

void BinaryPacket::appendInt32(int32_t value)
{
    appendUint32(*(uint32_t *)&value);
}

// float append
void BinaryPacket::appendFloat(float value)
{
    if (packetLen + 4 <= PACKET_MAX_SIZE)
    {
        memcpy(&packetBuffer[packetLen], &value, sizeof(float));
        packetLen += 4;
    }
}

// 受信パケットセット
void BinaryPacket::setReceivedPacket(const uint8_t *data, uint8_t size)
{
    if (size > PACKET_MAX_SIZE) size = PACKET_MAX_SIZE;
    memcpy(packetBuffer, data, size);
    packetLen = size;
}

// 符号なし get
uint8_t BinaryPacket::getUint8(uint8_t index) const
{
    return packetBuffer[index];
}

uint16_t BinaryPacket::getUint16(uint8_t index) const
{
    uint16_t value = packetBuffer[index] | (packetBuffer[index + 1] << 8);
    return value;
}

uint32_t BinaryPacket::getUint32(uint8_t index) const
{
    uint32_t value = 0;
    for (uint8_t i = 0; i < 4; i++)
        value |= (packetBuffer[index + i] << (8 * i));
    return value;
}

// 符号あり get
int8_t BinaryPacket::getInt8(uint8_t index) const
{
    int8_t value;
    value = *(int8_t *)&packetBuffer[index];
    return value;
}

int16_t BinaryPacket::getInt16(uint8_t index) const
{
    int16_t value;
    uint16_t uvalue = getUint16(index);
    value = *(int16_t *)&uvalue;
    return value;
}

int32_t BinaryPacket::getInt32(uint8_t index) const
{
    int32_t value;
    uint32_t uvalue = getUint32(index);
    value = *(int32_t *)&uvalue;
    return value;
}

// float get
float BinaryPacket::getFloat(uint8_t index) const
{
    float value;
    memcpy(&value, &packetBuffer[index], sizeof(float));
    return value;
}

// パケットデータ取得
const uint8_t *BinaryPacket::getPacketData() const
{
    return packetBuffer;
}

uint8_t BinaryPacket::getPacketSize() const
{
    return packetLen;
}
