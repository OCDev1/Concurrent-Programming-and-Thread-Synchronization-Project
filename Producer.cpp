#include "Producer.h"
#include <iostream>
#include <thread>
#include <random>
#include <cstring>

Producer::Producer(int id, int num_products, BoundedBuffer &buffer)
    : id(id), num_products(num_products), sports_counter(0), news_counter(0), weather_counter(0), buffer(buffer) {}

void Producer::produce() {
    const char* types[] = {"SPORTS", "NEWS", "WEATHER"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);

    for (int i = 0; i < num_products; ++i) {
        int type_index = dis(gen);
        std::string message = "Producer " + std::to_string(id) + " " + types[type_index] + " " + std::to_string(getCounter(type_index));
        char* msg = new char[message.length() + 1];
        std::strcpy(msg, message.c_str());
        buffer.insert(msg);
        incrementCounter(type_index);
    }

    char* done_msg = new char[5];
    std::strcpy(done_msg, "DONE");
    buffer.insert(done_msg);
}

int Producer::getCounter(int type_index) {
    switch (type_index) {
        case 0: return sports_counter;
        case 1: return news_counter;
        case 2: return weather_counter;
        default: return 0;
    }
}

void Producer::incrementCounter(int type_index) {
    switch (type_index) {
        case 0: ++sports_counter; break;
        case 1: ++news_counter; break;
        case 2: ++weather_counter; break;
        default: break;
    }
}
