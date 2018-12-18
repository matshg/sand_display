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
The register's on the IS31 are configured through a menu.

#### 1. Select response register
The first step is to select a response register. There are 9 response registers: 8 frame registers and 1 function registers. The 8 frames can be used to configure different LED arrangement. The function register is used to configure different modes/options.

Example: To select frame 1: Initiate TWI tx amd write to address 0xFD (Command Register) the data: 0x00.

#### 2. Configure Register
##### 2.1 If you have selected Frame 1-8: We have 3 options. Configure LED Control Register, Blink Control Register, PWM Register

LED Control Registers: 18 registers running from 0x00 - 0x11

Blink Control Registers: 18 registers running from 0x12 - 0x23

PWM Registers: 256 registers running from 0x24 - 0xB3

##### 2.2 If you have selected Function Register:
In this mode, we have 12 additional registers we can further configure.

Configuration Register: Address: 0x00

Picture Display Register: Address: 0x01

Auto Play Control Register: Address: 0x02

Auto Play Control Register 2: Address: 0x03

Display Option Register: Address: 0x05

Audio Synchronization Register: Address: 0x06

Frame State Register (READ ONLY): Address: 0x07

Breath Control Register: Address: 0x08

Breath Control Register 2: Address: 0x09

Shutdown Register: Address: 0x0A

AGC Control Register: Address: 0x0B

Audio ADC Rate Register: Address: 0x0C

Read datasheet for more info on how to configure each register.


#### Cross-Plexing (Charlieplexing)
The required lines to drive all 144 LEDs are reduced to 18 by using the cross-plexing feature optimizing space on the PCB. It is why the LED Control/Blink Control Registers have 18 registers each. Additionally each of the 144 LEDs can be dimmed individually with 8-bit allowing 256 steps of linear dimming.

Note: The IS31 can drive 144 LEDs. The Charlieplex comes with 105 LEDs. The remaining 39 LED's outputs must be off by LED control register (frame registers) else if on it will affect other LEDs.

In the Charlieplex schematic we find which outputs with no LED: https://learn.adafruit.com/assets/32561

It is:

Matrix A: C1-1, C2-1, C3-1, C4-1, C5-1, C6-1, C7-1, C8-1, C9-1, C9-2, C9-3, C9-4, C9-5, C9-6, C9-7, C9-8

Matrix B: C1-9, C1-10, C1-11, C1-12, C1-13, C1-14, C1-15, C1-16, C2-16, C3-16, C4-16, C5-16, C6-16, C7-16, C8-16, C9-9, C9-10, C9-11, C9-12, C9-13, C9-14, C9-15, C9-16

All these outputs must remain off in the LED control register.

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
