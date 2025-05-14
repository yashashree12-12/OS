// A. program where parent process sorts array elements in descending order and child process sorts
// array elements in descending order.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort_desc(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (arr[i] < arr[j]) {
                int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            }
}

void sort_asc(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (arr[i] > arr[j]) {
                int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            }
}

int main() {
    int arr[] = {5, 2, 9, 1, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process - Ascending sort
        printf("Child process: Sorting in Ascending Order:\n");
        sort_asc(arr, n);
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    }
    else {
        // Parent process - Descending sort
        wait(NULL);  // Wait for child to finish
        printf("Parent process: Sorting in Descending Order:\n");
        sort_desc(arr, n);
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    }
    return 0;
}

// gcc sort_process.c -o sort_process
//./sort_process
