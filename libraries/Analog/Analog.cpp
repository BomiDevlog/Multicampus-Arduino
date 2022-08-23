#include "Analog.h"

Analog::Analog(int pin, int to_min, int to_max):
    pin(pin),
    from_min(0), from_max(1023),
    to_min(to_min), to_max(to_max){
}

void Analog::setRange(int to_min, int to_max) {
    this->to_min = to_min;
    this->to_max = to_max;
}

int Analog::read() {
    int value = analogRead(pin);
    return map(value, from_min, from_max, to_min, to_max);
}