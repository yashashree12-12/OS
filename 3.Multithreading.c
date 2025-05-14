#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep
 
void* print_hello(void* arg) {
    int thread_num = *((int*)arg);
    printf("Hello from thread %d\n", thread_num);
    sleep(1); // Simulate work
    printf("Thread %d finished\n", thread_num);
    return NULL;
}
 
int main() {
    int n;
    printf("Enter number of threads: ");
    scanf("%d", &n);
 
    pthread_t threads[n];
    int thread_ids[n];
 
    for (int i = 0; i < n; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, print_hello, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }
 
    // Wait for all threads to finish
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
 
    printf("All threads completed.\n");
    return 0;
}