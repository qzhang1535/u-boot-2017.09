#include <common.h>

#define rTCFG0 			*((volatile unsigned long*)0x51000000)
#define rTCFG1 			*((volatile unsigned long*)0x51000004)
#define rTCON 			*((volatile unsigned long*)0x51000008)
/*#define rTCNTB0 			*((volatile unsigned long*)0x7F00600C)
#define rTCMPB0 			*((volatile unsigned long*)0x7F006010)
#define rTCNTO0 			*((volatile unsigned long*)0x7F006014)
#define rTCNTB1 			*((volatile unsigned long*)0x7F006018)
#define rTCMPB1 			*((volatile unsigned long*)0x7F00601c)
#define rTCNTO1 			*((volatile unsigned long*)0x7F006020)
#define rTCNTB2 			*((volatile unsigned long*)0x7F006024)
#define rTCNTO2 			*((volatile unsigned long*)0x7F00602c)
#define rTCNTB3 			*((volatile unsigned long*)0x7F006030)
#define rTCNTO3 			*((volatile unsigned long*)0x7F006038)
*/
#define rTCNTB4 			*((volatile unsigned long*)0x5100003C)
#define rTCNTO4 			*((volatile unsigned long*)0x51000040)
//#define rTINT_CSTAT 		*((volatile unsigned long*)0x7F006044)

DECLARE_GLOBAL_DATA_PTR;

int timer_init(void)
{
	// timer4
	// setting timer clk 50000000/16/2 = 1562500
	rTCFG0 |= 0x0F<<8;//prescale is 16
	rTCFG1 &= ~(0xf<<16);//(1/2 divid) 

	rTCNTB4 = 15625;
	
	rTCON |= (1<<22); // Auto-Reload
	rTCON |= (1<<21);// Update TCNTB4	
	rTCON &= ~(1<<21);//end updata

	rTCON |= (1<<20);// start timer	
	
	gd->arch.timer_rate_hz = 1562500;
	gd->arch.tbu = 15625;
	gd->arch.lastinc = 0;
	gd->arch.tbl = 0;
	
	return 0;
}

unsigned long get_tbclk(void)
{
	return gd->arch.timer_rate_hz;
}

unsigned long long get_ticks(void)
{
	ulong now = rTCNTO4 & 0xffff;

	if (gd->arch.lastinc >= now) {
		/* normal mode */
		gd->arch.tbl += gd->arch.lastinc - now;
	} else {
		/* we have an overflow ... */
		gd->arch.tbl += gd->arch.lastinc + gd->arch.tbu - now;
	}
	gd->arch.lastinc = now;

	return gd->arch.tbl;
}

ulong get_timer_masked(void)
{
	ulong tmr = get_ticks();

	return tmr / (gd->arch.timer_rate_hz / 1000);
}

ulong get_timer(ulong base)
{
	return get_timer_masked() - base;
}
