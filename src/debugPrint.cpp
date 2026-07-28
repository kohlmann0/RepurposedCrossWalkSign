#include <Arduino.h>
#include "debugPrint.h"

#if defined(AttachDebugger) && AttachDebugger == 1
#include "avr8-stub.h"
void DebugPrint(String message) {
  // Do Nothing, the Serial output is disabled when the debugger is attached to avoid conflicts with the debugger's serial communication.
}
#else
void DebugPrint(String message) {
  Serial.println(message);
}
#endif