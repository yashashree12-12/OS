#include <stdio.h>

#define MAX_BLOCKS 5
#define MAX_PROCESSES 3

int main() {
    int block_size[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    int process_size[MAX_PROCESSES] = {212, 417, 112};
    int allocation[MAX_PROCESSES];

    for (int i = 0; i < MAX_PROCESSES; i++) {
        allocation[i] = -1;  // No block allocated initially
    }

    for (int i = 0; i < MAX_PROCESSES; i++) {
        int max_diff = -1, block_index = -1;
        for (int j = 0; j < MAX_BLOCKS; j++) {
            if (block_size[j] >= process_size[i]) {
                int diff = block_size[j] - process_size[i];
                if (diff > max_diff) {
                    max_diff = diff;
                    block_index = j;
                }
            }
        }

        if (block_index != -1) {
            allocation[i] = block_index;
            block_size[block_index] -= process_size[i];
        }
    }

    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("%d\t\t%d\t\t", i + 1, process_size[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}

// gcc -o worst_fit worst_fit.c
// ./worst_fit
