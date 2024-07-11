#include "BoundedBuffer.h"
#include <stdexcept>

BoundedBuffer::BoundedBuffer(int size) : size(size) {
    if (sem_init(&empty, 0, size) != 0) {
        throw std::runtime_error("Failed to initialize semaphore");
    }
    if (sem_init(&full, 0, 0) != 0) {
        throw std::runtime_error("Failed to initialize semaphore");
    }
    if (pthread_mutex_init(&mutex, nullptr) != 0) {
        throw std::runtime_error("Failed to initialize mutex");
    }
}

BoundedBuffer::~BoundedBuffer() {
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
}

void BoundedBuffer::insert(char* s) {
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer.push(s);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

char* BoundedBuffer::remove() {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    char* s = buffer.front();
    buffer.pop();
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    return s;
}
