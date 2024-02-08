#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <time.h>

#define AES_256_KEY_SIZE 32  // 256 bits key size

void aes_encrypt(const char *input, const char *key, unsigned char *encrypted_data) {
    AES_KEY aes_key;
    AES_set_encrypt_key((const unsigned char *)key, 256, &aes_key);
    AES_encrypt((const unsigned char *)input, encrypted_data, &aes_key);
}

void aes_decrypt(const unsigned char *encrypted_data, const char *key, unsigned char *decrypted_data) {
    AES_KEY aes_key;
    AES_set_decrypt_key((const unsigned char *)key, 256, &aes_key);
    AES_decrypt(encrypted_data, decrypted_data, &aes_key);
}

void benchmark(int rounds, const char *original_message, const char *aes_key) {
    clock_t start, end;
    double cpu_time_used;

    for (int i = 0; i < rounds; i++) {
        start = clock();

        unsigned char encrypted_data[AES_BLOCK_SIZE];
        aes_encrypt(original_message, aes_key, encrypted_data);

        unsigned char decrypted_data[AES_BLOCK_SIZE];
        aes_decrypt(encrypted_data, aes_key, decrypted_data);

        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("Round %d - CPU time used: %f seconds\n", i + 1, cpu_time_used);
    }
}

int main() {
    const char *original_message = "Hello, AES with 256-bit key!";
    const char *aes_key = "0123456789abcdef0123456789abcdef";  // 256-bit key

    int rounds = 1;
    benchmark(rounds, original_message, aes_key);

    return 0;
}
