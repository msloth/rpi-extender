rpi-extender
============

rpi-extender is a TI Launchpad MSP430-based extender to the Raspberry Pi.

I got a rpi and started messing around with it and noticed it have no hardware ADC
on the exposed GPIOs, so this project is about getting a leftover MSP430 (preferrably
the 'g2231 or '2452) to act as an extender, providing the rpi with some ADC inputs
and PWM outputs.

The extender mcu is a SPI slave and waits for commands from the rpi. It is constantly
in low-power mode, just doing ADC and waiting for SPI communications.

Compile to hex and upload to a Launchpad, remove the MCU and hook it up to the rpi.
