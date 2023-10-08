#include <limits.h>
#include <stdio.h>
#include <stdint.h>

// int main()
// {
//     // printf("%x", UINT_MAX);
//     printf("%x\n", 
//         ((uint8_t)(0x02*0x87)) ^ ((uint8_t)(0x03 * 0x6E)) ^ ((uint8_t)0x46) ^ ((uint8_t)0xA6)
//     );

//     printf("%x\n", (0x02*0x87));
//     printf("%x\n", (uint8_t)(0x02*0x87));
    
//     return 0;
// }

/*
int a = {44};
printf("%d", a);
*/

int main()
{
    printf("%08X\n", ((uint32_t)0x00012001)^((uint32_t)0x59962200));
    printf("%08X\n", ((uint32_t)0x00012001)^((uint32_t)0x59962200)^((uint32_t)0x01000000));
    printf("%08X\n", ((uint32_t)0x00012001)^((uint32_t)0x59962200)^((uint32_t)0x02000000));
}

// ===============================================================
// #define AES_TEST 1

// #include <stdint.h>

// #include "key_schedule.c"
// #include "S-Box.c"
// #include "mix_column.c"

// #include <stdio.h>

// // #define ROUND_N (9, 11 or 13)
// // block size of 128 bits, and a key size of 128, 192, or 256 bits
// #define BLOCK_SIZE 128

// int KEY_SIZES[3] = {128, 192, 256}; // 32*4 32*6 | 32*8;
// int ROUND_N_S[3] = {10, 12, 14};

// void ShiftRows(uint8_t block[4][4]);
// void SubBytes(uint8_t block[4][4], uint8_t sbox[256]);
// void AddRoundKey(uint8_t block[4][4], uint32_t W[4]);

// void print_b(uint8_t block[4][4]);


// int main()
// {
//     int method = 0;
//     int key_size = KEY_SIZES[method];
//     int key_words_len = (int)(key_size / 32);
//     int round_n = ROUND_N_S[method];
//     int round_key_n = round_n + 1;

//     // int plain_text = 0x 0001 0001 01A1 98AF DA78 1734 8615 3566;
//     uint8_t block[4][4] = {
//         {0x00, 0x01, 0x00, 0x01}, 
//         {0x01, 0xA1, 0x98, 0xAF}, 
//         {0xDA, 0x78, 0x17, 0x34}, 
//         {0x86, 0x15, 0x35, 0x66}
//     };
//     // int key = 0001 2001 7101 98AE DA79 1714 6015 3594
//     // uint32_t key_words[] = {0x00012001, 0x710198AE, 0xDA791714, 0x60153594};
//     uint32_t key_words[] = {0x0f1571c9, 0x47d9e859, 0x0cb7ad, };

//     uint8_t sbox[256];
//     initialize_aes_sbox(sbox);
//     uint32_t *W = key_schedule(key_words, key_words_len, round_key_n, sbox);

// #if AES_TEST
//     puts("Exkey:");
//     for (int i = 0; i < 4*round_key_n; i++)
//     {
//         if (i%4 == 0 && i!=0)
//         {
//             puts("");
//         }
//         printf("%08X\n", W[i]);
//     }
//     puts("");
// #endif
    
   
// }
