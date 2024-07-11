#include "ScreenManager.h"
#include <iostream>
#include <cstring>

ScreenManager::ScreenManager(BoundedBuffer &queue) : queue(queue) {}

void ScreenManager::display() {
    int done_count = 0;
    while (done_count < 3) {
        char* msg = queue.remove();
        if (strcmp(msg, "DONE") == 0) {
            ++done_count;
            delete[] msg;
        } else {
            std::cout << msg << std::endl;
            delete[] msg;
        }
    }
    std::cout << "DONE" << std::endl;
}
