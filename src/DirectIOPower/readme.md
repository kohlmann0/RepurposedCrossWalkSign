This version of the code uses direct pin addressing (1 pin per LED segment), to drive the large 7-segment display.

Unfortunately, as I've discovered, only the Arduino Mega has enough pins to drive a full 2 digits.

As such, this is a placeholder in case I switch back to a Mega or something. Going forward for now, I'm going to try a different strategy, using two Sparkfun Large Digit Display drivers instead. This will be an interesting experiment, as I've never used them before.
