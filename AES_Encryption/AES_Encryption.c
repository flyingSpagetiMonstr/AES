// #define PRINT_BLOCK 0

#define AES_ENCRYTION_MAIN 0

#define AES_KEY_EX_TEST 0
#define AES_ADD_R_K_TEST 0
#define AES_R_TEST 0

#include <stdint.h>

#include "key_schedule.c"
#include "S-Box.c"
#include "new_mix.c"
// #include "mix_column.c"

#include <stdio.h>

// #define ROUND_N (9, 11 or 13)
// block size of 128 bits, and a key size of 128, 192, or 256 bits

void ShiftRows(uint8_t block[4][4]);
void SubBytes(uint8_t block[4][4], uint8_t sbox[256]);
void AddRoundKey(uint8_t block[4][4], uint32_t W[4]);

void print_b(uint8_t block[4][4]);

#if AES_ENCRYTION_MAIN
void AES_Encrytion(uint8_t block[4][4], uint32_t *key_words, int method);
int main()
{    
    uint8_t block[4][4] = {
        {0x00, 0x01, 0xDA, 0x86},
        {0x01, 0xA1, 0x78, 0x15},
        {0x00, 0x98, 0x17, 0x35},
        {0x01, 0xAF, 0x34, 0x66}
    };
    uint32_t key_words[] = {0x00012001, 0x710198AE, 0xDA791714, 0x60153594};
    
    AES_Encrytion(block, key_words, 0);
    
}
#endif

void AES_Encrytion(uint8_t block[4][4], uint32_t *key_words, int method)
{
    int KEY_SIZES[3] = {128, 192, 256}; // 32*4 32*6 | 32*8;
    int ROUND_N_S[3] = {10, 12, 14};

    int key_size = KEY_SIZES[method];
    int key_words_len = (int)(key_size / 32);
    int round_n = ROUND_N_S[method];
    int round_key_n = round_n + 1;

    // int plain_text = 0x 0001 0001 01A1 98AF DA78 1734 8615 3566;
#if PRINT_BLOCK
    puts("Original block:");
    print_b(block);
#endif

    // int key = 0001 2001 7101 98AE DA79 1714 6015 3594
    
    uint8_t sbox[256];
    initialize_aes_sbox(sbox);
    uint32_t *W = key_schedule(key_words, key_words_len, round_key_n, sbox);

#if AES_KEY_EX_TEST
    puts("Exkey:");
    for (int i = 0; i < 4*round_key_n; i++)
    {
        if (i%4 == 0 && i!=0)
        {
            puts("");
        }
        printf("%08X\n", W[i]);
    }
    puts("");
#endif

#if AES_ADD_R_K_TEST
    puts("W:");
    for (int i = 0; i < 4; i++)
    {
        printf("%08X ", W[i]);
    }
    puts("");
#endif

    AddRoundKey(block, W);
    W += 4;

#if AES_ADD_R_K_TEST
    puts("After add:");
    print_b(block);
#endif

    for (int i = 0; i < round_n - 1; i++)
    {
        SubBytes(block, sbox);

#if AES_R_TEST
        puts("Before Shift:");
        print_b(block);
#endif

        ShiftRows(block);
        
#if AES_R_TEST
        puts("After Shift:");
        print_b(block);
#endif

        MixColumns(block);
        AddRoundKey(block, W);
        W += 4;
    }
    // Final Round
    SubBytes(block, sbox);
    ShiftRows(block);
    AddRoundKey(block, W);
    W += 4;

#if PRINT_BLOCK
    puts("Result:");
    print_b(block);
#endif

}

void AddRoundKey(uint8_t block[4][4], uint32_t W[4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            block[j][i] ^= (W[i] << (8*j)) >> 8*3;
        }
    }
}

void SubBytes(uint8_t block[4][4], uint8_t sbox[256])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            block[i][j] = sbox[block[i][j]];
        }
    }
}

void ShiftRows(uint8_t block[4][4])
{
    uint8_t tmp[4];
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[j] = block[i][(j + i)%4];
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
