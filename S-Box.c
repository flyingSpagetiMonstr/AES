#ifndef INCLUDE_S_BOX
#define INCLUDE_S_BOX

#define S_BOX_MAIN 0
// S-box(8-bit -> 8bit)
// 2^8 = 256
// in hex its 2 digits

#include <stdint.h>

#define ROTL8(x, shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift)))) // uint8_t: 0~255



#if S_BOX_MAIN
#include <stdio.h>

void initialize_aes_sbox(uint8_t sbox[256]);

int main()
{
    uint8_t sbox[256];
    initialize_aes_sbox(sbox);
    for (int i = 0; i < 256; i++)
    {
        printf("%x ", sbox[i]);
    }
}
#endif


void initialize_aes_sbox(uint8_t sbox[256]) 
{
	// This S-Box code is from wiki
	
	uint8_t p = 1, q = 1;
	
	/* loop invariant: p * q == 1 in the Galois field */
	do
    {
		/* multiply p by 3 */
		p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);

		/* divide q by 3 (equals multiplication by 0xf6) */
		q ^= q << 1;
		q ^= q << 2;
		q ^= q << 4;
		q ^= q & 0x80 ? 0x09 : 0;

		/* compute the affine transformation */
		uint8_t xformed = q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);

		sbox[p] = xformed ^ 0x63;
	} while (p != 1);

	/* 0 is a special case since it has no inverse */
	sbox[0] = 0x63;
}

void initialize_inverse_sbox(uint8_t sbox[256], uint8_t inverse_sbox[256])
{
	// sbox[x] = y; inverse_sbox[y] = x;
	uint8_t y = 0;

	// (uint8_t)255 + 1 = 0
	for (uint8_t x = 0; ; x++)
	{
		y = sbox[x];
		inverse_sbox[y] = x;

		if (x == 255) break;
	}
}

#endif // INCLUDE_S_BOX