#include "uart.h"

#define CONFIG_UBOOT_START_ADDR			0x20000000

#define OM_STAT		(*(volatile u32 *)0xE010E100)

extern void copy_sd(u32 start_block, u16 block_size, u32 addr);
extern void copy_nand(u32 addr, u8 * buf, int len);



typedef void (*FUNC)(void);

static int boot_from_nand(void)
{
	u32 state = OM_STAT;
	
	if(state & (1<<1))
	{
		puts("\nboot from nand...\n");
		return 1;
	}
	else
	{
		puts("\nboot from sdcard...\n");
		return 0;
	}	
}

int main()
{
	FUNC theBoot;
	
	if(boot_from_nand())
	{
		copy_nand(16*1024, (u8 *)CONFIG_UBOOT_START_ADDR, 0x100000);
	}
	
	else
	{
		/* 从SD卡的块32拷贝4096个块到DDR的起始地址0x2000000地址处 */
		copy_sd(33, 4096, CONFIG_UBOOT_START_ADDR);
	}
	
	puts("##### Running in BL1 #####\n");
	
	theBoot = (FUNC)CONFIG_UBOOT_START_ADDR;
	
	theBoot();
	
	return 0;
}
