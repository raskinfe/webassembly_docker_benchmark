#include <stdio.h>
#include <time.h>

void multiplyMatrix(int m1[][4], int m2[][4], int result[][4], int row1, int col1, int row2, int col2) {
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col2; ++j) {
            result[i][j] = 0;
        }
    }

    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col2; ++j) {
            for (int k = 0; k < col1; ++k) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void printMatrix(int matrix[][4], int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int m1[4][4] = {{1, 2, 3, 4},
                    {5, 6, 7, 8},
                    {9, 10, 11, 12},
                    {13, 14, 15, 16}};

    int m2[4][4] = {{1, 0, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}};

    int result[4][4];

    for (int size = 1; size <= 4; ++size) {
        multiplyMatrix(m1, m2, result, size, size, size, size);
    }

    end = clock();   // Record the ending time
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", cpu_time_used);
    return 0;
}
