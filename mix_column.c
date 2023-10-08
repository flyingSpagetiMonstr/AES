#define MIX_COL_TEST 0

#include <stdint.h>
#include <string.h>

uint8_t cons_matrix[4][4] = {
    {2, 3, 1, 1},
    {1, 2, 3, 1},
    {1, 1, 2, 3},
    {3, 1, 1, 2}
};

uint8_t cons_matrix_inv[4][4] = {
    {0x0E, 0x0B, 0x0D, 0x09},
    {0x09, 0x0E, 0x0B, 0x0D},
    {0x0D, 0x09, 0x0E, 0x0B},
    {0x0B, 0x0D, 0x09, 0x0E}
};

uint8_t ***matrices = {cons_matrix, cons_matrix_inv};

uint8_t modifier = 0x1B;

#define MUL2(x) (((x) & 0B10000000)?(((x)<<1)^modifier): ((x)<<1))
#define GET_BIT(x, offset) (((uint8_t)((x) << (7 - (offset)))) >> 7)

uint8_t mul2e(uint8_t x, int exp);
uint8_t mul(uint8_t x, uint8_t e);


#if MIX_COL_TEST
#include <stdio.h>
uint8_t **MixColumns(uint8_t block[4][4]);
int main()
{
    uint8_t x = 0B10101010;
    printf("%X", muls[1](x));
}
#endif


// ===============================================

// void matrix_mul(uint8_t block[4][4])
void MixColumns(uint8_t block[4][4])
{
    uint8_t new_block[4][4] = {0};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int cnt = 0; cnt < 4; cnt++)
            {
                new_block[i][j] ^= mul(block[cnt][j], matrices[0][i][cnt]);
            }
        }
    }
    memcpy(block, new_block, 4*4*sizeof(uint8_t));
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
    for (int i = 0; i < 8; i++)
    {
        r ^= GET_BIT(e, i) * mul2e(x, i)  ;
    }
    return r;
}