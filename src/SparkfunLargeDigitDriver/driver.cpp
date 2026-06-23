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

// Segment mapping for the 7-segment display (common cathode):
  //    __   A
  //   |  |  F/B
  //    --   G
  //   |  |  E/C
  //    --   D

#define a  1<<0
#define b  1<<6
#define c  1<<5
#define d  1<<4
#define e  1<<3
#define f  1<<1
#define g  1<<2
#define dp 1<<7


namespace driver {
  
  byte COUNT_UP_INPUT_PIN = COUNT_UP;
  byte COUNT_DOWN_INPUT_PIN = COUNT_DOWN;

  void setup() {
    // Set segment control pins as OUTPUT
    pinMode(segmentClock, OUTPUT);
    pinMode(segmentLatch, OUTPUT);
    pinMode(segmentData, OUTPUT);
    
    digitalWrite(segmentClock, LOW);
    digitalWrite(segmentData, LOW);
    digitalWrite(segmentLatch, LOW);
  }

  
  //Given a number, or '-', shifts it out to the display
  void postToDisplay(byte number)
  {
    byte segments;

    switch (number)
    {
      case 1: segments = b | c; break;
      case 2: segments = a | b | d | e | g; break;
      case 3: segments = a | b | c | d | g; break;
      case 4: segments = f | g | b | c; break;
      case 5: segments = a | f | g | c | d; break;
      case 6: segments = a | f | g | e | c | d; break;
      case 7: segments = a | b | c; break;
      case 8: segments = a | b | c | d | e | f | g; break;
      case 9: segments = a | b | c | d | f | g; break;
      case 0: segments = a | b | c | d | e | f; break;
      case ' ': segments = 0; break;
      case 'c': segments = g | e | d; break;
      case '-': segments = g; break;
    }

    //Clock these bits out to the drivers (bit-bang each bit of "segments")
    for (byte x = 0 ; x < 8 ; x++)
    {
      digitalWrite(segmentClock, LOW);
      digitalWrite(segmentData, segments & 1 << (7 - x));
      digitalWrite(segmentClock, HIGH); //Data transfers to the register on the rising edge of SRCK
    }
  }

  //Takes a number and displays 2 numbers. Displays absolute value (no negatives)
  void display(int value)
  {
    int number = abs(value); //Remove negative signs and any decimals

    //Serial.print("number: ");
    //Serial.println(number);

    for (byte x = 0 ; x < 2 ; x++)
    {
      int remainder = number % 10;
      postToDisplay(remainder);
      number /= 10;
    }

    //Latch the current segment data
    digitalWrite(segmentLatch, LOW);
    digitalWrite(segmentLatch, HIGH); //Register moves storage register on the rising edge of RCK
  }

}

