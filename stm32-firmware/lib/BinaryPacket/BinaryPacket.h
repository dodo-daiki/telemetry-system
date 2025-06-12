#pragma once
#include <stdint.h>

class BinaryPacket{
    public:
        static const uint8_t PACKET_MAX_SIZE = 128;

        BinaryPacket();

        void clear();

        // append系（符号なし）
        void appendUint8(uint8_t value);
        void appendUint16(uint16_t value);
        void appendUint32(uint32_t value);

        // append系（符号あり）
        void appendInt8(int8_t value);
        void appendInt16(int16_t value);
        void appendInt32(int32_t value);

        // append float
        void appendFloat(float value);

        // 受信パケットセット
        void setReceivedPacket(const uint8_t *data, uint8_t size);

        // get系（符号なし）
        uint8_t getUint8(uint8_t index) const;
        uint16_t getUint16(uint8_t index) const;
        uint32_t getUint32(uint8_t index) const;

        // get系（符号あり）
        int8_t getInt8(uint8_t index) const;
        int16_t getInt16(uint8_t index) const;
        int32_t getInt32(uint8_t index) const;

        // get float
        float getFloat(uint8_t index) const;

        // パケットデータ取得
        const uint8_t *getPacketData() const;
        uint8_t getPacketSize() const;

    private:
        uint8_t packetBuffer[PACKET_MAX_SIZE];
        uint8_t packetLen;
};
