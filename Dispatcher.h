#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include "BoundedBuffer.h"

class Dispatcher {
private:
    std::vector<BoundedBuffer*> &producer_queues;
    BoundedBuffer &sports_queue;
    BoundedBuffer &news_queue;
    BoundedBuffer &weather_queue;

public:
    Dispatcher(std::vector<BoundedBuffer*> &producer_queues, BoundedBuffer &sports_queue, BoundedBuffer &news_queue, BoundedBuffer &weather_queue);
    void dispatch();
};

#endif // DISPATCHER_H
