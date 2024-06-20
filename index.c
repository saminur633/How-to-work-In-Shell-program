#include <stdio.h>

void bestFit(int blockSize[], int m, int processSize[], int n) {
    // Array to store allocation result of each process
    int allocation[n];
    int fragment[m];

    // Initially no block is assigned to any process
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Pick each process and find the best fit block for it
    for (int i = 0; i < n; i++) {
        // Find the best fit block for current process
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }

        // If a suitable block was found
        if (bestIdx != -1) {
            // Allocate block j to process i
            allocation[i] = bestIdx;
            // Calculate the fragmentation for the allocated block
            fragment[bestIdx] = blockSize[bestIdx] - processSize[i];
            // Reduce available memory in this block
            blockSize[bestIdx] -= processSize[i];
        }
    }

    // Calculate total fragmentation
    int totalFragmentation = 0;
    for (int i = 0; i < m; i++) {
        if (blockSize[i] > 0) {
            totalFragmentation += blockSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }

    printf("\nTotal Fragmentation: %d\n", totalFragmentation);
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    bestFit(blockSize, m, processSize, n);

    return 0;
}

// Compile and run the program using a C compiler, such as gcc:
gcc best_fit.c -o best_fit
./best_fit
