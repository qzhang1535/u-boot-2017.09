#define NFCONF         	(*(volatile unsigned int *) 0x4E000000)
#define NFCONT         	(*(volatile unsigned int *) 0x4E000004)
#define NFCMMD         	(*(volatile unsigned int *) 0x4E000008)
#define NFADDR         	(*(volatile unsigned int *) 0x4E00000C)
#define NFDATA         	(*(volatile unsigned char *) 0x4E000010) //注意：类型char
#define NFMECCD0     	(*(volatile unsigned int *) 0x4E000014)
#define NFMECCD1     	(*(volatile unsigned int *) 0x4E000018)
#define NFSECCD     	(*(volatile unsigned int *) 0x4E00001C)
#define NFSTAT         	(*(volatile unsigned int *) 0x4E000020)
#define NFESTAT0     	(*(volatile unsigned int *) 0x4E000024)
#define NFESTAT1     	(*(volatile unsigned int *) 0x4E000028)
#define NFMECC0     	(*(volatile unsigned int *) 0x4E00002C)
#define NFMECC1     	(*(volatile unsigned int *) 0x4E000030)
#define NFMECC         	(*(volatile unsigned int *) 0x4E000034)
#define NFSBLK         	(*(volatile unsigned int *) 0x4E000038)
#define NFEBLK         	(*(volatile unsigned int *) 0x4E00003C)

/*nand command */
#define NAND_CMD_RESET     0xFF

#define NAND_PAGE_SIZE    2048
#define NAND_PAGE_MASK    (NAND_PAGE_SIZE-1)

static void nand_chip_select(void)
{
    int i;
    NFCONT &= ~(1<<1);
    for(i=0; i<10; i++);
}

static void nand_chip_deselect(void)
{
    NFCONT |= (1<<1);
}

static void nand_write_cmd(unsigned char cmd)
{
    NFCMMD = cmd;
}

static void nand_write_addr(unsigned int addr)
{
    int col, page;
    int i;
    col = addr & NAND_PAGE_MASK;
    page = addr / NAND_PAGE_SIZE;
    
    NFADDR = col & 0xff;            /* Column Address A0~A7 */
    for(i=0; i<10; i++);        
    NFADDR = (col >> 8) & 0x0f;        /* Column Address A8~A11 */
    for(i=0; i<10; i++);
    NFADDR = page & 0xff;            /* Row Address A12~A19 */
    for(i=0; i<10; i++);
    NFADDR = (page >> 8) & 0xff;    /* Row Address A20~A27 */
    for(i=0; i<10; i++);
    NFADDR = (page >> 16) & 0x03;    /* Row Address A28~A29 */
    for(i=0; i<10; i++);
}

static void nand_wait_idle(void)
{
    while( !(NFSTAT & 0x01))
        ;
}

void nand_reset(void)
{
    nand_chip_select();
    nand_write_cmd(NAND_CMD_RESET);
    nand_wait_idle();
    nand_chip_deselect();
}

static unsigned char nand_read_byte(void)
{
    return (NFDATA&0xFF);
}


void nand_read_page(unsigned char * dest_addr, unsigned long src_addr, unsigned int size)
{
    int i,j;

    NFCONT &= ~(1<<1);
    for(i=0; i<10; i++);
	
	nand_write_cmd(0x00);
	nand_write_addr(src_addr);
	nand_write_cmd(0x30);
	nand_wait_idle();
	//read one block
	for(j=0; j<size; j++)
	{
		*dest_addr = nand_read_byte();
		dest_addr ++;
	}
    nand_chip_deselect();
}

