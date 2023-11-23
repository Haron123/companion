#file makefile
device := atmega328p
cpufreq := 16000000
port := /dev/ttyACM0
LDFLAGS := 

CC := avr-gcc
CFLAGS := -Wall -Oz -I inc/ -DF_CPU=$(cpufreq) -mmcu=$(device) --param=min-pagesize=0
OBJ := main.o i2c.o mpr121.o ssd1306.o battery_indic.o system_time.o draw.o gesture.o

CLEAN_TARGET := *.o *.bin *.hex

all: project upload clean

project: $(OBJ)
	$(CC) -o $@ $^
	avr-gcc $(LDFLAGS) -mmcu=$(device) -o main.bin $(OBJ)
	avr-objcopy -O ihex -R .eeprom main.bin main.hex 


%.o: src/%.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf $(CLEAN_TARGET)

upload :
	avrdude -F -V -c avrisp -p $(device) -P $(port) -b 115200 -U flash:w:main.hex
