#pragma once
#include <Arduino.h>

namespace driver {
    extern byte GREEN_BUTTON_INPUT_PIN;
    extern byte RED_BUTTON_INPUT_PIN;    
    extern byte YELLOW_BUTTON_INPUT_PIN;


    void display(int currentValue);
    void setup();
}