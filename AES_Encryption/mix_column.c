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

elem_t mul1(elem_t x);
elem_t mul2(elem_t x);
elem_t mul3(elem_t x);

elem_t (*muls[])(elem_t) = {NULL, mul1, mul2, mul3};


#if MIX_COL_TEST
#include <stdio.h>
elem_t **matrix_mul(elem_t block[4][4]);
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
                new_block[i][j] ^= muls[cons_matrix[i][cnt]](block[cnt][j]);
            }
        }
    }
    memcpy(block, new_block, 4*4*sizeof(elem_t));
}


elem_t mul1(elem_t x)
{
    return x;
}
elem_t mul2(elem_t x)
{
    return (x & 0B10000000)?((x<<1)^modifier): (x<<1);
}
elem_t mul3(elem_t x)
{
    return x^mul2(x);
}


// elem_t mul(elem_t x, elem_t a)
// {
//     switch (a)
//     {
//     case 1:
//         return x;
//         break;
//     case 2:
//         return (x & 0B10000000)?((x<<1)^modifier): (x<<1);
//         break;
//     case 3:
//         return 
//         break;
//     default:
//         break;
//     }
    
// } 