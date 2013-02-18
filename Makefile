
# System code files
SOURCEFILES = msp430-arch.c adc.c pwm.c spi.c

# Project code files
# Change ULFILE to the main source code file, without the file extension.
PROJECTFILES = rpiextender.c



#-----------------------------------------------------------------
CC =      msp430-gcc
SIZE =    msp430-size

# add more optimizations here, like remove sections etc
CFLAGS =  -O2 -Wall -g -mmcu=msp430g2231 -D__MSP430G2231__=1

#OBJS = $(PROJECT).o $(ARCH).o

SOURCEFILES += $(PROJECTFILES)
#OBJECTFILES = $(PROJECTFILES:.c=.o)
OBJECTFILES = msp430-arch.o adc.o rpiextender.o pwm.o spi.o


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



