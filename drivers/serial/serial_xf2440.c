#include <common.h>
#include <asm/io.h>
#include <serial.h>


#define GPHCON              (*(volatile unsigned long *)0x56000070)
#define GPHDAT              (*(volatile unsigned long *)0x56000074)
#define GPHUP               (*(volatile unsigned long *)0x56000078)

#define ULCON0              (*(volatile unsigned long *)0x50000000)
#define UCON0               (*(volatile unsigned long *)0x50000004)
#define UFCON0              (*(volatile unsigned long *)0x50000008)
#define UMCON0              (*(volatile unsigned long *)0x5000000c)
#define UTRSTAT0            (*(volatile unsigned long *)0x50000010)
#define UFSTAT0            (*(volatile unsigned long *)0x50000018)
#define UTXH0               (*(volatile unsigned char *)0x50000020)
#define URXH0               (*(volatile unsigned char *)0x50000024)
#define UBRDIV0             (*(volatile unsigned long *)0x50000028)

#define ULCON1              (*(volatile unsigned long *)0x50004000)
#define UCON1               (*(volatile unsigned long *)0x50004004)
#define UFCON1              (*(volatile unsigned long *)0x50004008)
#define UMCON1              (*(volatile unsigned long *)0x5000400c)
#define UTRSTAT1            (*(volatile unsigned long *)0x50004010)
#define UTXH1               (*(volatile unsigned char *)0x50004020)
#define URXH1               (*(volatile unsigned char *)0x50004024)
#define UBRDIV1             (*(volatile unsigned long *)0x50004028)

static int xf2440_serial_init(void)
{
	ULCON0  = 0x03;     // 8N1(8个数据位，无较验，1个停止位)
	UCON0   = 0x05;     // 查询方式，UART时钟源为PCLK
	UFCON0  = 0x00;     // 不使用FIFO
	UMCON0  = 0x00;     // 不使用流控
	UBRDIV0 = 26; // 波特率为115200

	return 0;
}

void xf2440_serial_setbrg(void)
{
	int i = 0;
	
	UBRDIV0 = 26; // 波特率为115200

	//for delay
	for(;i < 100; ++i)
		;
}

static void xf2440_serial_putc(const char c)
{
	if (c == '\n')
		xf2440_serial_putc('\r');


	// here is very important!!!!!!
	while (!(UTRSTAT0 & 0x02));
	UTXH0 = c;
}

static int	xf2440_serial_getc(void)
{
	while (!(UTRSTAT0 & 0x1));
	
	return (URXH0 & 0xff);
}
static int xf2440_serial_tstc(void)
{
	return (UTRSTAT0 & 0x1);
}

static struct serial_device xf2440_serial_drv = {
	.name	= "xf2440_serial",
	.start	= xf2440_serial_init,
//	.stop	= NULL,
	.setbrg	= xf2440_serial_setbrg,
	.putc	= xf2440_serial_putc,
	.puts	= default_serial_puts,
	.getc	= xf2440_serial_getc,
	.tstc	= xf2440_serial_tstc,
};


struct serial_device *default_serial_console(void)
{
	return &xf2440_serial_drv;
}


