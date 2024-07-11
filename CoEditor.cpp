#include <thread>
#include <chrono>
#include "BoundedBuffer.h"

class CoEditor {
private:
    BoundedBuffer &queue;
    BoundedBuffer &screen_manager_queue;

public:
    CoEditor(BoundedBuffer &queue, BoundedBuffer &screen_manager_queue)
        : queue(queue), screen_manager_queue(screen_manager_queue) {}

    void edit() {
        bool done = false;
        while (!done) {
            char* msg = queue.remove();
            if (std::strcmp(msg, "DONE") != 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                screen_manager_queue.insert(msg);
            } else {
                done = true;
                screen_manager_queue.insert(msg);
            }
        }
    }
};
