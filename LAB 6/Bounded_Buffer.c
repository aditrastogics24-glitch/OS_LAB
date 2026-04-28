#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 15

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty;
sem_t full;

// Mutex lock
pthread_mutex_t mutex;

// Producer function
void *producer(void *arg) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        int item = i;

        sem_wait(&empty);            // wait if buffer is full
        pthread_mutex_lock(&mutex);  // critical section

        buffer[in] = item;
        printf("Produced: %d at buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);             // signal item available

        usleep(100000); // slow down for visibility
    }
    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    for (int i = 0; i < MAX_ITEMS; i++) {

        sem_wait(&full);             // wait if buffer is empty
        pthread_mutex_lock(&mutex);  // critical section

        int item = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);            // signal space available

        usleep(150000); // slow down for visibility
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}