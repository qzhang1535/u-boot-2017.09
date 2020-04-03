#define GPHCON              (*(volatile unsigned long *)0x56000070)
#define GPHDAT              (*(volatile unsigned long *)0x56000074)
#define GPHUP               (*(volatile unsigned long *)0x56000078)

#define ULCON0              (*(volatile unsigned long *)0x50000000)
#define UCON0               (*(volatile unsigned long *)0x50000004)
#define UFCON0              (*(volatile unsigned long *)0x50000008)
#define UMCON0              (*(volatile unsigned long *)0x5000000c)
#define UTRSTAT0            (*(volatile unsigned long *)0x50000010)
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




void putc(unsigned char c)
{
	if(c == '\n')
	{
		putc('\r');
	}
    /* 等待，直到发送缓冲区中的数据已经全部发送出去 */
    while (!(UTRSTAT0 & 0x02));
    
    /* 向UTXH0寄存器中写入数据，UART即自动将它发送出去 */
    UTXH0 = c;
}


void serial_puts(char* str)
{
	while(*str)
	{
		putc(*str);
		str++;
	}
}
/*
void serial_putsn(unsigned char* str, unsigned int count)
{
	while(count--)
	{
		putc(*str);
		str++;
	}
}
*/
