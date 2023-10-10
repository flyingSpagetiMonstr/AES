#ifndef INCLUDE_AES_FUNCTIONS
#define INCLUDE_AES_FUNCTIONS

#include <stdint.h>
#include <stdio.h>

// get byte from 32bit x with offset from the highest digit (index start with 0)
#define GET_BYTE(x, offset) ((x) << (8*(offset))) >> 8*3

void AddRoundKey(uint8_t block[4][4], uint32_t W[4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            block[j][i] ^= GET_BYTE(W[i], j);
        }
    }
}

void SubBytes(uint8_t block[4][4], uint8_t sbox_or_inverse[256])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            block[i][j] = sbox_or_inverse[block[i][j]];
        }
    }
}

void ShiftRows(uint8_t block[4][4], int inverse)
{
    uint8_t tmp[4];
    // if inverse = 0, sign = 1 else = -1
    int sign[2] = {1, -1};
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[j] = block[i][(j + sign[inverse] * i + 4)%4];
        }
        for (int j = 0; j < 4; j++)
        {
            block[i][j] = tmp[j];
        }
    }
}

void print_b(uint8_t block[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%02X ", block[i][j]);
        }
        puts("");
    }
}

#endif // INCLUDE_AES_FUNCTIONS