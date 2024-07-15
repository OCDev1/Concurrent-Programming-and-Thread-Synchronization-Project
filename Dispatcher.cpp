#include "Dispatcher.h"
#include <cstring>

Dispatcher::Dispatcher(std::vector<BoundedBuffer*> &producer_queues, BoundedBuffer &sports_queue, BoundedBuffer &news_queue, BoundedBuffer &weather_queue)
    : producer_queues(producer_queues), sports_queue(sports_queue), news_queue(news_queue), weather_queue(weather_queue) {}

void Dispatcher::dispatch() {
    bool done = false;
    while (!done) {
        done = true;
        for (auto &queue : producer_queues) {
            char* msg = queue->try_remove(); // Use non-blocking try_remove
            if (msg != nullptr) {
                if (strcmp(msg, "DONE") != 0) {
                    done = false;
                    if (std::strstr(msg, "SPORTS")) {
                        sports_queue.insert(msg);
                    } else if (std::strstr(msg, "NEWS")) {
                        news_queue.insert(msg);
                    } else if (std::strstr(msg, "WEATHER")) {
                        weather_queue.insert(msg);
                    } else {
                        // If message type is not recognized, free it
                        delete[] msg;
                    }
                } else {
                    // Free the "DONE" message
                    delete[] msg;
                }
            }
        }
    }
    char* done_msg = new char[5];
    std::strcpy(done_msg, "DONE");
    sports_queue.insert(done_msg);

    done_msg = new char[5];
    std::strcpy(done_msg, "DONE");
    news_queue.insert(done_msg);

    done_msg = new char[5];
    std::strcpy(done_msg, "DONE");
    weather_queue.insert(done_msg);
}
