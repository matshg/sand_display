# Sand Display
15x7 LED display flashing based on accelerometer inputs.

## Scope:
Directly and clearly document the IS31FL3731 LED DRIVER and its cross-plexing feature for nRF52832

Recently I discovered this LED SAND project: https://www.bhoite.com/2018/01/led-sand-animation/
I wanted to try for myself and bought the Charlieplex Featherwing and LIS3DH Accelerometer.

Charlieplex: https://learn.adafruit.com/adafruit-15x7-7x15-charlieplex-led-matrix-charliewing-featherwing/overview
Accelerometer: https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/overview

The accelerometer is simple to setup, look at the code. This document will focus on the IS31FL3731 driver chip (IS31).

## IS31FL3731
Datasheet: http://www.issi.com/WW/pdf/31FL3731.pdf

### Register Control
To control the LED's, the register's on the IS31 are configured through a menu. Here's how to turn on all 105 of the LED's.

Note: The IS31 can drive 144 LEDs. The Charlieplex comes with 105 LEDs. The remaining 39 LED's outputs must be off by LED control register (frame registers) else if on it will affect other LEDs.

I will explain the TWI (I2C) commands in this format: "TWI TX: "TWI_INSTANCE", "IS31_SLAVE_ADDRESS", "IS31_REGISTER", "IS31_DATA""

#### 1. Make FUNCTION REGISTER AVAILABLE
TWI TX: &m_twi, 0x74, 0xFD (COMMAND REG), 0x0B

Description: Select the COMMAND REGISTER and write: 0x0B (0000 1011).
By writing 0x0B the Function Register is available. Now we can access the Configuration Register (0x00), Picture Display Register (0x01), Auto Play Control Register 1 (0x02), Auto Play Control Register 2 (0x03), RESERVED, Display Option Register (0x05), Audio Synchronization Register (0x06), Frame State Register (0x07), Breath Control Register 1 (0x08), Breath Control Register 2 (0x09), Shutdown Register (0x0A), AGC Control Register (0x0B), Audio ADC Rate Register (0x0C)

#### 2. SHUTDOWN MODE
TWI TX: &m_twi, 0x74, 0x0A (SHUTDOWN REG), 0x00

Description: Select the SHUTDOWN REGISTER and write: 0x00 (0000 0000).

The IS31 is in shutdown mode.

#### 3. Make FUNCTION REGISTER AVAILABLE
TWI TX: &m_twi, 0x74, 0xFD (COMMAND REG), 0x0B

#### 4. NORMAL OPERATION MODE
TWI TX: &m_twi, 0x74, 0x0A (SHUTDOWN REG), 0x01

Description: Select SHUTDOWN REGISTER and write: 0x01 (0000 0001).

The IS31 is in normal operation mode.

#### 5. Make FUNCTION REGISTER AVAILABLE
TWI TX: &m_twi, 0x74, 0xFD (COMMAND REG), 0x0B

#### 6. Configure PICTURE DISPLAY REGISTER
TWI TX: &m_twi, 0x74, 0x01 (PICTURE FRAME REG), 0x00

Description: Select the PICTURE DISPLAY REGISTER and write: 0x00 (0000 0000).

Set FRAME 1 in PICTURE MODE

#### 7. Make FRAME 1 REGISTER AVAILABLE
TWI TX: &m_twi, 0x74, 0xFD (COMMAND REG), 0x00

Description: FRAME 1 Available

#### 8. CLEAR ALL LED's
Running a double for loop to clear the matrix.

First loop: i=0; i<6: TWI TX: &m_twi, 0x74, 0x24+(i*24)

Second loop (inside the first loop): j=0; j<24: TWI TX: &m_twi, 0x74, 0x00

Description: In the first iteration of the first loop, we write to the 
