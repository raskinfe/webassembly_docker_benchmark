#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

void generate_random_password(char *password, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand((unsigned int)time(NULL));
    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    password[length] = '\0';
}

void sha256_hash(const char *input, char *output) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, input, strlen(input));
    SHA256_Final((unsigned char *)output, &ctx);
}

int benchmark_password_hashing() {
    char password[16];
    generate_random_password(password, sizeof(password) - 1);

    char hash[SHA256_DIGEST_LENGTH * 2 + 1];

    // Measure the time it takes to hash the password
    clock_t start = clock();
    sha256_hash(password, hash);
    clock_t end = clock();

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // printf("Generated Password: %s\n", password);
    // printf("Hashed Password: %s\n", hash);
    printf("Time Taken to Hash: %f seconds\n", cpu_time_used);

    return 0;
}

int main() {
    int result = benchmark_password_hashing();

    return result;
}
