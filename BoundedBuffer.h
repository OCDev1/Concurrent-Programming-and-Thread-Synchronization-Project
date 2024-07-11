#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H

#include <queue>
#include <semaphore.h>
#include <pthread.h>

class BoundedBuffer {
private:
    int size;
    std::queue<char*> buffer;
    sem_t empty;
    sem_t full;
    pthread_mutex_t mutex;

public:
    BoundedBuffer(int size);
    ~BoundedBuffer();

    void insert(char* s);
    char* remove();
};

#endif // BOUNDEDBUFFER_H
