#include "BoundedBuffer.h"
#include <mutex>
#include <stdexcept>


BoundedBuffer::BoundedBuffer(size_t capacity) : capacity(capacity) {}

void BoundedBuffer::insert(char* item) {
    std::unique_lock<std::mutex> lock(mutex);
    not_full.wait(lock, [this]() { return buffer.size() < capacity; });
    buffer.push(item);
    not_empty.notify_one();
}

char* BoundedBuffer::remove() {
    std::unique_lock<std::mutex> lock(mutex);
    not_empty.wait(lock, [this]() { return !buffer.empty(); });
    char* item = buffer.front();
    buffer.pop();
    not_full.notify_one();
    return item;
}

char* BoundedBuffer::try_remove() {
    std::unique_lock<std::mutex> lock(mutex);
    if (buffer.empty()) {
        return nullptr;
    } else {
        char* item = buffer.front();
        buffer.pop();
        not_full.notify_one();
        return item;
    }
}
