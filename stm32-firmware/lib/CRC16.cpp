#include "CRC16.h"

// CRC16生成
uint16_t CRC16::generate(const uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFF;

    for (uint16_t pos = 0; pos < length; pos++)
    {
        crc ^= (uint16_t)data[pos];
        for (uint8_t i = 0; i < 8; i++)
        {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }

    return crc;
}

// CRC16検証（正しい場合 1 / 間違っている場合 0 を返す）
uint8_t CRC16::verify(const uint8_t *data_with_crc, uint16_t total_length)
{
    if (total_length < 2) return 0; // CRC付が無い → エラー扱い

    uint16_t data_length = total_length - 2;
    uint16_t crc_calc = generate(data_with_crc, data_length);
    uint16_t crc_recv = data_with_crc[data_length] | (data_with_crc[data_length + 1] << 8);

    if (crc_calc == crc_recv){
        return 1; // 正しい
    }else{
        return 0; // 間違い
    }
}
