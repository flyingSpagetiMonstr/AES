#ifndef INCLUDE_MIX_COLUMN
#define INCLUDE_MIX_COLUMN


#define MIX_COL_TEST 0

#include <stdint.h>
#include <string.h>

#include "aes_functions.c" // import GET_BYTE

// int inverse = CONS_MATRIX or CONS_MATRIX_INV
#define CONS_MATRIX 0
#define CONS_MATRIX_INV 1



uint8_t matrices[2][4][4] = {{
    {2, 3, 1, 1},
    {1, 2, 3, 1},
    {1, 1, 2, 3},
    {3, 1, 1, 2}},{
    {0x0E, 0x0B, 0x0D, 0x09},
    {0x09, 0x0E, 0x0B, 0x0D},
    {0x0D, 0x09, 0x0E, 0x0B},
    {0x0B, 0x0D, 0x09, 0x0E}}
};


uint8_t modifier = 0x1B;

#define MUL2(x) (((x) & 0B10000000)?(((x)<<1)^modifier): ((x)<<1))
#define GET_BIT(x, offset) (((uint8_t)((x) << (7 - (offset)))) >> 7)



uint8_t mul2e(uint8_t x, int exp);
uint8_t mul(uint8_t x, uint8_t e);


#if MIX_COL_TEST
#include <stdio.h>
// uint8_t **MixColumns(uint8_t block[4][4]);
int main()
{
    uint8_t x = 0B10101010;
    printf("%X", muls[1](x));
}
#endif


// ===============================================

// void matrix_mul(uint8_t block[4][4])
void MixColumns(uint8_t block[4][4], int inverse)
{
    uint8_t new_block[4][4] = {0};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int cnt = 0; cnt < 4; cnt++)
            {
                new_block[i][j] ^= mul(block[cnt][j], matrices[inverse][i][cnt]);
            }
        }
    }
    memcpy(block, new_block, 4*4*sizeof(uint8_t));
}


uint32_t MixColumns_Word_inv(uint32_t W)
{
    uint8_t new_W_split[4] = {0};
    
    for (int index_new = 0; index_new < 4; index_new++)
    {
        for (int i = 0; i < 4; i++)
        {
            new_W_split[index_new] ^= mul(GET_BYTE(W, i), matrices[1][index_new][i]);
        }
    }

    W = 0;
    for (int index_new = 0; index_new < 4; index_new++)
    {
        W += ((uint32_t)new_W_split[index_new]) << ((3-index_new)*8);
    }

    return W;
}

uint8_t mul2e(uint8_t x, int exp)
{
    for (int i = 0; i < exp; i++)
    {
        x = MUL2(x);
    }
    return x;
}

uint8_t mul(uint8_t x, uint8_t e)
{
    uint8_t r = 0;
    // for (int i = 0; i < 8; i++)
    for (int i = 0; i < 4; i++)
    {
        r ^= GET_BIT(e, i) * mul2e(x, i)  ;
    }
    return r;
}

#endif // INCLUDE_MIX_COLUMN