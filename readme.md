# Contents: AES
- AES by block
  - AES_Encryption.c
  - AES_Decryption.c
- AES by file: AES.c
  - Encryption
  - Decryption

# Mannual
- Set RUN_EXAMPLE to 1 to run block encryption & decryption example.

- Set RUN_EXAMPLE to 0 to run AES by file
  - set INVERSE to 0 to run encryption
  - set INVERSE to 1 to run encryption

- Set PRINT_BLOCK to 1 to print block after/before it's encryption/decryption

- The varaible char *filename of "test.png" stands for the name of file to encrypt, the output would be "test.png.aes", and after decryption it will become "test.png.recovery".

# Notice
- For file encryption, the padding function is not accomplished yet. Currently the last block is padded with 0s defaulty (which may damage the data).