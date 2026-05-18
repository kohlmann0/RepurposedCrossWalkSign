I purchased this old cross-walk sign from a local surplus store. 
- It used to run on 110v-single phase AC and had it's own proprietary control board. 
- I removed the internaal controls and transformers and converted it to a 5v, USB-C powered device running (currently) on an Arduino UNO.
- Right now, it's just a simple count-up/count-down display (I was playing with it as a giant health counter).

The Arduino Uno has a limited number of pins, so I could never fully use the Ten's digit (it only has like 13 pins, and I needed at least 14 pins, plus any buttons I wanted to add).
- I refactored the code using PlatformIO to use test a display driver I got from Sparkfun [https://www.sparkfun.com/sparkfun-large-digit-driver.html](https://www.sparkfun.com/sparkfun-large-digit-driver.html)
- That's what this intial Github push is, the start of that refactor process.

I also created a third configuration to play with an ArduinoProMini, because I had one laying around, and it was a much smaller foot-print than the Uno. [https://www.sparkfun.com/arduino-pro-mini-328-5v-16mhz.html](https://www.sparkfun.com/arduino-pro-mini-328-5v-16mhz.html)

Finally I wired it up, and designed 3D printed a nice housing for it.

I will update this ReadMe when I have some more news/pictures/schematics/3D models.


TODO: Add some pictures of the device, Solidworks or STL files, and a Fritzing wiring diagram.
TODO: Programming wise, give it some different functionality to play with. Timiers/Clocks orjust a regular Serial display from some other device.
