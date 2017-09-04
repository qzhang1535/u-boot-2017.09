#include <common.h>

#include <nand.h>
#include <netdev.h>
#include "spl.h"

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	gd->bd->bi_arch_number = 0xa8;
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;
	
	return 0;
}







#ifdef CONFIG_DRIVER_DM9000

#define SROM_BW_REG 		(*(volatile unsigned long *)0x70000000)
#define SROM_BC1_REG		(*(volatile unsigned long *)0x70000008)
#define DM9000_Tacs	(0x0)	// 0clk		address set-up
#define DM9000_Tcos	(0x4)	// 4clk		chip selection set-up
#define DM9000_Tacc	(0xE)	// 14clk	access cycle
#define DM9000_Tcoh	(0x1)	// 1clk		chip selection hold
#define DM9000_Tah	(0x4)	// 4clk		address holding time
#define DM9000_Tacp	(0x6)	// 6clk		page mode access cycle
#define DM9000_PMC	(0x0)	// normal(1data)page mode configuration

static void s3c6410_srom_int(void)
{
	SROM_BW_REG &= ~(0xf << 4);
	SROM_BW_REG |= ((1<<7) | (1<<6) |(1<<4));
	SROM_BC1_REG = ((DM9000_Tacs<<28)+(DM9000_Tcos<<24)+(DM9000_Tacc<<16)+(DM9000_Tcoh<<12)+(DM9000_Tah<<8)+(DM9000_Tacp<<4)+(DM9000_PMC));    
  //  printf("SROM_BW_REG:%x\n", SROM_BW_REG);
   // printf("SROM_BC1_REG:%x\n", SROM_BC1_REG);
}

int board_eth_init(bd_t *bis)
{
	s3c6410_srom_int();
	return dm9000_initialize(bis);
}
#endif

