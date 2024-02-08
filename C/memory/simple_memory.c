#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int i = 0;
    // Allocate 1 MB of memory in each iteration
    while (i < 60) {
        void* mem = malloc(1024 * 1024); // 1 MB
        if (mem == NULL) {
            printf("error");
            perror("malloc");
            break; // Exit the loop if malloc fails
        }
        
        printf("i: %d \n", i);
        sleep(1);
        i++;
    }

    // The program will never reach this point in normal execution
    return 0;
}
