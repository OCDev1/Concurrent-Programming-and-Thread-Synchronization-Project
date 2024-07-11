#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "BoundedBuffer.h"

class ScreenManager {
private:
    BoundedBuffer &queue;

public:
    ScreenManager(BoundedBuffer &queue);
    void display();
};

#endif // SCREENMANAGER_H
