#pragma once
#include "BinaryPacket.h"
#include "CRC16.h"
#include <stdint.h>

class UplinkData
{
public:
    UplinkData();

    void clear();

    // セッター
    void setHeader(uint16_t value);
    void setPacketType(uint16_t value);
    void setID(uint32_t value);
    void setCommandID(uint16_t value);
    void setArg1(uint32_t value);
    void setArg2(uint32_t value);

    // ゲッター
    uint16_t getHeader() const;
    uint16_t getPacketType() const;
    uint32_t getID() const;
    uint16_t getCommandID() const;
    uint32_t getArg1() const;
    uint32_t getArg2() const;

    // パケット生成
    const uint8_t *generatePacket(uint8_t &out_size);

    // パケット解析
    bool parsePacket(const uint8_t *data, uint8_t size);

    // CRC確認のみ
    bool verifyCRC(const uint8_t *data, uint8_t size);

private:
    BinaryPacket packet;

    // データフィールド
    uint16_t header;
    uint16_t packetType;
    uint32_t id;
    uint16_t commandID;
    uint32_t arg1;
    uint32_t arg2;
};
