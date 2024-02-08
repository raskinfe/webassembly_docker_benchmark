#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lz4.h>
#include <time.h>

#define BUFFER_SIZE 1024

void lz4_compress(const char *input, const char *output) {
    FILE *infile = fopen(input, "rb");
    if (!infile) {
        fprintf(stderr, "Error opening input file: %s\n", input);
        return;
    }

    FILE *outfile = fopen(output, "wb");
    if (!outfile) {
        fprintf(stderr, "Error opening output file: %s\n", output);
        fclose(infile);
        return;
    }

    char in_buf[BUFFER_SIZE];
    char out_buf[BUFFER_SIZE];

    int compressed_size;

    do {
        size_t size = fread(in_buf, 1, BUFFER_SIZE, infile);
        if (size == 0)
            break;

        compressed_size = LZ4_compress_default(in_buf, out_buf, size, BUFFER_SIZE);

        if (compressed_size <= 0) {
            fprintf(stderr, "Error compressing data\n");
            break;
        }

        fwrite(&compressed_size, sizeof(int), 1, outfile);
        fwrite(out_buf, 1, compressed_size, outfile);

    } while (1);

    fclose(infile);
    fclose(outfile);
}

void lz4_decompress(const char *input, const char *output) {
    FILE *infile = fopen(input, "rb");
    if (!infile) {
        fprintf(stderr, "Error opening input file: %s\n", input);
        return;
    }

    FILE *outfile = fopen(output, "wb");
    if (!outfile) {
        fprintf(stderr, "Error opening output file: %s\n", output);
        fclose(infile);
        return;
    }

    char in_buf[BUFFER_SIZE];
    char out_buf[BUFFER_SIZE];

    int compressed_size;

    do {
        if (fread(&compressed_size, sizeof(int), 1, infile) != 1)
            break;

        if (fread(in_buf, 1, compressed_size, infile) != compressed_size) {
            fprintf(stderr, "Error reading compressed data\n");
            break;
        }

        int decompressed_size = LZ4_decompress_safe(in_buf, out_buf, compressed_size, BUFFER_SIZE);

        if (decompressed_size < 0) {
            fprintf(stderr, "Error decompressing data\n");
            break;
        }

        fwrite(out_buf, 1, decompressed_size, outfile);

    } while (compressed_size > 0);

    fclose(infile);
    fclose(outfile);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    const char *input_file = "input.txt";
    const char *compressed_file = "compressed_lz4";
    const char *decompressed_file = "decompressed_lz4.txt";

    // Compress
    lz4_compress(input_file, compressed_file);

    // Decompress
    lz4_decompress(compressed_file, decompressed_file);

     end = clock();   // Record the ending time
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", cpu_time_used);


    return 0;
}
