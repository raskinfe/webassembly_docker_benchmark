#include <stdio.h>
#include <string.h>
#include <time.h>

void compressRLE(char *input) {
    int length = strlen(input);

    for (int iter = 0; iter < 100000; iter++) {
        for (int i = 0; i < length; i++) {
            int count = 1;

            // Count occurrences of the current character
            while (i < length - 1 && input[i] == input[i + 1]) {
                count++;
                i++;
            }

            // Print the character and its count
            // printf("%c%d", input[i], count);
        }
    }
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    // Example input string
    char input[] = "AAAABBBCCDAA";

    // Perform CPU-intensive Run-Length Encoding
    compressRLE(input);

    end = clock();   // Record the ending time
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", cpu_time_used);

    return 0;
}
