#include <common.h>
#include <netdev.h>
#include <usb.h>

#include <usb/dwc2_udc.h>



DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	gd->bd->bi_arch_number = 0xa8;
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;
	
	return 0;
}

int dram_init(void)
{
	/* dram_init must store complete ramsize in gd->ram_size */
	gd->ram_size = CONFIG_SYS_SDRAM_SIZE;
	
	return 0;
}


#ifdef CONFIG_USB_GADGET


static int s5pc1xx_phy_control(int on)
{
    return 0;	
}

struct dwc2_plat_otg_data s5pc110_otg_data = {
	.phy_control = s5pc1xx_phy_control,
	.regs_phy = 0xEC100000,
	.regs_otg = 0xEC000000,
	.usb_phy_ctrl = 0xE010E80C,
};

int board_usb_init(int index, enum usb_init_type init)
{
	debug("USB_udc_probe\n");
	return dwc2_udc_probe(&s5pc110_otg_data);
}
#endif


#ifdef CONFIG_DRIVER_DM9000

#define SMC_BC_TACS(x) (x << 28) /* 0clk     address set-up */
#define SMC_BC_TCOS(x) (x << 24) /* 4clk     chip selection set-up */
#define SMC_BC_TACC(x) (x << 16) /* 14clk    access cycle */
#define SMC_BC_TCOH(x) (x << 12) /* 1clk     chip selection hold */
#define SMC_BC_TAH(x)  (x << 8)  /* 4clk     address holding time */
#define SMC_BC_TACP(x) (x << 4)  /* 6clk     page mode access cycle */
#define SMC_BC_PMC(x)  (x << 0)  /* normal(1data)page mode configuration */

#define SROM_BW  		(*(volatile u32 *)0xE8000000)
#define	SROM_BC1  		(*(volatile u32 *)0xE8000008)

int board_eth_init(bd_t *bis)
{

	SROM_BW |= (1<<4) | (1<<5);

	SROM_BC1 = SMC_BC_TACS(0) | SMC_BC_TCOS(1) | SMC_BC_TACC(3)		
				| SMC_BC_TCOH(1) | SMC_BC_TAH(0) 
				| SMC_BC_TACP(0) | SMC_BC_PMC(0);
			
	return dm9000_initialize(bis);
}
#endif


