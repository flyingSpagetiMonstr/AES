#define MIX_COL_TEST 0

#include <stdint.h>
#include <string.h>
typedef uint8_t elem_t;

elem_t cons_matrix[4][4] = {
    {2, 3, 1, 1},
    {1, 2, 3, 1},
    {1, 1, 2, 3},
    {3, 1, 1, 2}
};

elem_t modifier = 0x1B;

#define MUL2(x) (((x) & 0B10000000)?(((x)<<1)^modifier): ((x)<<1))
#define GET_BIT(x, offset) (((uint8_t)((x) << (7 - (offset)))) >> 7)

uint8_t mul2e(uint8_t x, int exp);
uint8_t mul(uint8_t x, uint8_t e);


#if MIX_COL_TEST
#include <stdio.h>
elem_t **MixColumns(elem_t block[4][4]);
int main()
{
    elem_t x = 0B10101010;
    printf("%X", muls[1](x));
}
#endif


// ===============================================

// void matrix_mul(elem_t block[4][4])
void MixColumns(elem_t block[4][4])
{
    elem_t new_block[4][4] = {0};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int cnt = 0; cnt < 4; cnt++)
            {
                new_block[i][j] ^= mul(block[cnt][j], cons_matrix[i][cnt]);
            }
        }
    }
    memcpy(block, new_block, 4*4*sizeof(elem_t));
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
