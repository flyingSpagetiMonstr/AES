# AES
This project is an assignment of my Cryptology course at 3rd year.
- AES by block
  - AES_Encryption.c
  - AES_Decryption.c
- AES by file: AES.c
  - Encryption
  - Decryption

# Mannual
- Set RUN_EXAMPLE to 1 to run block encryption & decryption example
  - Set SPEED_TEST to 1 to test speed of example encryption/decryption

- Set RUN_EXAMPLE to 0 to run AES by file
  - set INVERSE to 0 to run encryption
  - set INVERSE to 1 to run decryption

- Set PRINT_BLOCK to 1 to print block after/before it's encryption/decryption

- [test.png]
==encryption==> [test.png,aes] 
==decryption==> [test.png.recovery] 

# Notice
- For file encryption, it's simply encrypting every blocks in the file (i.e., not following any encryption policy).
- The padding function is not complemented yet, and currently the last block is padded with 0s defaulty (which might damage the data), and when decrypting, the 0s wont get deleted after decryption.