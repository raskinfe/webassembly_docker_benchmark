#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (file_descriptor == -1) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }

    // Write to the file
    const char *content = "Hello, Wasmer!\n";
    ssize_t bytes_written = write(file_descriptor, content, strlen(content));

    if (bytes_written == -1) {
        fprintf(stderr, "Error writing to file: %s\n", filename);
        close(file_descriptor);
        return 1;
    }

    printf("File '%s' written successfully.\n", filename);

    // Close the file
    close(file_descriptor);

    return 0;
}
