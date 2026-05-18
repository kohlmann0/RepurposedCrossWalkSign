#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <driver.h>


volatile int currentValue = 0; // Variable to store the current value displayed on the 7-segment

// put function declarations here:
int clamp(int,  int, int);
void display(int);
void CountUp();
void CountDown();

void setup() {
  Serial.begin(9600);
  Serial.println(F("*** Setting Up MRK ***"));
  
  driver::setup(); // Call the driver setup function to initialize the display and any other necessary components
  
  // Set input interrupts for counting up and down
  pinMode(driver::COUNT_UP_INPUT_PIN, INPUT_PULLUP);
  pinMode(driver::COUNT_DOWN_INPUT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(driver::COUNT_UP_INPUT_PIN), CountUp, FALLING);
  attachInterrupt(digitalPinToInterrupt(driver::COUNT_DOWN_INPUT_PIN), CountDown, FALLING);
  
  driver::display(currentValue); // Initialize display to show 0  
}

void loop() {
  delay(1000); // Sleep for 1000ms to reduce power consumption, but still allow interrupts to wake the device
  Serial.println("Current value: " + String(currentValue)); // Debugging statement to check the current value in the serial monitor
}

void CountUp() {
  currentValue = clamp(currentValue + 1, 0, 9);
  driver::display(currentValue);
}

void CountDown() {  
  currentValue = clamp(currentValue - 1, 0, 9);
  driver::display(currentValue);
}

int clamp(int d, int min, int max) {
  const int t = d < min ? min : d;
  return t > max ? max : t;
}