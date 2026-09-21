#include <Arduino.h>
#include "debugPrint.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <driver.h>
#include "stopwatch_logic.h"

volatile int currentValue = 0; // Variable to store the current value displayed on the 7-segment
enum Mode { COUNTING, STOP_WATCH };
volatile Mode currentMode = COUNTING; // Enum to track the current mode of operation
volatile unsigned long yellowButtonPressStart = 0;
volatile bool yellowButtonIsPressed = false;
volatile bool greenButtonPressedFlag = false;
volatile bool redButtonPressedFlag = false;
volatile bool yellowButtonReleasedFlag = false;
volatile bool yellowButtonLongPressFlag = false;

StopwatchState stopwatchState = {false, 0, 0};

// put function declarations here:
int clamp(int, int, int);
void displayCurrentValue();
void GreenButtonPressed();
void RedButtonPressed();
void YellowButtonPressed();
void ChangeMode();
void CountUp();
void CountDown();
void ResetToZero();
void HandlePendingButtonEvents();
void ToggleStopwatch();
void StopStopwatch();

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

  displayCurrentValue(); // Initialize display to show 0
}

void loop() {
  // Poll the yellow button (no interrupt available on this pin)
  YellowButtonPressed();

  HandlePendingButtonEvents();
  displayCurrentValue();
  delay(50); // Allow updates to appear smoothly while still conserving power
}

void ResetToZero() {
  if (currentMode == STOP_WATCH) {
    stopwatchReset(stopwatchState);
  } else {
    currentValue = 0;
  }
}

void CountUp() {
  currentValue = clamp(currentValue + 1, 0, 99);
}

void CountDown() {
  currentValue = clamp(currentValue - 1, 0, 99);
}

void ToggleStopwatch() {
  stopwatchToggle(stopwatchState, millis());
}

void StopStopwatch() {
  stopwatchStop(stopwatchState, millis());
}

void ChangeMode() {
  DebugPrint(F("ChangeMode function called."));

  if (currentMode == COUNTING) {
    currentMode = STOP_WATCH;
    ResetToZero();
    DebugPrint(F("Switched to STOP_WATCH mode."));
  } else {
    currentMode = COUNTING;
    ResetToZero();
    DebugPrint(F("Switched to COUNTING mode."));
  }
}

int clamp(int d, int min, int max) {
  const int t = d < min ? min : d;
  return t > max ? max : t;
}

void displayCurrentValue() {
  if (currentMode == STOP_WATCH) {
    driver::display(stopwatchDisplayValue(stopwatchState, millis()));
  } else {
    driver::display(currentValue);
  }
}

void HandlePendingButtonEvents() {
  if (greenButtonPressedFlag) {
    greenButtonPressedFlag = false;

    if (currentMode == COUNTING) {
      CountUp();
    } else {
      ToggleStopwatch();
    }
  }

  if (redButtonPressedFlag) {
    redButtonPressedFlag = false;

    if (currentMode == COUNTING) {
      CountDown();
    } else {
      StopStopwatch();
    }
  }

  if (yellowButtonReleasedFlag) {
    yellowButtonReleasedFlag = false;

    if (yellowButtonLongPressFlag) {
      yellowButtonLongPressFlag = false;
      ChangeMode();
    } else {
      ResetToZero();
    }
  }
}

void GreenButtonPressed() {
  greenButtonPressedFlag = true;
}

void RedButtonPressed() {
  redButtonPressedFlag = true;
}

void YellowButtonPressed() {
  const int buttonState = digitalRead(driver::YELLOW_BUTTON_INPUT_PIN);

  if (buttonState == LOW) {
    yellowButtonPressStart = millis();
    yellowButtonIsPressed = true;
  } else if (yellowButtonIsPressed) {
    const unsigned long pressDuration = millis() - yellowButtonPressStart;
    yellowButtonIsPressed = false;
    yellowButtonReleasedFlag = true;
    yellowButtonLongPressFlag = (pressDuration >= 1000);
  }
}


