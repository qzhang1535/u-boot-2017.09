
static void (*theApp)(void);


static int check_flashboot_mode(void)
{
    volatile unsigned int *pdw = (volatile unsigned int *)0;
    unsigned int dwVal;
    dwVal = *pdw; 
    *pdw = 0x12345678;
    if (*pdw != 0x12345678) /* 向norflash写数据需要特定时序，不能直接赋值 */
    {
        return 1; //boot from norflash
    }
    else //boot from nandflash
    {
        *pdw = dwVal; //数据还原
        return 0;
    }
}



int main(void)
{
	int i = 0;
	volatile unsigned char *sdram = (volatile unsigned char *)0x30000000;
	volatile unsigned char *start = (volatile unsigned char *)4096;
	
	serial_puts("\r\n\r\n\r\n");
	
	if(check_flashboot_mode() == 0)
	{
		serial_puts("Boot from Nandflash\r\n");
		for(i = 0; i < 256; ++i)
		{
			nand_read_page(sdram + (i * 1024), 4096 + (i *1024), 2048);
		}
	}
	else
	{
		serial_puts("Boot from Norflash\r\n");	
		for(i = 0; i < (512*1024); ++i)
		{
			sdram[i] = start[i];
		}
	}
	
	serial_puts("Jump to uboot...");
	theApp = (void (*)(void))0x30000000;
	theApp();
		
	while(1)
	{
	}	

	return 0;
}
