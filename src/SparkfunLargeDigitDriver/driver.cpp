#include <Arduino.h>
#include "../driver.h"
#include "driver_config.h"

/*
https://www.sparkfun.com/sparkfun-large-digit-driver.html

 Here's how to hook up the Arduino pins to the Large Digit Driver IN
 Arduino pin 6 -> CLK (Green on the 6-pin cable)
 5 -> LAT (Blue)
 7 -> SER on the IN side (Yellow)
 5V -> 5V (Orange)
 Power Arduino with 12V and connect to Vin -> 12V (Red)
 GND -> GND (Black)

 There are two connectors on the Large Digit Driver. 'IN' is the input side that should be connected to
 your microcontroller (the Arduino). 'OUT' is the output side that should be connected to the 'IN' of addtional
 digits.
*/


namespace driver {
  
   byte COUNT_UP_INPUT_PIN = COUNT_UP;
   byte COUNT_DOWN_INPUT_PIN = COUNT_DOWN;
   
void setup() {
  // Set segment control pins as OUTPUT
  pinMode(segmentClock, OUTPUT);
  pinMode(segmentLatch, OUTPUT);
  pinMode(segmentData, OUTPUT);
}
}

