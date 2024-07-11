#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <cstring>
#include "BoundedBuffer.h"

class Producer {
private:
    int id;
    int num_products;
    BoundedBuffer &buffer;

public:
    Producer(int id, int num_products, BoundedBuffer &buffer)
        : id(id), num_products(num_products), buffer(buffer) {}

    void produce() {
        const char* types[] = {"SPORTS", "NEWS", "WEATHER"};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 2);

        for (int i = 0; i < num_products; ++i) {
            int type_index = dis(gen);
            std::string message = "Producer " + std::to_string(id) + " " + types[type_index] + " " + std::to_string(i);
            char* msg = new char[message.length() + 1];
            std::strcpy(msg, message.c_str());
            buffer.insert(msg);
        }
        char* done_msg = new char[5];
        std::strcpy(done_msg, "DONE");
        buffer.insert(done_msg);
    }
};
