

DEVICE = atmega328p
F_CPU = 8000000L

CC = avr-gcc
CC_ARGS= -mmcu=$(DEVICE) -D F_CPU=$(F_CPU) -O1 -ggdb -Wall -I$(INCLUDE_PATH)

INCLUDE_PATH =./src -I ./include -I ./port/atmega328

AVRDUDE = avrdude
AVRDUDE_ARGS = -Cavrdude.conf -F -v -pm328p -carduino -PCOM10 -b115200 -D


SRCS_PATH = ./src
DEBUG_PATH = ./debug
PORT_PATH = ./port/atmega328

C-SRCS=$(wildcard $(SRCS_PATH)/*.c)
C-PORTS=$(wildcard $(PORT_PATH)/*.c)
C-SRC=$(wildcard *.c)
ASM-SRCS=$(wildcard $(SRCS_PATH)/*.S)
OBJS = main.o
OBJS += $(patsubst $(SRCS_PATH)/%.S, %.o, $(ASM-SRCS))
OBJS += $(patsubst $(SRCS_PATH)/%.c, %.o, $(C-SRCS))
OBJS += $(patsubst $(PORT_PATH)/%.c, %.o, $(C-PORTS))
OBJS += $(patsubst %.c, %.o, $(C-SRC))

all: $(OBJS)
	$(CC) $(CC_ARGS) $(DEBUG_PATH)/bsp.o $(DEBUG_PATH)/usart.o $(DEBUG_PATH)/main.o -o $(DEBUG_PATH)/$(DEVICE).elf
	avr-objcopy -Oihex  -j .text -j .data  ./debug/$(DEVICE).elf ./debug/$(DEVICE).hex
	avr-size -A ./debug/$(DEVICE).hex

%.o: %.c
	$(CC) $(CC_ARGS) -c $^ -o $(DEBUG_PATH)/$@

%.o: %.S
	$(CC) $(CC_ARGS) -c $^ -o $(DEBUG_PATH)/$@

%.o: $(SRCS_PATH)/%.c
	$(CC) $(CC_ARGS) -c /$^ -o $(DEBUG_PATH)/$@

%.o: $(SRCS_PATH)/%.c
	$(CC) $(CC_ARGS) -c $^ -o $(DEBUG_PATH)/$@

%.o: $(PORT_PATH)/%.c
	$(CC) $(CC_ARGS) -c /$^ -o $(DEBUG_PATH)/$@

%.o: $(PORT_PATH)/%.c
	$(CC) $(CC_ARGS) -c $^ -o $(DEBUG_PATH)/$@

upload:
	$(AVRDUDE) $(AVRDUDE_ARGS) -Uflash:w:"./debug/atmega328p.hex":i
clear:
	rm -rf $(DEBUG_PATH)/*.o 
	rm -rf $(DEBUG_PATH)/*.map
	rm -rf $(DEBUG_PATH)/*.elf
	rm -rf $(DEBUG_PATH)/*.hex
	mkdir debug


