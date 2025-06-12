#pragma once
#include <stdint.h>

class CRC16
{
public:
    // CRC16生成
    static uint16_t generate(const uint8_t *data, uint16_t length);

    // CRC16検証（正しい場合 1 / 間違っている場合 0 を返す）
    static uint8_t verify(const uint8_t *data_with_crc, uint16_t total_length);
};