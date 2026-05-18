#pragma once
#include <Arduino.h>

namespace driver {
    extern byte COUNT_UP_INPUT_PIN;
    extern byte COUNT_DOWN_INPUT_PIN;

    void display(int currentValue);
    void setup();
}