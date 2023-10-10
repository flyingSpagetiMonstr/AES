#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define PRINT_BLOCK 1
#include "AES_Encryption/AES_Encryption.c"
#include "AES_Decryption/AES_Decryption.c"

#define BLOCK_SIZE 128
#define NAME_MAX 64

void example(void);

// padding @ end of file #########################################

int main() {
    example();
exit(0);

    char *filename = "test.png";
    char output_file_name[NAME_MAX];

    strcpy(output_file_name, filename);
    strcat(output_file_name, ".aes");

    FILE* original_file = fopen(filename, "rb"); // Open the original_file in binary mode
    FILE* output_file = fopen(output_file_name, "wb"); // Open the original_file in binary mode

    if (original_file == NULL) {
        printf("Failed to open the original_file.\n");
        return 1;
    }
    if (output_file == NULL) {
        printf("Failed to open the output_file.\n");
        return 1;
    }

    int flag = 1;
    uint8_t block[4][4] = {0};
    uint32_t key_words[] = {0x00012001, 0x710198AE, 0xDA791714, 0x60153594};
    int method = 0;
    int cnt = 0;

    while (flag)
    {
        memset(block, 0, 4*4*sizeof(uint8_t));
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 4; i++)
            {
                flag = fread(&block[i][j], sizeof(uint8_t), 1, original_file);
            }
        }
        cnt++;
        printf("Encryption round %d running...\n", cnt);
        AES_Encrytion(block, key_words, method);
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 4; i++)
            {
                fwrite(&block[i][j], sizeof(uint8_t), 1, output_file);
            }
        }
    }
    
    fclose(original_file);
    fclose(output_file);

    return 0;
}



void example(void)
{
    uint8_t block[4][4] = {
        {0x00, 0x01, 0xDA, 0x86},
        {0x01, 0xA1, 0x78, 0x15},
        {0x00, 0x98, 0x17, 0x35},
        {0x01, 0xAF, 0x34, 0x66}
    };
    uint32_t key_words[] = {0x00012001, 0x710198AE, 0xDA791714, 0x60153594};
    int method = 0;

    AES_Encrytion(block, key_words, method);
    AES_Decrytion(block, key_words, method);
    
}

// Original block:
// 00 01 DA 86
// 01 A1 78 15
// 00 98 17 35
// 01 AF 34 66
// Result:
// 6C 8F D2 1A
// DD 56 3B 65
// 59 42 47 42
// 6B CB 98 2A