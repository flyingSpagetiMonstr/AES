#define PRINT_BLOCK 1
#define INVERSE 0
#define RUN_EXAMPLE 0
#define SPEED_TEST 1 // SPEED_TEST BY RUNNING EXAMPLE FOR 1024 TIMES

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "AES_Encryption.c"
#include "AES_Decryption.c"

#define BLOCK_SIZE 128
#define NAME_MAX 64


void example(void);

// padding @ end of file (also when no padding need)#########################################

#include <time.h>
clock_t start_time, end_time;
double execution_time;

int main() {
#if SPEED_TEST && RUN_EXAMPLE
    int execution_round = 1024;
    start_time = clock();

    for (int i = 0; i < execution_round; i++)
    {
#endif

#if RUN_EXAMPLE
        example();
#endif

#if SPEED_TEST && RUN_EXAMPLE
    }
    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time of single block: %f seconds\n", execution_time / (execution_round*2));
#endif
#if SPEED_TEST || RUN_EXAMPLE
    exit(0);
#endif



#if !INVERSE
    char *filename = "test.png";
#else
    char *filename = "test.png.aes";
#endif
    char output_file_name[NAME_MAX];

    strcpy(output_file_name, filename);

#if !INVERSE
    strcat(output_file_name, ".aes");
#else
    output_file_name[strlen(output_file_name)-4] = '\0';
    strcat(output_file_name, ".recovery");
#endif



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
    
    // start timing
    puts("Running...");
    start_time = clock();
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
        // printf("Round %d running...\n", cnt);
#if !INVERSE
        AES_Encrytion(block, key_words, method);
#else
        AES_Decrytion(block, key_words, method);
#endif

        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 4; i++)
            {
                fwrite(&block[i][j], sizeof(uint8_t), 1, output_file);
            }
        }
    }
    // end timing
    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time of file encryption/decryption: %f seconds\n", execution_time);

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