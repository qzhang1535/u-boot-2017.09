#include <common.h>

#include <nand.h>
#include <netdev.h>
#include <usb.h>
#include "spl.h"

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	gd->bd->bi_arch_number = 0xa8;
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;
	
	return 0;
}

int board_usb_init(int index, enum usb_init_type init)
{
	return s3c2410_udc_probe();
}


 

