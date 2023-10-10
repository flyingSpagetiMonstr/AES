#ifndef INCLUDE_KEY_SCHEDULE
#define INCLUDE_KEY_SCHEDULE


#define KEY_SCHEDULE_TEST 0

#include <stdlib.h> 
#include <stdint.h>
// #include "S-Box.c" 

#define RotWord(x) ((x) << 8 | (x) >> (32 - 8))

uint32_t SubWord(uint32_t x, uint8_t sbox[256]);


uint32_t rcon[11] = {
    0xffffffff,
    0x01000000, 0x02000000, 
    0x04000000, 0x08000000, 
    0x10000000, 0x20000000, 
    0x40000000, 0x80000000, 
    0x1B000000, 0x36000000
};

#if KEY_SCHEDULE_TEST
#include <stdio.h> 
#include "S-Box.c"
uint32_t *key_schedule(
    uint32_t *key_words /*(K)*/, 
    int N /*(KEY_WORD_N) 4, 6, 8*/, 
    int ROUND_KEY_N /*R*/,
    uint8_t sbox[256]);

int main()
{
    uint8_t sbox[256];
    initialize_aes_sbox(sbox);

    uint32_t in = 0xabcdef12;
    // printf("%x", RotWord(in));
    // printf("%x", SubWord(in));
    // SubWord(in, sbox);
    uint32_t Key[] = {0x12345678, 0x12345678, 0x12345678, 0x12345678}; // N = 4 
    uint32_t *W = key_schedule(Key, 4, 11, sbox);
    for (int i = 0; i < 4*11; i++)
    {
        printf("%x ", W[i]);
    }
}

#endif

//====================================================

uint32_t *key_schedule(
    uint32_t *key_words /*(K)*/, 
    int N /*(KEY_WORD_N) 4, 6, 8*/, 
    int ROUND_KEY_N /*R*/,
    uint8_t sbox[256]) 
{
    int W_len = 4*ROUND_KEY_N;
    uint32_t *W;
    W = (uint32_t*) malloc(W_len*sizeof(uint32_t));
    // K_0~K_{N-1}: 32-bit WORDS of KEY
    // W_0~W_{4*R-1}: l = 4R*Word = R*(128-bit) 

    int i = 0;
    for (; i < N; i++)
    {
        W[i] = key_words[i]; 
    }
    
    for (; i < 4*ROUND_KEY_N; i++)
    {
        if (i % N == 0)
        {
            // subbyte? rotl?
            W[i] = W[i-N]^SubWord(RotWord(W[i-1]), sbox)^(rcon[(int)(i/N)]);
        }
        else if((N > 6) && (i % N == 4))
        {
            W[i] = W[i-N]^SubWord(W[i-1], sbox);
        }
        else
        {
            W[i] = W[i-N]^W[i-1];
        }
    }
    return W;
}

uint32_t SubWord(uint32_t x, uint8_t sbox[256]) // sbox or inverse_sbox
{
    uint8_t x_s[4];
    uint32_t output = 0;
    for (int i = 0; i < 4; i++)
    {
        x_s[i] = (x << (8*i)) >> 3*8;
        // printf("%x ", x_s[i]);

        // code under this line are not checked yet_________
        x_s[i] = sbox[x_s[i]];
        output += (uint32_t)x_s[i] << (3-i)*8;
    }
    return output;
}

// void new_round_keys(uint32_t *W, int ROUND_KEY_N, uint8_t inverse_sbox[256])
// {
//     int W_len = 4*ROUND_KEY_N;

//     uint32_t *D = (uint32_t*) malloc(W_len*sizeof(uint32_t));

//     for (int i = 1; i < W_len - 1; i++)
//     {
//         // SubWord(W[i], inverse_sbox);
//     }
    
// }

#endif // INCLUDE_KEY_SCHEDULE
