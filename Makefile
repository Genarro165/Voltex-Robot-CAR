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
	CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -std=gnu++11 -flto -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections
	MN_FILE = main.elf
	LINK_FLAGS = -Os -mmcu=$(MCU) -o $(MN_FILE) -flto -Wl,--gc-sections
endif

ifeq ($(CORE), true)
	CXXFLAGS += -I../arduino-core -I/usr/share/arduino/hardware/arduino/avr/variants/standard
	LINK_FLAGS += ../arduino-core/*.o
endif

INO_NAME = src/src
$(shell cp $(INO_NAME).ino $(INO_NAME).cpp)
SRCS ?= $(wildcard src/Drivers/*.cpp) $(wildcard src/*.cpp) $(wildcard src/States/*.cpp)
TOTAL_SRCS += $(SRCS)
OBJS = $(TOTAL_SRCS:.cpp=.o)

BOARD ?= xplainedmini
BAUD = 9600
PORT ?= /dev/ttyUSB0
ifeq ($(BOARD), xplainedmini)
	P_PORT = usb
	PROG = xplainedmini
else
	P_PORT = $(PORT)
	PROG = arduino
endif


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all install clean monitor

$(MN_FILE): $(OBJS)
	$(CXX) $(LINK_FLAGS) $(OBJS)
	@echo "programmer: $(PROG)"
	@echo "port:       $(P_PORT)"
	avr-size --format=avr --mcu=atmega328p $(MN_FILE)

all: $(MN_FILE)

install: $(MN_FILE)
	avr-objcopy -O ihex $(MN_FILE) main.hex
	sudo avrdude -c $(PROG) -p m328p -C /etc/avrdude.conf -P $(P_PORT) -U flash:w:main.hex
	minicom --dev $(PORT) -b $(BAUD)

monitor:
	minicom --dev $(PORT) -b $(BAUD)

clean:
	rm -f $(OBJS) *.elf *.hex

