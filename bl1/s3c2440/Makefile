ifeq ("$(origin O)", "command line")
		    TARGET_OUTPUT := $(O)
endif

TARGET_NAME=spl

CROSS_COMPILE ?= arm-linux-
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
AR      = $(CROSS_COMPILE)ar
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
CFLAGS = -Wall -nostdlib -g -Os -fno-builtin-printf 

ifeq ($(strip $(TARGET_OUTPUT)), )
	OBJ_OUT := $(shell pwd)
else
	OBJ_OUT := $(TARGET_OUTPUT)
endif

OBJS=start.o lowlevel_init.o nand_cp.o uart.o main.o
OBJS_DEP=$(addprefix $(OBJ_OUT)/,$(OBJS))

$(OBJ_OUT)/$(TARGET_NAME).bin: $(OBJ_OUT)  $(OBJS_DEP)
	$(LD) -Ts3c2440.lds -o $(OBJ_OUT)/$(TARGET_NAME).elf $(OBJS_DEP) 
	${OBJCOPY} -O binary -S --pad-to 4096 $(OBJ_OUT)/$(TARGET_NAME).elf $@
	$(OBJDUMP) -D $(OBJ_OUT)/$(TARGET_NAME).elf > $(OBJ_OUT)/$(TARGET_NAME).dis 


$(OBJ_OUT):
	    mkdir -p $@

$(OBJ_OUT)/%.o : %.c
	    $(CC) -c $< -o $@ -fno-builtin

$(OBJ_OUT)/%.o : %.S
	    $(CC) -c $< -o $@

clean:
	rm -rf $(OBJ_OUT)/*.o
	rm -rf $(OBJ_OUT)/*.elf
	rm -rf $(OBJ_OUT)/*.bin
	rm -rf $(OBJ_OUT)/*.dis

