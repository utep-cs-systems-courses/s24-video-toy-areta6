# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:video.elf

#additional rules for files
video.elf: ${COMMON_OBJECTS}  videodemo.o wdt_handler.o buzzer.o shapes.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: video.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
