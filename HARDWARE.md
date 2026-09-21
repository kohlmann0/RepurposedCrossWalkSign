# WalkSign hardware wiring guide

This document summarizes how the sign electronics are wired together for the current SparkFun Large Digit Driver build and links to the build photos captured during construction.

## Overview

The current design uses:

- An Arduino-compatible microcontroller
- Two SparkFun Large Digit Driver boards, one per display digit
- Three control buttons
- A 5V power feed for the logic and display drivers

The driver code expects the following pin assignments:

- Green button: D2
- Red button: D3
- Yellow button: D4
- Segment latch: D5
- Segment clock: D6
- Segment data: D7

## Wiring instructions

### 1. Connect the display driver boards

For each SparkFun Large Digit Driver board:

- Arduino GND -> Driver GND
- Arduino 5V -> Driver 5V
- Arduino D5 -> Driver LAT
- Arduino D6 -> Driver CLK
- Arduino D7 -> Driver SER on the IN side

The display driver boards can be daisy-chained. The OUT connector on the first driver connects to the IN connector on the next driver.

### 2. Button wiring

Connect the control buttons as normally-open momentary switches to the Arduino pins:

- Green button: Arduino D2 to GND through the button
- Red button: Arduino D3 to GND through the button
- Yellow button: Arduino D4 to GND through the button

The code uses INPUT_PULLUP, so the digital pins are pulled high when the button is not pressed and go low when the button is pressed.

### 3. Power wiring

- Connect a stable 5V source to the Arduino and the driver boards.
- Keep the ground common across the Arduino, buttons, and display driver boards.
- If using the old direct-drive layout instead of the SparkFun driver boards, the legacy pin mapping in the project is also available in the source tree and is documented in the driver configuration files.

### 4. Suggested physical layout

- Mount the Arduino close to the control side of the sign.
- Place the digit driver boards near the large display modules or along the power rail.
- Keep the data and clock signal lines short and routed away from high-current power paths.
- Use a common ground between the controller and the driver boards to avoid ghosting or unstable output.

## Wiring notes

The SparkFun driver boards do not behave like a standard I2C display module. They are bit-banged shift-register style modules. The project uses a simple serial stream with latch and clock lines to transfer segment data for each digit. This is why the code writes the segment bits one at a time and then pulses the latch to update the display.

## Build process image gallery

The project images below document the build and assembly process.

This first image is our end goal. I will walk you through some of the basic steps.

<figure>
  <img src="Images/IMG_3786.JPEG" alt="Figure 1: Final build." />
  <figcaption>Figure 1: Final build.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3773.JPEG" alt="Figure 2: I am using multi-wire female Dupont connectors for all my connections. I used a 3-wire connector in this case because it was what I had on hand." />
  <figcaption>Figure 2: I am using multi-wire female Dupont connectors for all my connections. I used a 3-wire connector in this case because it was what I had on hand.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3776.JPEG" alt="Figure 3: Prep the wire for the connector by pulling it apart into three separate wires." />
  <figcaption>Figure 3: Prep the wire for the connector by pulling it apart into three separate wires.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3778.JPEG" alt="Figure 4: Strip back about 1/8 inch." />
  <figcaption>Figure 4: Strip back about 1/8 inch.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3779.JPEG" alt="Figure 5: Female Dupont pin." />
  <figcaption>Figure 5: Female Dupont pin.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3780.JPEG" alt="Figure 6: Place the crimp pin in the crimper with the tabs in the jaw/anvil, and the female portion sticking out." />
  <figcaption>Figure 6: Place the crimp pin in the crimper with the tabs in the jaw/anvil, and the female portion sticking out.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3782.JPEG" alt="Figure 7: Place the wire into the jaw/tabs, with the exposed wire just barely touching the back of the female portion so that, when you crimp, the first tabs hit the wire insulation and the second tabs engage the wire itself." />
  <figcaption>Figure 7: Place the wire into the jaw/tabs, with the exposed wire just barely touching the back of the female portion so that, when you crimp, the first tabs hit the wire insulation and the second tabs engage the wire itself.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3772.JPEG" alt="Figure 8: Finished crimp." />
  <figcaption>Figure 8: Finished crimp.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3774.JPEG" alt="Figure 9: Insert the female pins into the housing." />
  <figcaption>Figure 9: Insert the female pins into the housing.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3775.JPEG" alt="Figure 10: Assemble connector." />
  <figcaption>Figure 10: Assemble connector.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3783.JPEG" alt="Figure 11: Do both ends. Choose a length to match your physical installation." />
  <figcaption>Figure 11: Do both ends. Choose a length to match your physical installation.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3771.JPEG" alt="Figure 12: Connect the output from the first SparkFun driver to the input of the second driver." />
  <figcaption>Figure 12: Connect the output from the first SparkFun driver to the input of the second driver.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3785.JPEG" alt="Figure 13: Make similar cables for the connection to the WalkSign itself. Use your best judgment on length and wiring path, and cut to roughly the correct length." />
  <figcaption>Figure 13: Make similar cables for the connection to the WalkSign itself. Use your best judgment on length and wiring path, and cut to roughly the correct length.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3784.JPEG" alt="Figure 14: Group your wires together to keep them organized." />
  <figcaption>Figure 14: Group your wires together to keep them organized.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3787.JPEG" alt="Figure 15: Terrible picture, but solder your wires to the correct pad on the display driver." />
  <figcaption>Figure 15: Terrible picture, but solder your wires to the correct pad on the display driver.</figcaption>
</figure>

<figure>
  <img src="Images/IMG_3801.JPEG" alt="Figure 16: With my salvaged WalkSign, I used hot glue to secure the components to the back of the sign. Note: the green circuit board had a hard time making a mechanical bond. When in doubt, use more glue." />
  <figcaption>Figure 16: With my salvaged WalkSign, I used hot glue to secure the components to the back of the sign. Note: the green circuit board had a hard time making a mechanical bond. When in doubt, use more glue.</figcaption>
</figure>
  
These are the basic electrical connections you will use on the controller side.

- With my code, 5, 6, and 7 are the data signals going to the display driver, along with 5V supply and ground (GND).
- 2, 3, and 4 (missing in this image) are the Green, Red, and Yellow button inputs, respectively.
- Shown here is my Arduino Uno test bed, but this could also be an Arduino Pro, an ESP32, or something else.

<figure>
  <img src="Images/IMG_3802.JPEG" alt="Figure 17: Controller connections." />
  <figcaption>Figure 17: Controller connections.</figcaption>
</figure>

## References

- Project summary: [README.md](README.md)
- SparkFun driver notes: [src/SparkfunLargeDigitDriver/readme.md](src/SparkfunLargeDigitDriver/readme.md)
- Legacy direct-drive notes: [src/DirectIOPower/readme.md](src/DirectIOPower/readme.md)
