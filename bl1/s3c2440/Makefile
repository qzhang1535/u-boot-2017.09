# 目录存在的问题
# 1、头文件依赖没有
# 2、链接脚本里的文件目录要自己指定


#设置输出文件目录
OBJDIR = output/obj
BINDIR = spl

#设置输入文件目录
SRC_C = $(shell find -name '*.c')
SRC_S = $(shell find -name '*.S')
SRC_C_FILE = $(notdir $(SRC_C))
SRC_S_FILE = $(notdir $(SRC_S))

INC = $(addprefix -I, $(dir $(shell find -name '*.h')))

OBJ = $(addprefix $(OBJDIR)/, $(SRC_C_FILE:.c=.o))
OBJ +=$(addprefix $(OBJDIR)/, $(SRC_S_FILE:.S=.o))


#设置编译环境 
CROSS_COMPILE ?= arm-linux-
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
AR      = $(CROSS_COMPILE)ar
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
CFLAGS = -Wall -nostdlib -g -Os -fno-builtin-printf 
vpath %.c $(dir $(SRC_C))
vpath %.S $(dir $(SRC_S))

all:$(OBJDIR) $(OBJ)
	${LD} -Ts3c2440.lds -o $(BINDIR).elf $(OBJ)	
	${OBJCOPY} -O binary -S $(BINDIR).elf $(BINDIR).bin
	${OBJCOPY} -O binary -S --pad-to 4096 $(BINDIR).elf $(BINDIR).bin	
	${OBJDUMP} -D $(BINDIR).elf > $(BINDIR).dis

#创建文件夹
$(OBJDIR):
	@echo $(OBJ)
	mkdir -p $(OBJDIR)	
$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
$(OBJDIR)/%.o : %.S
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

.PHONY : clean
clean:
	rm -f $(OBJDIR)/*.o
	rm -f *.elf *.bin *.dis


	
