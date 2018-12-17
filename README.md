# Sand Display
15x7 LED display flashing based on accelerometer inputs

Scope: Document the IS31FL3731 LED DRIVER and its cross-plexing feature for nRF52832

Recently I discovered this LED SAND project: https://www.bhoite.com/2018/01/led-sand-animation/
I wanted to try for myself and bought the Charlieplex Featherwing from Adafruit.com and the LIS3DH Accelerometer.

Charlieplex: https://learn.adafruit.com/adafruit-15x7-7x15-charlieplex-led-matrix-charliewing-featherwing/overview
Accelerometer: https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/overview

The accelerometer is simple to setup, please look at the code. This document will mostly focus on how to setup the IS31FL3731 driver chip.

# IS31FL3731

Please refer to datasheet: http://www.issi.com/WW/pdf/31FL3731.pdf

Communication with the IS31 is done through TWI(I2C) protocol. While the driver supports 144 LEDs, the Charlieplex comes with 105 LEDs.

## Cross-plexing
The LED's are driven by the "cross-plexing" feature. The correct term is "Charlieplexing". https://en.wikipedia.org/wiki/Charlieplexing

Charlieplexing on the IS31FL3731:

