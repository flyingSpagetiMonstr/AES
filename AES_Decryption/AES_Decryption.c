#include <stdint.h>

#include <stdio.h>

#include "../key_schedule.c"
#include "../S-Box.c"
#include "../mix_column.c"
#include "../aes_functions.c"

void AES_Decrytion(uint8_t block[4][4], uint32_t *key_words, int method)
{
    int inverse = 1;

    int KEY_SIZES[3] = {128, 192, 256};
    int ROUND_N_S[3] = {10, 12, 14};

    int key_size = KEY_SIZES[method];
    int key_words_len = (int)(key_size / 32);
    int round_n = ROUND_N_S[method];
    int round_key_n = round_n + 1;

    uint8_t sbox[256] = {0}, inverse_sbox[256] = {0};

    // combine the 2 functions (maybe) #################################
    initialize_aes_sbox(sbox);
    initialize_inverse_sbox(sbox, inverse_sbox);

    // ==================================================
    uint32_t *W = key_schedule(key_words, key_words_len, round_key_n, sbox);
    // W_len = 4*ROUND_KEY_N
    for (int i = 1; i < 4*round_key_n - 1; i++)
    {
        W[i] = MixColumns_Word_inv(W[i]);
    }
    
    W += 4*round_key_n - 4; 

    AddRoundKey(block, W); W -= 4;

    for (int i = 0; i < round_n - 1; i++)
    {
        ShiftRows(block, inverse);
        SubBytes(block, inverse_sbox);
        AddRoundKey(block, W); W -= 4;
        MixColumns(block, inverse); // ########################
    }

    // Final Round
    ShiftRows(block, inverse);
    SubBytes(block, inverse_sbox);
    AddRoundKey(block, W); // K_0
    // W -= 4;

    puts("After Decryption: ");
    print_b(block);
}