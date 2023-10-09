#include <stdint.h>

void AES_Decrytion(uint8_t block[4][4], uint32_t *key_words, int method)
{
    int KEY_SIZES[3] = {128, 192, 256}; // 32*4 32*6 | 32*8;
    int ROUND_N_S[3] = {10, 12, 14};

    int key_size = KEY_SIZES[method];
    int key_words_len = (int)(key_size / 32);
    int round_n = ROUND_N_S[method];
    int round_key_n = round_n + 1;

    uint8_t sbox[256];
    initialize_aes_sbox(sbox);

    // ================================
    uint32_t *W = inv_key_schedule(key_words, key_words_len, round_key_n, sbox);


    AddRoundKey(block, W);
    W += 4;


    for (int i = 0; i < round_n - 1; i++)
    {
        SubBytes(block, sbox);


        ShiftRows(block);
        

        MixColumns(block);
        AddRoundKey(block, W);
        W += 4;
    }
    // Final Round
    SubBytes(block, sbox);
    ShiftRows(block);
    AddRoundKey(block, W);
    W += 4;


}


// InvAddRoundKey = AddRoundKey
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

// inv_subbytes
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

void InvShiftRows(uint8_t block[4][4])
{
    uint8_t tmp[4];
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // tmp[j] = block[i][(j + i)%4];
            tmp[j] = block[i][(j - i)%4];
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
