#include <Arduino.h>
#include "../driver.h"
#include "driver_config.h"
/*
 This driver is for a direct IO power control circuit, which uses two buttons to count up and down a value displayed on a 7-segment display. The buttons are connected to pins 2 and 3, and the segments of the display are connected to pins 4-10 for the ones digit, and 11-17 for the tens digit (currently not used, but set as OUTPUT for future expansion).
 The driver uses interrupts to detect button presses, and updates the display accordingly. The value is clamped between 0 and 9 for the ones digit, and between 0 and 99 for the tens digit (currently not used).
 The driver also includes a delay in the main loop to reduce power consumption, while still allowing interrupts to wake the device.
*/


namespace driver {

   byte COUNT_UP_INPUT_PIN = COUNT_UP;
   byte COUNT_DOWN_INPUT_PIN = COUNT_DOWN;

  // Segment map for digits 0-9 (Common Cathode)
  // Positions flow clockwise starting from the top center segment, with the middle segment last:
  // [0] = Top Center
  // [1] = Top Right
  // [2] = Bottom Right
  // [3] = Bottom Center
  // [4] = Bottom Left
  // [5] = Top Left
  // [6] = Middle
  byte DIGIT_MAP[10][7] = {
    {1,1,1,1,1,1,0}, // 0
    {0,1,1,0,0,0,0}, // 1
    {1,1,0,1,1,0,1}, // 2
    {1,1,1,1,0,0,1}, // 3
    {0,1,1,0,0,1,1}, // 4
    {1,0,1,1,0,1,1}, // 5
    {1,0,1,1,1,1,1}, // 6
    {1,1,1,0,0,0,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,0,1,1}  // 9
  };
  // Are the LED's wired with a common anode (or cathode)?
  const bool IS_COMMON_ANODE = true; // true = invert, false = normal

  /* Function Declarations */
  void displayOnesDigit(int);
  void displayTensDigit(int);


  void setup() {
   

    // Set all one's digit segment pins as OUTPUT
    pinMode(ONES_TOP_CENTER , OUTPUT);
    pinMode(ONES_TOP_RIGHT , OUTPUT);
    pinMode(ONES_BOTTOM_RIGHT , OUTPUT);
    pinMode(ONES_BOTTOM_CENTER , OUTPUT);
    pinMode(ONES_BOTTOM_LEFT , OUTPUT);
    pinMode(ONES_TOP_LEFT , OUTPUT);
    pinMode(ONES_MIDDLE , OUTPUT);

    // Tens Digits (NOTE: currently not used, but set as OUTPUT for future expansion)
    // Set all ten's digitsegment pins as OUTPUT
    // pinMode( TENS_TOP_CENTER , OUTPUT);
    // pinMode( TENS_TOP_RIGHT , OUTPUT);
    // pinMode( TENS_BOTTOM_RIGHT , OUTPUT);
    // pinMode( TENS_BOTTOM_CENTER , OUTPUT);
    // pinMode( TENS_BOTTOM_LEFT , OUTPUT);
    // pinMode( TENS_TOP_LEFT , OUTPUT);
    // pinMode( TENS_MIDDLE , OUTPUT);
  }

  void display(int value) {
    displayOnesDigit(value % 10); // Display the ones digit  
    // displayTensDigit(value / 10); // Display the tens digit
  }

  // *** NOTE: Important, electrically, the LED segments on this display are active when the pin is LOW.
  // This is because the LED's share a common Hot (5v), and each signal is pulled to Ground to turn on the segment. 
  // So, the logic is inverted when writing to the pins.
  // To accommodate this, I have added inversion logic, if needed.
  void writeSegment(uint8_t pin, uint8_t value) {
    digitalWrite(pin, value ^ IS_COMMON_ANODE);
  }

  void displayOnesDigit(int digit) {
    writeSegment(ONES_TOP_CENTER, DIGIT_MAP[digit][0]);
    writeSegment(ONES_TOP_RIGHT, DIGIT_MAP[digit][1]);
    writeSegment(ONES_BOTTOM_RIGHT, DIGIT_MAP[digit][2]);
    writeSegment(ONES_BOTTOM_CENTER, DIGIT_MAP[digit][3]);
    writeSegment(ONES_BOTTOM_LEFT, DIGIT_MAP[digit][4]);
    writeSegment(ONES_TOP_LEFT, DIGIT_MAP[digit][5]);
    writeSegment(ONES_MIDDLE, DIGIT_MAP[digit][6]);
  }
  // Right now, I only  have enough IO pins for a single digit, but this is how I would display the tens digit if I had more pins available.
  void displayTensDigit(int digit) {
    writeSegment(TENS_TOP_CENTER, DIGIT_MAP[digit][0]);
    writeSegment(TENS_TOP_RIGHT, DIGIT_MAP[digit][1]);
    writeSegment(TENS_BOTTOM_RIGHT, DIGIT_MAP[digit][2]);
    writeSegment(TENS_BOTTOM_CENTER, DIGIT_MAP[digit][3]);
    writeSegment(TENS_BOTTOM_LEFT, DIGIT_MAP[digit][4]);
    writeSegment(TENS_TOP_LEFT, DIGIT_MAP[digit][5]);
    writeSegment(TENS_MIDDLE, DIGIT_MAP[digit][6]);
  }
}