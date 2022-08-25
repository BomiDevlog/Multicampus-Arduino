#pragma once

#include <Analog.h>

class Ultra{
protected:
    int echo;
    int trig;
public:
    Ultra(int echo, int trig);
    int getDistance();
};