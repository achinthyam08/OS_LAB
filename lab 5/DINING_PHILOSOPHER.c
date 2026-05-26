#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];        // one semaphore per fork
sem_t room;            // limits philosophers entering (avoids deadlock)

// Philosopher function
void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Try to enter room
        sem_wait(&room);

        // Pick up forks
        sem_wait(&forks[id]);                 // left fork
        printf("Philosopher %d picked up left fork %d\n", id, id);

        sem_wait(&forks[(id + 1) % N]);       // right fork
        printf("Philosopher %d picked up right fork %d\n", id, (id + 1) % N);

        // Eat
        printf("Philosopher %d is eating\n", id);
        sleep(2);

        // Put down forks
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        printf("Philosopher %d put down forks %d and %d\n",
               id, id, (id + 1) % N);

        // Leave room
        sem_post(&room);

        sleep(1);
    }
}

int main() {
    pthread_t thread[N];
    int ids[N];

    // Initialize semaphores
    sem_init(&room, 0, N - 1);  // allow max N-1 philosophers

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&thread[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (they actually run infinitely)
    for (int i = 0; i < N; i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}
