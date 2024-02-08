#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap arr[i+1] and arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Function to perform Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Find the pivot index such that elements smaller than the pivot are on the left
        // and elements greater than the pivot are on the right
        int pivotIndex = partition(arr, low, high);

        // Recursively sort the sub-arrays
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    srand(time(NULL));
    int size = 10000;
    int *arr = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < 10000; i++) {
        int randomNumber = getRandomNumber(1, 10000);
        arr[i] = randomNumber;
    }
    // Perform Quick Sort
    // printArray(arr, size);
    // printf("\n=================\n");
    quickSort(arr, 0, size - 1);
    // printArray(arr, 10);
    end = clock();   // Record the ending time
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    free(arr);

    printf("CPU time used: %f seconds\n", cpu_time_used);
    return 0;
}
