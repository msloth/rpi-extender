
# Makefile for the Raspberry Pi extender.
# 
# Author: Marcus Lunden <marcus.lunden@gmail.com>
# 

# System/arch files
SOURCEFILES = msp430-arch.c adc.c pwm.c

# check for USI or USCI
ifdef USI
SOURCEFILES += spi-usi.c
CFLAGS += -DUSI_SPI
else
SOURCEFILES += spi-usci.c
CFLAGS += -DUSCI_SPI
endif

# check for choice of microcontroller
ifdef MSP
# if MCU is defined on the command line, we use that one
MCU=$(MSP)
else  # MSP
# otherwise, we see if the USI is set, and default from that
ifdef USI
MCU=msp430g2231
else  # USI
MCU=msp430g2553
endif  # USI
endif  # MSP

#-----------------------------------------------------------------
# source- and object files
PROJECTFILES = rpiextender.c
SOURCEFILES += $(PROJECTFILES)
OBJECTFILES = $(SOURCEFILES:.c=.o)

CC =      msp430-gcc
SIZE =    msp430-size

# more flags, like optimizations, here: remove unused sections etc
CFLAGS =  -O2 -Wall -g -mmcu=$(MCU)

all: $(OBJECTFILES)
	$(CC) $(CFLAGS) -o rpiextender.elf $(OBJECTFILES)
	$(SIZE) rpiextender.elf

help:
	@echo " "
	@echo "Raspberry Pi extender; reads ADC and sets PWM according to SPI commands"
	@echo "  from the RPi. This is written for g2452/g2231 and g2553 but they differ"
	@echo "  in how they implement hardware SPI. The g2553 has a USCI-module and the"
	@echo "  g2231/g2452 has just a USI."
	@echo " "
	@echo "Usage:"
	@echo "Compile everything; defaults to msp430g2553 (and thus USCI SPI)"
	@echo "   make all"
	@echo "Compile everything, using USI SPI; defaults to msp430g2231"
	@echo "   make USI=1 all"
	@echo "Compile everything, using USI SPI and msp430g2452"
	@echo "   make USI=1 MSP=msp430g2452 all"
	@echo "Program the binary file to the microcontroller; you must compile first."
	@echo "   make upload"
	@echo " "

%.o: %.c
	$(CC) $(CFLAGS) -c $<

# remove all object files etc
clean:
	rm -fr $(PROJECT).elf $(OBJS) $(PROJECT)

# erase the device
erase:
	@mspdebug rf2500 "erase"
	
# upload the binary to the device
upload:
	@mspdebug rf2500 "prog $(PROJECTFILES:.c=.elf)"



