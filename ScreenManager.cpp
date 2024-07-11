#include <iostream>
#include "BoundedBuffer.h"

class ScreenManager {
private:
    BoundedBuffer &queue;

public:
    ScreenManager(BoundedBuffer &queue) : queue(queue) {}

    void display() {
        int done_count = 0;
        while (done_count < 3) {
            char* msg = queue.remove();
            if (std::strcmp(msg, "DONE") == 0) {
                ++done_count;
                delete[] msg;
            } else {
                std::cout << msg << std::endl;
                delete[] msg;
            }
        }
        std::cout << "DONE" << std::endl;
    }
};
