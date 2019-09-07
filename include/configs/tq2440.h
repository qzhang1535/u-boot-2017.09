#ifndef _TQ2440_H
#define _TQ2440_H


#define CONFIG_BAUDRATE			115200
#define CONFIG_NR_DRAM_BANKS	1

#define CONFIG_FASTBOOT_FLASH_NAND_DEV		1


#define CONFIG_SYS_MAXARGS			16
#define CONFIG_SYS_CBSIZE			256
#define CONFIG_SYS_PBSIZE			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)


#define CONFIG_SYS_GENERIC_BOARD
#define CONFIG_SYS_INIT_SP_ADDR	0x33ffffff
#define CONFIG_SYS_SDRAM_BASE	0x30000000
#define CONFIG_SYS_SDRAM_SIZE		(64*1024*1024)	/* 64 Mb */
#define CONFIG_SYS_MALLOC_LEN	0x100000	
/*#define CONFIG_SYS_UBOOT_BASE	0x50000000	*/
#define CONFIG_SYS_LOAD_ADDR	0x30007fc0	
#define CONFIG_SYS_TEXT_BASE	0x30000000



#define CONFIG_SYS_MAX_NAND_DEVICE		1
#define CONFIG_SYS_NAND_BASE				0x4E000010		/*nand->IO_ADDR_R = nand->IO_ADDR_W=CONFIG_SYS_NAND_BASE*/

	
	
#define CONFIG_ENV_IS_IN_NAND				1
#define CONFIG_ENV_OFFSET					0x100000
#define CONFIG_ENV_SIZE						(128*1024)

#define CONFIG_EXTRA_ENV_SETTINGS           "serial#=TQ2440F000A\0"
#define CONFIG_BOOTCOMMAND					"nand read 0x30007fc0 kernel; bootm 0x30007fc0"

#ifdef CONFIG_SPL_BUILD
#define CONFIG_SPL_FRAMEWORK				1
#define CONFIG_SPL_LIBGENERIC_SUPPORT		1
#define CONFIG_SPL_LIBCOMMON_SUPPORT		1
#define CONFIG_SPL_SERIAL_SUPPORT			1
#define CONFIG_SPL_TEXT_BASE				0x30000000
#define CONFIG_SPL_STACK					0x2000

/* #define CONFIG_SPL_NAND_SUPPORT				1*/
#define CONFIG_SPL_NAND_RAW_ONLY			1

/*first 8k is spl*/	
#define CONFIG_SYS_NAND_U_BOOT_OFFS			(8*1024)				
#define CONFIG_SYS_NAND_U_BOOT_SIZE			(0x200000 - 8*1024)
#define CONFIG_SYS_NAND_U_BOOT_DST			0x5fe00000
#endif

#define CONFIG_AUTO_COMPLETE					1		/*tab auto complete*/
#define CONFIG_CMDLINE_EDITING				1		/*cmd line editing*/



#define CONFIG_CMD_LOADB						1
#define CONFIG_CMD_MTDPARTS					1
#define CONFIG_CMD_NAND						1
#define CONFIG_CMD_PING						1
#define CONFIG_CMD_SAVEENV					1

/*mtd*/
#define CONFIG_MTD_DEVICE						1
#define MTDIDS_DEFAULT 							"nand0=nand0"
#define MTDPARTS_DEFAULT 						"mtdparts=nand0:0x200000@0x0(uboot),0x600000@0x200000(kernel),0x4000000@0x800000(rootfs),-(reserved)"
#define MTD_ACTIVE_PART 						"nand0,2"


#define CONFIG_SETUP_MEMORY_TAGS		1
#define CONFIG_CMDLINE_TAG				1


#define CONFIG_SYS_MONITOR_BASE			1
#define CONFIG_SYS_ICACHE_OFF				1
#define CONFIG_SYS_DCACHE_OFF				1

#endif
