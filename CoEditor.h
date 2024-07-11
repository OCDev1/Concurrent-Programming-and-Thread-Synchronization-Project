#ifndef COEDITOR_H
#define COEDITOR_H
#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <cstring>

#include "BoundedBuffer.h"

class CoEditor {
private:
    BoundedBuffer &queue;
    BoundedBuffer &screen_manager_queue;

public:
    CoEditor(BoundedBuffer &queue, BoundedBuffer &screen_manager_queue);
    void edit();
};

#endif // COEDITOR_H
