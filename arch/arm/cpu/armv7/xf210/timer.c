#include <common.h>

#define rTCFG0 			*((volatile unsigned long*)0xE2500000)
#define rTCFG1 			*((volatile unsigned long*)0xE2500004)
#define rTCON 			*((volatile unsigned long*)0xE2500008)

#define rTCNTB4 			*((volatile unsigned long*)0xE250003C)
#define rTCNTO4 			*((volatile unsigned long*)0xE2500040)



DECLARE_GLOBAL_DATA_PTR;


int timer_init(void)
{
	// timer4
	// setting timer clk 66000000/132/8 = 62500
	rTCON &= ~(1<<20);// start timer	
	
	rTCFG0 &= ~(0xFF<<8);
	rTCFG0 |= 0x83<<8;//prescale is 132
	
	rTCFG1 &= ~(0xf<<16);
	rTCFG1 |= 0x3<<16;// div is 16

	rTCNTB4 = 0xFFFFFFFF;
	
	rTCON |= (1<<22); // Auto-Reload
	rTCON |= (1<<21);// Update TCNTB4	
	rTCON &= ~(1<<21);//end updata

	rTCON |= (1<<20);// start timer	
	
	gd->arch.timer_rate_hz = 62500;// 一秒钟的计数值
	gd->arch.tbu = 0xFFFFFFFF;// 计数寄存器的值 

	// 用于计数
	gd->arch.lastinc = gd->arch.tbu;
	gd->arch.tbl = 0;
	
	return 0;
}

unsigned long get_tbclk(void)
{
	return gd->arch.timer_rate_hz;
}

unsigned long long get_ticks(void)
{
	ulong now = rTCNTO4;

//	printf("now:%x\n", now);

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
 	//printf("get_timer:%d\n", get_timer_masked());
	return get_timer_masked() - base;
}