#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>

class BoundedBuffer {
public:
    BoundedBuffer(size_t capacity);
    void insert(char* item);
    char* remove();
    char* try_remove();
    std::mutex& getMutex() {
        return buffer_mutex;
    }

private:
    std::queue<char*> buffer;
    std::mutex mutex;
    std::condition_variable not_empty;
    std::condition_variable not_full;
    size_t capacity;
    std::mutex buffer_mutex;
};

#endif // BOUNDEDBUFFER_H
