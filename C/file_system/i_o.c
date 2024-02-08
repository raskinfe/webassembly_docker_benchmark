#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GB_SIZE 1024LL * 1024LL * 1024LL

#define SOURCE_FILE_SIZE_GB 1
#define TARGET_FILE_SIZE_GB 0.11
#define BUFFER_SIZE 4096

void write_benchmark(const char *source_filename, const char *target_filename) {
    struct timespec start, end;
    FILE *source_file = fopen(source_filename, "rb");
    if (!source_file) {
        perror("Error opening source file for reading");
        exit(EXIT_FAILURE);
    }

    FILE *target_file = fopen(target_filename, "wb");
    if (!target_file) {
        perror("Error opening target file for writing");
        fclose(source_file);
        exit(EXIT_FAILURE);
    }

    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (!buffer) {
        perror("Error allocating memory for buffer");
        fclose(source_file);
        fclose(target_file);
        exit(EXIT_FAILURE);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    long long total_size = (long long)GB_SIZE * TARGET_FILE_SIZE_GB;


    for (size_t i = 0; i < total_size / BUFFER_SIZE; ++i) {
        fread(buffer, 1, BUFFER_SIZE, source_file);
        fwrite(buffer, 1, BUFFER_SIZE, target_file);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Read Time: %f seconds\n", elapsed_time);

    free(buffer);
    fclose(source_file);
    fclose(target_file);
}

int main() {
    const char *source_filename = "source_file.dat";
    const char *target_filename = "target_file.dat";
    struct timespec start, end;

    // Create a source file with 10GB content
    FILE *source_file = fopen(source_filename, "wb");
    if (!source_file) {
        perror("Error opening source file for writing");
        exit(EXIT_FAILURE);
    }

    // Fill the source file with some data
    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (!buffer) {
        perror("Error allocating memory for buffer");
        fclose(source_file);
        exit(EXIT_FAILURE);
    }

    // Fill the buffer with some data
    memset(buffer, 'A', BUFFER_SIZE);

    clock_gettime(CLOCK_MONOTONIC, &start);

    long long total_size = (long long)GB_SIZE * SOURCE_FILE_SIZE_GB;

    for (size_t i = 0; i < total_size / BUFFER_SIZE; ++i) {
        fwrite(buffer, 1, BUFFER_SIZE, source_file);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Write Time: %f seconds\n", elapsed_time);

    free(buffer);
    fclose(source_file);

    // Perform disk I/O benchmark
    write_benchmark(source_filename, target_filename);

    // Clean up: Remove the files
    if (remove(source_filename) != 0) {
        perror("Error deleting the source file");
        exit(EXIT_FAILURE);
    }

    if (remove(target_filename) != 0) {
        perror("Error deleting the target file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
