#include <iostream>
#include <queue>
#include <semaphore.h>
#include <pthread.h>
#include <cstring>

class BoundedBuffer {
private:
    int size;
    std::queue<char*> buffer;
    sem_t empty; // Counting semaphore
    sem_t full;  // Counting semaphore
    pthread_mutex_t mutex; // Binary semaphore

public:
    BoundedBuffer(int size) : size(size) {
        sem_init(&empty, 0, size);
        sem_init(&full, 0, 0);
        pthread_mutex_init(&mutex, nullptr);
    }

    ~BoundedBuffer() {
        sem_destroy(&empty);
        sem_destroy(&full);
        pthread_mutex_destroy(&mutex);
    }

    void insert(char* s) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer.push(s);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    char* remove() {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        char* s = buffer.front();
        buffer.pop();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        return s;
    }
};
