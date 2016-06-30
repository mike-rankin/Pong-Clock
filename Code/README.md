Pong Clock
==========

**This is for hardware revision V2.3**
*If you have an earlier version, see the [V2.2](https://github.com/mic159/Pong_Clock/tree/v2.2) branch*

This is the Arduino code for 0miker0's Pong Clock.
It can be purchased at [Tindie](https://www.tindie.com/products/miker/pongclock-complete-kit/ "Pong Clock Complete Kit").

![Pong Clock](https://sites.google.com/site/0miker0/_/rsrc/1378317054480/pongclock/photo%201.JPG?height=293&width=400)

Schematics and further details of the hardware can be found at his website: [0miker0](https://sites.google.com/site/0miker0/pongclock)

Installing
----------
To open the code in the Arduino IDE, you will need to make sure you clone this repository into a directory called "Pong_Clock" (case sensitive).
Then you will need to make sure you have all the correct dependencies installed into the library folder.

To upload the code to the clock itself, you will need an FTDI cable set to 3.3v.
Mike uses [this one from sparkfun](https://www.sparkfun.com/products/9873)

Requirements
------------

 * Adafruit GFX https://github.com/adafruit/Adafruit-GFX-Library
 * Adafriut SSD1306 https://github.com/adafruit/Adafruit_SSD1306
 * RTClib https://github.com/mic159/RTClib

**NOTE:** RTClib is using my fork. This was because I made some modifications to reduce RAM usage.

Arduino SRAM
------------
The 328p chip only has 2KB of RAM, so we need to be careful about what goes into RAM.
The library for the display buffers the entire screen in RAM, which uses up half of it already (128 x 64 / 8 = 1024 bytes), so we dont have much to work with.

One of the other main uses of RAM is usually strings.
To combat this, I have used PROGMEM strings everywhere, mostly by using the FlashStringHelper (the F macro) method.

Unfortunately, virtual methods on classes also use up a bunch of RAM, so I have some uglyness in Menu.cpp to do it all manually.

