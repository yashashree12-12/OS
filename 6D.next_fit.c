#include <stdio.h>

#define MAX_BLOCKS   5
#define MAX_PROCESSES 4

int main() {
    int block_size[MAX_BLOCKS]   = {100, 500, 200, 300, 600};
    int process_size[MAX_PROCESSES] = {212, 417, 112, 426};
    int allocation[MAX_PROCESSES];
    int last_alloc = 0;  // Start searching from block 0

    // Initialize allocations to -1 (not allocated)
    for (int i = 0; i < MAX_PROCESSES; i++) {
        allocation[i] = -1;
    }

    // For each process, perform Next-Fit allocation
    for (int i = 0; i < MAX_PROCESSES; i++) {
        int count = 0;
        int j = last_alloc;

        // Traverse up to MAX_BLOCKS blocks, wrapping around
        while (count < MAX_BLOCKS) {
            if (block_size[j] >= process_size[i]) {
                // Allocate process i to block j
                allocation[i] = j;
                block_size[j] -= process_size[i];
                last_alloc = j;  // Update last_alloc for next search
                break;
            }
            j = (j + 1) % MAX_BLOCKS;
            count++;
        }
        // if count == MAX_BLOCKS and no block found, allocation[i] stays -1
    }

    // Print results
    printf("Process No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("%d\t\t%d\t\t", i + 1, process_size[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}


// gcc -o next_fit next_fit.c
// ./next_fit
