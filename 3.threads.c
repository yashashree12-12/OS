#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Function to be run by thread
void* print_message(void* arg) {
    char* message = (char*)arg;
    for (int i = 0; i < 5; i++) {
        printf("%s - %d\n", message, i + 1);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, print_message, "Thread 1");
    pthread_create(&thread2, NULL, print_message, "Thread 2");

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished executing.\n");
    return 0;
}

// How to Compile and Run (on Linux/WSL):
// Save the code as threads.c

// Compile it with the pthread library:

// bash
// Copy code
// gcc threads.c -o threads -lpthread
// Run the program:

// bash
// Copy code
// ./threads
// ✅ Sample Output:
// mathematica
// Copy code
// Thread 1 - 1
// Thread 2 - 1
// Thread 1 - 2
// Thread 2 - 2
// Thread 1 - 3
// Thread 2 - 3
// Thread 1 - 4
// Thread 2 - 4
// Thread 1 - 5
// Thread 2 - 5
// Both threads have finished executing.