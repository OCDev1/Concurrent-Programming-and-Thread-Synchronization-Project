#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"

class Producer {
public:
    Producer(int id, int num_products, BoundedBuffer &buffer);
    void produce();

private:
    int id;
    int num_products;
    int sports_counter;
    int news_counter;
    int weather_counter;
    BoundedBuffer &buffer;

    int getCounter(int type_index);
    void incrementCounter(int type_index);
};

#endif // PRODUCER_H
