#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];     // one semaphore per fork
sem_t room;         // to prevent deadlock (max N-1 philosophers inside)

void think(int i) {
    printf("Philosopher %d is thinking.\n", i);
    usleep(100000);
}

void eat(int i) {
    printf("Philosopher %d is eating.\n", i);
    usleep(150000);
}

void* philosopher(void* arg) {
    int i = *(int*)arg;

    while (1) {
        think(i);

        sem_wait(&room); // allow only N-1 philosophers to try picking forks

        // pick up forks (left then right)
        sem_wait(&forks[i]);
        printf("Philosopher %d picked up left fork %d.\n", i, i);

        sem_wait(&forks[(i + 1) % N]);
        printf("Philosopher %d picked up right fork %d.\n", i, (i + 1) % N);

        eat(i);

        // put down forks
        sem_post(&forks[i]);
        sem_post(&forks[(i + 1) % N]);

        printf("Philosopher %d put down forks %d and %d.\n",
               i, i, (i + 1) % N);

        sem_post(&room); // leave room
    }
    return NULL;
}

int main() {
    pthread_t phil[N];
    int ids[N];

    // initialize semaphores
    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }

    // join threads (runs indefinitely)
    for (int i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
    }

    return 0;
}