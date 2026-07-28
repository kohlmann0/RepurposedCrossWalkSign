#include <Arduino.h>
#include "debugPrint.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <driver.h>


volatile int currentValue = 0; // Variable to store the current value displayed on the 7-segment
enum Mode {COUNTING, OTHER_MODE};
volatile Mode currentMode = COUNTING; // Enum to track the current mode of operation 
volatile unsigned long yellowButtonPressStart = 0;
volatile bool yellowButtonIsPressed = false;

// put function declarations here:
int clamp(int,  int, int);
void display(int);
void GreenButtonPressed();
void RedButtonPressed();
void YellowButtonPressed();
void ChangeMode();
void CountUp();
void CountDown();


void setup() {

  #if !(defined(AttachDebugger) && AttachDebugger == 1)
  // If we aren't attaching a debugger, initialize the serial port for the regular Serial output.
  Serial.begin(9600);
  Serial.println(F("*** Setting Up MRK ***"));
  #endif
  
  driver::setup(); // Call the driver setup function to initialize the display and any other necessary components
  
  // Set input interrupts for the buttons
  pinMode(driver::GREEN_BUTTON_INPUT_PIN, INPUT_PULLUP);
  pinMode(driver::RED_BUTTON_INPUT_PIN, INPUT_PULLUP);  
  pinMode(driver::YELLOW_BUTTON_INPUT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(driver::GREEN_BUTTON_INPUT_PIN), GreenButtonPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(driver::RED_BUTTON_INPUT_PIN), RedButtonPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(driver::YELLOW_BUTTON_INPUT_PIN), YellowButtonPressed, CHANGE);
  
  driver::display(currentValue); // Initialize display to show 0  
}

void loop() {
  delay(500); // Sleep to reduce power consumption, but still allow interrupts to wake the device
  DebugPrint("Current value: " + String(currentValue)); // Debugging statement to check the current value in the serial monitor  
  driver::display(currentValue);
}


void ResetToZero() {  
  currentValue = 0;
}

void CountUp() {
  currentValue = clamp(currentValue + 1, 0, 99);
}

void CountDown() {  
  currentValue = clamp(currentValue - 1, 0, 99);
}


void ChangeMode() {  
  DebugPrint(F("ChangeMode function called."));
  // Placeholder, I haven't planned out the other modes yet.

  switch (currentMode) {
    case COUNTING:
      currentMode = OTHER_MODE;
      DebugPrint(F("Switched to OTHER_MODE."));
      break;
    case OTHER_MODE:
      currentMode = COUNTING;
      DebugPrint(F("Switched to COUNTING mode."));
      break;
  }
}

int clamp(int d, int min, int max) {
  const int t = d < min ? min : d;
  return t > max ? max : t;
}


void GreenButtonPressed(){
  switch (currentMode) {
    case COUNTING:
      CountUp();
      break;
    case OTHER_MODE:
      // Handle other mode behavior here
      break;
  }
  driver::display(currentValue);
}

void RedButtonPressed(){
  switch (currentMode) {
    case COUNTING:
      CountDown();
      break;
    case OTHER_MODE:
      // Handle other mode behavior here
      break;
  }
  driver::display(currentValue);
}

void YellowButtonPressed(){
  int buttonState = digitalRead(driver::YELLOW_BUTTON_INPUT_PIN);
  bool yellowButtonWasLongPress = false;
  if (buttonState == LOW) {
    yellowButtonPressStart = millis();
    yellowButtonIsPressed = true;
  } else if (buttonState = HIGH) {
    const unsigned long pressDuration = millis() - yellowButtonPressStart;
    yellowButtonIsPressed = false;
    // Check if the button was held for a long press (e.g., 1 second)
    yellowButtonWasLongPress = (pressDuration >= 1000);    
  }

  if (yellowButtonWasLongPress) {
    ChangeMode();
  } else {
      switch (currentMode) {
      case COUNTING:
        ResetToZero();
        break;
      case OTHER_MODE:      
        ResetToZero();
        break;
    }
  }
}



