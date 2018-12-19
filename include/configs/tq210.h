#ifndef _TQ210_H
#define _TQ210_H

#include <asm/arch/cpu.h>

#define CONFIG_BAUDRATE			115200
#define CONFIG_NR_DRAM_BANKS	1

#define CONFIG_USB_GADGET_DWC2_OTG_PHY		1
#define CONFIG_USB_GADGET_DUALSPEED		1
#define CONFIG_FASTBOOT_FLASH_NAND_DEV  	1


#define CONFIG_SYS_MAXARGS			16
#define CONFIG_SYS_CBSIZE			256
#define CONFIG_SYS_PBSIZE			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)



#define CONFIG_SYS_INIT_SP_ADDR			0x30000000
#define CONFIG_SYS_SDRAM_BASE			0x20000000
#define CONFIG_SYS_SDRAM_SIZE			(1024*1024*1024)	/* 64 Mb */
#define CONFIG_SYS_MALLOC_LEN			0x100000	
/*#define CONFIG_SYS_UBOOT_BASE	0x50000000	*/

#define CONFIG_SYS_LOAD_ADDR			0x20007fc0	
#define CONFIG_SYS_TEXT_BASE			0x20000000



#define CONFIG_SYS_MAX_NAND_DEVICE			1
#define CONFIG_SYS_NAND_BASE				0xB0E00010		/*nand->IO_ADDR_R = nand->IO_ADDR_W=CONFIG_SYS_NAND_BASE*/

#define CONFIG_SYS_NAND_ECCSIZE				512
#define CONFIG_SYS_NAND_ECCBYTES			13

#define CONFIG_ENV_IS_IN_NAND				1
#define CONFIG_ENV_OFFSET					0x100000
#define CONFIG_ENV_SIZE						(128*1024)

#define CONFIG_BOOTCOMMAND					"ubi part boot;ubifsmount ubi0:boot;ubifsload 20008000 zImage;ubifsload 20800000 s5pv210-tq210.dtb;bootz 20008000 - 20800000"


#define CONFIG_AUTO_COMPLETE				1		/*tab auto complete*/
#define CONFIG_CMDLINE_EDITING				1		/*cmd line editing*/



#define CONFIG_CMD_LOADB					1
#define CONFIG_CMD_MTDPARTS					1
#define CONFIG_CMD_NAND						1
#define CONFIG_CMD_PING						1
#define CONFIG_CMD_SAVEENV					1

/*mtd*/
#define CONFIG_MTD_DEVICE						1
#define MTDIDS_DEFAULT 						    "nand0=nand0"
#define MTDPARTS_DEFAULT 					    "mtdparts=nand0:0x200000@0x0(bootloader),0x800000@0x200000(boot),0x4000000@0xa00000(rootfs),-(reserved)"
#define MTD_ACTIVE_PART 					    "nand0,2"



#define CONFIG_SETUP_MEMORY_TAGS			1
#define CONFIG_CMDLINE_TAG				1
#define CONFIG_INITRD_TAG				1


#define CONFIG_SYS_MONITOR_BASE				1
#define CONFIG_SYS_ICACHE_OFF				1
#define CONFIG_SYS_DCACHE_OFF				1


#endif

