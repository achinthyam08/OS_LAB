#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty, full, mutex;

// Producer function
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 15; i++) {
        item = i;

        sem_wait(&empty);   // wait if buffer is full
        sem_wait(&mutex);   // enter critical section

        buffer[in] = item;
        printf("Produced: %d at buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // exit critical section
        sem_post(&full);    // increase filled slots
    }
    pthread_exit(NULL);
}

// Consumer function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 15; i++) {

        sem_wait(&full);    // wait if buffer is empty
        sem_wait(&mutex);   // enter critical section

        item = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // exit critical section
        sem_post(&empty);   // increase empty slots
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t p, c;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // all slots empty
    sem_init(&full, 0, 0);            // no items initially
    sem_init(&mutex, 0, 1);           // binary semaphore

    // Create threads
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
