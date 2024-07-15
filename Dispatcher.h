#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include "BoundedBuffer.h"

class Dispatcher {
public:
    Dispatcher(std::vector<BoundedBuffer*> &producer_queues, BoundedBuffer &sports_queue, BoundedBuffer &news_queue, BoundedBuffer &weather_queue);
    void dispatch();

private:
    std::vector<BoundedBuffer*> &producer_queues;
    BoundedBuffer &sports_queue;
    BoundedBuffer &news_queue;
    BoundedBuffer &weather_queue;
};

#endif // DISPATCHER_H