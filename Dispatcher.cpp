#include "Dispatcher.h"
#include <iostream>
#include <cstring>

Dispatcher::Dispatcher(std::vector<BoundedBuffer*> &producer_queues, BoundedBuffer &sports_queue, BoundedBuffer &news_queue, BoundedBuffer &weather_queue)
    : producer_queues(producer_queues), sports_queue(sports_queue), news_queue(news_queue), weather_queue(weather_queue) {}

void Dispatcher::dispatch() {
    bool done = false;
    while (!done) {
        done = true;
        for (auto &queue : producer_queues) {
            char* msg = queue->remove();
            if (std::strcmp(msg, "DONE") != 0) {
                done = false;
                if (std::strstr(msg, "SPORTS")) {
                    sports_queue.insert(msg);
                } else if (std::strstr(msg, "NEWS")) {
                    news_queue.insert(msg);
                } else if (std::strstr(msg, "WEATHER")) {
                    weather_queue.insert(msg);
                }
            } else {
                // Print when "DONE" message is received
                std::cout << "Dispatcher received 'DONE' from Producer." << std::endl;
                delete[] msg;
            }
        }
    }
    char* done_msg = new char[5];
    std::strcpy(done_msg, "DONE");
    sports_queue.insert(done_msg);
    news_queue.insert(done_msg);
    weather_queue.insert(done_msg);
}
