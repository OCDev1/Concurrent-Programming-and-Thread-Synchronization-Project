#include "Dispatcher.h"
#include <vector>
#include <cstring>
#include <thread>
#include <chrono>
#include <cstddef>

Dispatcher::Dispatcher(std::vector<BoundedBuffer*> &producer_queues, BoundedBuffer &sports_queue, BoundedBuffer &news_queue, BoundedBuffer &weather_queue)
    : producer_queues(producer_queues), sports_queue(sports_queue), news_queue(news_queue), weather_queue(weather_queue) {}

void Dispatcher::dispatch() {
    bool all_done = false;
    std::vector<bool> queue_done(producer_queues.size(), false);

    while (!all_done) {
        all_done = true;
        for (size_t i = 0; i < producer_queues.size(); ++i) {
            if (queue_done[i]) continue;

            char* msg = producer_queues[i]->try_remove();
            if (msg != nullptr) {
                if (std::strcmp(msg, "DONE") == 0) {
                    queue_done[i] = true;
                    delete[] msg;
                } else {
                    all_done = false;
                    if (std::strstr(msg, "SPORTS")) {
                        sports_queue.insert(msg);
                    } else if (std::strstr(msg, "NEWS")) {
                        news_queue.insert(msg);
                    } else if (std::strstr(msg, "WEATHER")) {
                        weather_queue.insert(msg);
                    } else {
                        delete[] msg;
                    }
                }
            } else {
                all_done = false;
            }
        }
        
        if (!all_done) {
            // Sleep for a short duration to avoid busy-waiting
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    // Send DONE messages to consumer queues
    BoundedBuffer* consumer_queues[] = {&sports_queue, &news_queue, &weather_queue};
    for (auto queue : consumer_queues) {
        char* done_msg = new char[5];
        std::strcpy(done_msg, "DONE");
        queue->insert(done_msg);
    }
}