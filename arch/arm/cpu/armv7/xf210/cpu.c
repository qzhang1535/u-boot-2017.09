#include <common.h>
#include <asm/io.h>

#define rWTCON 				*((volatile unsigned long*)0xE2700000)
#define rWTDAT 				*((volatile unsigned long*)0xE2700004)
#define rWTCNT 				*((volatile unsigned long*)0xE2700008)



unsigned int s5p_cpu_id = 0;

void reset_cpu(ulong addr)
{
	rWTCON = 0;
	rWTCON |= (0<<3) | (199<<8) | (1<<0);// 66000000/16/220 = 18750

	rWTCNT = 18750;
	rWTDAT = 18750;

	rWTCON |= (1<<5);
	while(1);
	
}
