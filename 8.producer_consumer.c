#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5 // Size of buffer

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = i + 1;  // Producing item

        sem_wait(&empty); // Wait if buffer is full
        pthread_mutex_lock(&mutex); // Enter critical section

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Signal item available

        sleep(1); // Sleep to simulate time
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full); // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Enter critical section

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Signal space available

        sleep(2); // Sleep to simulate time
    }
    return NULL;
}

int main() {
    pthread_t prodThread, consThread;

    sem_init(&empty, 0, SIZE); // Initially all slots are empty
    sem_init(&full, 0, 0);     // Initially no items in buffer
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

// gcc producer_consumer.c -lpthread -o producer_consumer
// ./producer_consumer
