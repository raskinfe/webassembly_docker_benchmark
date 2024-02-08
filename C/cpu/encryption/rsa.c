#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

void generate_key_pair(RSA **rsa_key) {
    BIGNUM *bne = BN_new();
    RSA *rsa = RSA_new();

    // Set the public exponent to 65537 (RSA_F4)
    BN_set_word(bne, RSA_F4);

    // Generate the RSA key pair
    RSA_generate_key_ex(rsa, 2048, bne, NULL);

    // Free the BIGNUM
    BN_free(bne);

    *rsa_key = rsa;
}

void print_key(RSA *rsa_key) {
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa_key, NULL, NULL, 0, NULL, NULL);
    
    char *pem_key;
    long pem_size = BIO_get_mem_data(bio, &pem_key);
    // printf("RSA Private Key:\n%s\n", pem_key);

    BIO_free(bio);
}

int rsa_encrypt(const char *message, RSA *rsa_key, unsigned char **encrypted_message) {
    int rsa_size = RSA_size(rsa_key);
    *encrypted_message = (unsigned char *)malloc(rsa_size);

    int result = RSA_public_encrypt(strlen(message) + 1, (unsigned char *)message, *encrypted_message, rsa_key, RSA_PKCS1_OAEP_PADDING);
    return result;
}

int rsa_decrypt(const unsigned char *encrypted_message, int encrypted_size, RSA *rsa_key, char **decrypted_message) {
    int rsa_size = RSA_size(rsa_key);
    *decrypted_message = (char *)malloc(rsa_size);

    int result = RSA_private_decrypt(encrypted_size, encrypted_message, (unsigned char *)*decrypted_message, rsa_key, RSA_PKCS1_OAEP_PADDING);
    return result;
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock(); // Record the starting time

    RSA *rsa_key = NULL;
    generate_key_pair(&rsa_key);
    
    print_key(rsa_key);

    const char *original_message = "Hello, RSA!";
    // printf("Original Message: %s\n", original_message);

    unsigned char *encrypted_message;
    int encrypted_size = rsa_encrypt(original_message, rsa_key, &encrypted_message);
    // printf("Encrypted Message Size: %d\n", encrypted_size);

    char *decrypted_message;
    int decrypted_size = rsa_decrypt(encrypted_message, encrypted_size, rsa_key, &decrypted_message);
    // printf("Decrypted Message Size: %d\n", decrypted_size);

    // printf("Decrypted Message: %s\n", decrypted_message);

    RSA_free(rsa_key);
    free(encrypted_message);
    free(decrypted_message);

    
    end = clock();   // Record the ending time
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", cpu_time_used);

    return 0;
}
