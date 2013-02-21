
# System code files
SOURCEFILES = msp430-arch.c adc.c pwm.c

# Use USI-peripheral instead of USCI by running 'make USI=1 all'
ifdef USI
SOURCEFILES += spi-usi.c
else
SOURCEFILES += spi-usci.c
endif

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

# Project code files
# Change ULFILE to the main source code file, without the file extension.
PROJECTFILES = rpiextender.c

#-----------------------------------------------------------------
CC =      msp430-gcc
SIZE =    msp430-size

# add more optimizations here, like remove sections etc
CFLAGS =  -O2 -Wall -g -mmcu=$(MCU)

#OBJS = $(PROJECT).o $(ARCH).o

SOURCEFILES += $(PROJECTFILES)
OBJECTFILES = $(SOURCEFILES:.c=.o)

all: $(OBJECTFILES)
	$(CC) $(CFLAGS) -o rpiextender.elf $(OBJECTFILES)
	$(SIZE) rpiextender.elf



#all: %.o
#all: $(OBJECTFILES)
#	$(CC) $(CFLAGS) -o $(PROJECTFILES).elf $(OBJECTFILES)
#	$(SIZE) $(PROJECT).elf

%.o: %.c
	$(CC) $(CFLAGS) -c $<

# remove all object files etc
clean:
	rm -fr $(PROJECT).elf $(OBJS) $(PROJECT)

# erase the device
erase:
	mspdebug rf2500 "erase"
	
# upload to the device
ul:
	make
	mspdebug rf2500 "prog $(PROJFILE).elf"



