#include <common.h>

DECLARE_GLOBAL_DATA_PTR;


#define rWTCON 				*((volatile unsigned long*)0x53000000)
#define rWTDAT 				*((volatile unsigned long*)0x53000004)
#define rWTCNT 				*((volatile unsigned long*)0x53000008)


void reset_cpu(unsigned long ignored)
{
	rWTCON = 0;
	rWTCON |= (0<<3) | (199<<8) | (1<<0);// 50000000/16/200 = 15625

	rWTCNT = 15625;
	rWTDAT = 15625;

	rWTCON |= (1<<5);
	while(1);
}

int dram_init(void)
{
	/* dram_init must store complete ramsize in gd->ram_size */
	gd->ram_size = CONFIG_SYS_SDRAM_SIZE;
	
	return 0;
}

 void enable_caches(void)
{

}