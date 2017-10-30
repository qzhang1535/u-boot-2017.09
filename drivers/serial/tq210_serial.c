#include <common.h>
#include <post.h>
#include <watchdog.h>
#include <serial.h>


#define ULCON0 		*((volatile unsigned int *)0xE2900000)
#define UCON0 		*((volatile unsigned int *)0xE2900004)
#define UFCON0 		*((volatile unsigned int *)0xE2900008)
#define UTRSTAT0 	*((volatile unsigned int *)0xE2900010)
#define UTXH0  		*((volatile unsigned int *)0xE2900020)
#define URXH0 		*((volatile unsigned int *)0xE2900024)
#define UBRDIV0 	*((volatile unsigned int *)0xE2900028)
#define UDIVSLOT0	*((volatile unsigned int *)0xE290002C)


static int tq210_uart0_init(void)
{
	return 0;
}

static	void	tq210_uart0_setbrg(void)
{
}
static	int	tq210_uart0_getc(void)
{
	while (!(UTRSTAT0 & 0x1))
	{
		
	}
	
	return (URXH0 & 0xff);
}

static int tq210_uart0_tstc(void)
{
	return (UTRSTAT0 & 0x1);
}

static void tq210_uart0_putc(const char c)
{
	if (c == '\n')
		tq210_uart0_putc('\r');
		
	while (!(UTRSTAT0 & (1 << 2)));	/* 等待发送缓冲区为空 */
		UTXH0 = c;					/* 发送一字节数据 */
	
}
static void tq210_uart0_puts(const char *s)
{
	while (*s)
		tq210_uart0_putc(*s++);
}

struct serial_device tq210_serial_device = {
	.name   = "tq210_uart0",
	.start  = tq210_uart0_init,
	.setbrg = tq210_uart0_setbrg,
	.getc   = tq210_uart0_getc,
	.tstc   = tq210_uart0_tstc,
	.putc   = tq210_uart0_putc,
	.puts   = tq210_uart0_puts,
};

__weak struct serial_device *default_serial_console(void)
{
	return &tq210_serial_device;
}

void tq210_serial_initialize(void)
{
	serial_register(&tq210_serial_device);
}