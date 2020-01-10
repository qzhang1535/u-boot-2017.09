ifeq ("$(origin O)", "command line")
	BL1_OUTPUT := $(O)
endif

OBJ=bl1

CROSS_COMPILE?=arm-linux-

CC              = $(CROSS_COMPILE)gcc
CPP             = $(CC) -E
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
LD              = $(CROSS_COMPILE)ld
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump

OBJS=start.o clock.o uart.o ddr.o copy.o main.o
OBJS_WITH_DIR=$(addprefix $(BL1_OUTPUT)/,$(OBJS))
TOOL_ADDHEADER=$(addprefix $(BL1_OUTPUT)/,addheader)

$(BL1_OUTPUT)/$(OBJ).bin: $(BL1_OUTPUT) $(OBJS_WITH_DIR) $(TOOL_ADDHEADER)
	$(LD) -Ttext 0xD0020010 -o $(BL1_OUTPUT)/$(OBJ).elf $(OBJS_WITH_DIR) 
	$(OBJCOPY) -O binary $(BL1_OUTPUT)/$(OBJ).elf $@
	$(OBJDUMP) -D $(BL1_OUTPUT)/$(OBJ).elf > $(BL1_OUTPUT)/$(OBJ).dis
	$(TOOL_ADDHEADER) $(BL1_OUTPUT)/$(OBJ).bin $(BL1_OUTPUT)/u-boot-spl.bin
	
$(BL1_OUTPUT):
	mkdir -p $@

$(BL1_OUTPUT)/%.o : %.c
	$(CC) -c $< -o $@ -fno-builtin
$(BL1_OUTPUT)/%.o : %.S
	$(CC) -c $< -o $@

$(BL1_OUTPUT)/addheader:
	gcc -o $@ mkhead/addheader.c
	
clean:
	rm *.o *.elf *.bin *.dis addheader
