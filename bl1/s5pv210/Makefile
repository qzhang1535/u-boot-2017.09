ifeq ("$(origin O)", "command line")
	TARGET_OUTPUT := $(O)
endif


TARGET_NAME=bl1

CROSS_COMPILE?=arm-linux-

CC              = $(CROSS_COMPILE)gcc
CPP             = $(CC) -E
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
LD              = $(CROSS_COMPILE)ld
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump

ifeq ($(strip $(TARGET_OUTPUT)), )
		OBJ_OUT := $(shell pwd)
else
		OBJ_OUT := $(TARGET_OUTPUT)
endif

HOST_ADDHEADER=$(OBJ_OUT)/addheader
OBJS=start.o clock.o uart.o ddr.o copy.o main.o

OBJS_DEP=$(addprefix $(OBJ_OUT)/,$(OBJS))
$(OBJ_OUT)/$(TARGET_NAME).bin: $(OBJ_OUT) $(HOST_ADDHEADER) $(OBJS_DEP)
	$(LD) -Ttext 0xD0020010 -o $(OBJ_OUT)/$(TARGET_NAME).elf $(OBJS_DEP) 
	$(OBJCOPY) -O binary $(OBJ_OUT)/$(TARGET_NAME).elf $@
	$(OBJDUMP) -D $(OBJ_OUT)/$(TARGET_NAME).elf > $(OBJ_OUT)/$(TARGET_NAME).dis
	$(HOST_ADDHEADER) $(OBJ_OUT)/$(TARGET_NAME).bin $(OBJ_OUT)/u-boot-spl.bin
	
$(HOST_ADDHEADER):
	gcc -o $@ mkhead/addheader.c
	
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
	rm -rf $(OBJ_OUT)/addheader
