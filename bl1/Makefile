OBJ=bl1

CROSS_COMPILE=arm-linux-

CC              = $(CROSS_COMPILE)gcc
CPP             = $(CC) -E
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
LD              = $(CROSS_COMPILE)ld
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump

$(OBJ).bin: start.o clock.o uart.o ddr.o copy.o  main.o
	$(LD) -Ttext 0xD0020010 -o $(OBJ).elf $^ -lgcc -L/opt/EmbedSky/4.4.6/lib/gcc/arm-embedsky-linux-gnueabi/4.4.6
	$(OBJCOPY) -O binary $(OBJ).elf $@
	$(OBJDUMP) -D $(OBJ).elf > $(OBJ).dis
	make -C mkhead
	./mkhead/addheader $(OBJ).bin u-boot-spl.bin
	
%.o : %.c
	$(CC) -c $< -o $@ -fno-builtin
%.o : %.S
	$(CC) -c $< -o $@
	
clean:
	make -C mkhead clean
	rm *.o *.elf *.bin *.dis
