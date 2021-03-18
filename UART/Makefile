# Basic Makefile for ARM Cortex-M4 assembly projects
TARGET = main

# Linker script location and info
LD_SCRIPT = ./ld/STM32F411CEU6.ld
MCU_SPEC = cortex-m4

# Toolchain defs (ARM bare metal defaults)
TOOLCHAIN = /usr/bin/arm-none-eabi

AS = $(TOOLCHAIN)-as
CC = $(TOOLCHAIN)-gcc
DB = $(TOOLCHAIN)-gdb
LD = $(TOOLCHAIN)-ld
OC = $(TOOLCHAIN)-objcopy
OD = $(TOOLCHAIN)-objdump
OS = $(TOOLCHAIN)-size

# Assembly directives.
ASFLAGS += -c
ASFLAGS += -O0
ASFLAGS += -mcpu=$(MCU_SPEC)
ASFLAGS += -mthumb
ASFLAGS += -Wall
# (Set error messages to appear on a single line.)
ASFLAGS += -fmessage-length=0

# C compilation directives
CFLAGS += -mcpu=$(MCU_SPEC)
CFLAGS += -mthumb
CFLAGS += -Wall
CFLAGS += -g
# (Set error messages to appear on a single line.)
CFLAGS += -fmessage-length=0
# (Set system to ignore semihosted junk)
CFLAGS += --specs=nosys.specs

# Linker directives.
LSCRIPT = ./$(LD_SCRIPT)
LFLAGS += -mcpu=$(MCU_SPEC)
LFLAGS += -mthumb
LFLAGS += -Wall
LFLAGS += --specs=nosys.specs
LFLAGS += -nostdlib
LFLAGS += -lgcc
LFLAGS += -T$(LSCRIPT)

AS_SRC = ./src/core.s
AS_SRC += ./src/vector_table.s
C_SRC = ./src/main.c

OBJS  = $(AS_SRC:.S=.o)
OBJS += $(C_SRC:.c=.o)

.PHONY: all
all: $(TARGET).bin

%.o: %.S
	$(CC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<

.PHONY: clean
clean:
	#rm -f $(OBJS)
	rm -f $(TARGET).elf
	rm -f $(TARGET).bin
	clear

.PHONY: debug
debug:
	$(DB) $(TARGET).elf