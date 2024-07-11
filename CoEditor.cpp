#include "CoEditor.h"
#include <cstring>
#include <thread>
#include <chrono>

CoEditor::CoEditor(BoundedBuffer &queue, BoundedBuffer &screen_manager_queue)
    : queue(queue), screen_manager_queue(screen_manager_queue) {}

void CoEditor::edit() {
    bool done = false;
    while (!done) {
        char* msg = queue.remove();
        if (strcmp(msg, "DONE") != 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            screen_manager_queue.insert(msg);
        } else {
            done = true;
            screen_manager_queue.insert(msg);
        }
    }
}
