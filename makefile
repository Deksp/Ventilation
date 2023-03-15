MCU = atmega328p
F_CPU = 16000000
CC = avr-g++
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=${MCU} -Os -c
CFLAGST = -c -Wall -Os -mmcu=${MCU} -DF_CPU=${F_CPU}
TARGET = ventilation
SRCS = main
LIB = Privod
SETINGS = Timers

#new make
all: $(TARGET)
	
$(TARGET): main.o Privod.o Timers.o
	$(CC) -mmcu=atmega328p -o $(TARGET).elf $(SRCS).o $(LIB).o $(SETINGS).o
	${OBJCOPY} -j .text -j .data -O ihex $(TARGET).elf ${TARGET}.hex
	avr-size --format=berkeley ${TARGET}.elf

flash:
	avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i 
	@echo -F -P usb
	
${SRCS}.o: ${SRCS}.cpp
	${CC} ${CFLAGS} ${SRCS}.cpp -o ${SRCS}.o

${LIB}.o: ${LIB}.cpp
	${CC} ${CFLAGS} ${LIB}.cpp -o ${LIB}.o
	
${SETINGS}.o: ${SETINGS}.cpp 
	${CC} ${CFLAGS} ${SETINGS}.cpp -o ${SETINGS}.o

clean:
	del *.bin *.hex