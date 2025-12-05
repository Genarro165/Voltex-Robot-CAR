MCU ?= atmega328p
F_CPU ?= 16000000UL
BAUD ?= 9600
TEST ?= false
CORE ?= true

ifeq ($(TEST), true)
	CC = gcc
	CXX = g++
	CXXFLAGS = -Os -Wall
	MN_FILE = main
	LINK_FLAGS = -o $(MN_FILE)
else
	CC = avr-gcc
	CXX = avr-g++
	CCFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -std=gnu11 -flto -fno-rtti -ffunction-sections -fdata-sections
	CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -std=gnu++11 -flto -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections
	MN_FILE = main.elf
	LINK_FLAGS = -Os -mmcu=$(MCU) -o $(MN_FILE) -flto -Wl,--gc-sections
endif

ifeq ($(CORE), true)

CXXFLAGS += -I/usr/share/arduino/hardware/arduino/avr/variants/standard -I../arduino-core -D ARDUINO_CORE
	LINK_FLAGS += ../arduino-core/*.o
endif

INO_NAME = src/src
$(shell cp $(INO_NAME).ino $(INO_NAME).cpp)
SRCS ?= $(wildcard src/Drivers/*.cpp) $(wildcard src/*.cpp) $(wildcard src/States/*.cpp) $(wildcard src/fuck-arduino-kekw/*.cpp) $(wildcard src/fuck-arduino-kekw/Arduino-LiquidCrystal-I2C-library/*.cpp)

TOTAL_SRCS += $(SRCS)
OBJS = $(TOTAL_SRCS:.cpp=.o) src/fuck-arduino-kekw/utility/twi.o
MONITOR_PORT ?= /dev/ttyUSB0
BAUD ?= 9600
BOARD ?= xplainedmini

ifeq ($(BOARD), xplainedmini)
	PORT = usb
	PROG = xplainedmini
else
	PORT = $(MONITOR_PORT)
	PROG = arduino
endif

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(MN_FILE): $(OBJS)
	$(CXX) $(LINK_FLAGS) $(OBJS)
	avr-size --format=avr --mcu=atmega328p $(MN_FILE)
	@echo "programmer: $(PROG)"
	@echo "port: 	    $(PORT)"

.PHONY: all install clean monitor

all: $(MN_FILE)

install: $(MN_FILE)
	avr-objcopy -O ihex $(MN_FILE) main.hex
	sudo avrdude -c $(PROG) -p m328p -C /etc/avrdude.conf -P $(PORT) -U flash:w:main.hex
	minicom --dev $(MONITOR_PORT) -b $(BAUD)

monitor:
	minicom --dev $(MONITOR_PORT) -b $(BAUD)

clean:
	rm -f $(OBJS) *.elf *.hex

