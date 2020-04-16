#define COCKTIME    0x4C000000    
#define MPLLCON        0x4C000004
#define UPLLCON        0x4C000008
#define CLKCON        0x4C00000C
#define CLKSLOW        0x4C000010
#define CLKDIVN     0x4C000014
#define CAMDIVN     0x4C000018
#define LOCKTIME	0x4C000000



#define GPHCON              (0x56000070)
#define GPHDAT              (0x56000074)
#define GPHUP               (0x56000078)

#define ULCON0              (0x50000000)
#define UCON0               (0x50000004)
#define UFCON0              (0x50000008)
#define UMCON0              (0x5000000c)
#define UTRSTAT0            (0x50000010)
#define UTXH0               (0x50000020)
#define URXH0               (0x50000024)
#define UBRDIV0             (0x50000028)

#define BWSCON (0x48000000)
#define BANKCON0 (0x48000004)
#define BANKCON1 (0x48000008)
#define BANKCON2 (0x4800000C)
#define BANKCON3 (0x48000010)
#define BANKCON4 (0x48000014)
#define BANKCON5 (0x48000018)
#define BANKCON6 (0x4800001C)
#define BANKCON7 (0x48000020)
#define REFRESH (0x48000024)
#define BANKSIZE (0x48000028)
#define MRSRB6 (0x4800002C)
#define MRSRB7 (0x48000030)

#define NFCONF         	(0x4E000000)
#define NFCONT         	(0x4E000004)


	.globl lowlevel_init
lowlevel_init:
	mov	r12, lr

	bl system_clock_init
	bl uart_asm_init
	bl mem_asm_init
	bl nand_asm_init

	mov	lr, r12
	mov	pc, lr


system_clock_init:	
    /*FCLK:HCLK:PCLK=1:4:8*/
    ldr r0, =CLKDIVN
    mov r1, #0x05
    str r1, [r0]   
	
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0xc0000000
	mcr p15, 0, r0, c1, c0,0
	
    /*UPLL=(m*Fin)/(P*(1<<S)), m=(MDIV+8), p=(PDIV+2), s=SDIV*/
    ldr r0, =UPLLCON
    ldr r1, =((0x10<<12)|(0x01<<4)|(0x01))
    str r1, [r0]

    ldr r0, =0
    ldr r1, =100
loop:
    add r0, r0, #1
    cmp r0, r1
    bne loop
	
    /*MPLL=(2*m*Fin)/(P*(1<<S)), m=(MDIV+8), p=PDIV+2 s=SDIV*/
    ldr r0, =MPLLCON 
    ldr r1, =((0x5C<<12)|(0x01<<4)|(0x01))
    str r1, [r0]
		
	mov	pc, lr
	
uart_asm_init:	
	ldr r0, =GPHCON
	ldr r1, [r0]
	orr r1, r1, #0xa0
	str r1, [r0]
	
	ldr r0, =GPHUP
	ldr r1, =0x0c
	str r1, [r0]
	
	ldr r0, =ULCON0
	ldr r1, =0x03
	str r1, [r0]
	
	ldr r0, =UCON0
	ldr r1, =0x05
	str r1, [r0]
	
	ldr r0, =UFCON0
	ldr r1, =0x00
	str r1, [r0]	
	
	ldr r0, =UMCON0
	ldr r1, =0x00
	str r1, [r0]
	
	ldr r0, =UBRDIV0
	ldr r1, =27
	str r1, [r0]
	
	mov	pc, lr
	
mem_asm_init:
	ldr r0, =BWSCON
	ldr r1, =0x22011110
	str r1, [r0]
	
	ldr r0, =BANKCON0
	ldr r1, =0x00000700
	str r1, [r0]
	
	ldr r0, =BANKCON1
	ldr r1, =0x00000700
	str r1, [r0]
	
	ldr r0, =BANKCON2
	ldr r1, =0x00000700
	str r1, [r0]
	
	ldr r0, =BANKCON3
	ldr r1, =0x00000700
	str r1, [r0]
	
	ldr r0, =BANKCON4
	ldr r1, =0x00000700
	str r1, [r0]
	
	ldr r0, =BANKCON5
	ldr r1, =0x00000700
	str r1, [r0]
	
	ldr r0, =BANKCON6
	ldr r1, =0x00018005
	str r1, [r0]
	
	ldr r0, =BANKCON7
	ldr r1, =0x00018005
	str r1, [r0]
	
	ldr r0, =REFRESH
	ldr r1, =0x008C04F4
	str r1, [r0]
	
	ldr r0, =BANKSIZE
	ldr r1, =0x000000B1
	str r1, [r0]
	
	ldr r0, =MRSRB6
	ldr r1, =0x30
	str r1, [r0]
	
	ldr r0, =MRSRB7
	ldr r1, =0x30
	str r1, [r0]
	
	mov	pc, lr
	
nand_asm_init:
	ldr r0, =NFCONF
	ldr r1, =((0<<12)|(3<<8)|(0<<4))
	str r1, [r0]
	
	ldr r0, =NFCONT
	ldr r1, =((0x01<<4)|(0x01<<1)|(0x01<<0))
	str r1, [r0]
	
	mov	pc, lr
	
	
	

