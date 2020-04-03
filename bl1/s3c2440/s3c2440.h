#ifndef __S3C2440_H__
#define __S3C2440_H__
// Memory control 
#define rBWSCON    (*(volatile unsigned *)0x48000000)	//Bus width & wait status
#define rBANKCON0  (*(volatile unsigned *)0x48000004)	//Boot ROM control
#define rBANKCON1  (*(volatile unsigned *)0x48000008)	//BANK1 control
#define rBANKCON2  (*(volatile unsigned *)0x4800000c)	//BANK2 cControl
#define rBANKCON3  (*(volatile unsigned *)0x48000010)	//BANK3 control
#define rBANKCON4  (*(volatile unsigned *)0x48000014)	//BANK4 control
#define rBANKCON5  (*(volatile unsigned *)0x48000018)	//BANK5 control
#define rBANKCON6  (*(volatile unsigned *)0x4800001c)	//BANK6 control
#define rBANKCON7  (*(volatile unsigned *)0x48000020)	//BANK7 control
#define rREFRESH   (*(volatile unsigned *)0x48000024)	//DRAM/SDRAM refresh
#define rBANKSIZE  (*(volatile unsigned *)0x48000028)	//Flexible Bank Size
#define rMRSRB6    (*(volatile unsigned *)0x4800002c)	//Mode register set for SDRAM
#define rMRSRB7    (*(volatile unsigned *)0x48000030)	//Mode register set for SDRAM


// I/O PORT 
#define rGPACON    (*(volatile unsigned *)0x56000000)	//Port A control
#define rGPADAT    (*(volatile unsigned *)0x56000004)	//Port A data

#define rGPBCON    (*(volatile unsigned *)0x56000010)	//Port B control
#define rGPBDAT    (*(volatile unsigned *)0x56000014)	//Port B data
#define rGPBUP     (*(volatile unsigned *)0x56000018)	//Pull-up control B

#define rGPCCON    (*(volatile unsigned *)0x56000020)	//Port C control
#define rGPCDAT    (*(volatile unsigned *)0x56000024)	//Port C data
#define rGPCUP     (*(volatile unsigned *)0x56000028)	//Pull-up control C

#define rGPDCON    (*(volatile unsigned *)0x56000030)	//Port D control
#define rGPDDAT    (*(volatile unsigned *)0x56000034)	//Port D data
#define rGPDUP     (*(volatile unsigned *)0x56000038)	//Pull-up control D

#define rGPECON    (*(volatile unsigned *)0x56000040)	//Port E control
#define rGPEDAT    (*(volatile unsigned *)0x56000044)	//Port E data
#define rGPEUP     (*(volatile unsigned *)0x56000048)	//Pull-up control E

#define rGPFCON    (*(volatile unsigned *)0x56000050)	//Port F control
#define rGPFDAT    (*(volatile unsigned *)0x56000054)	//Port F data
#define rGPFUP     (*(volatile unsigned *)0x56000058)	//Pull-up control F

#define rGPGCON    (*(volatile unsigned *)0x56000060)	//Port G control
#define rGPGDAT    (*(volatile unsigned *)0x56000064)	//Port G data
#define rGPGUP     (*(volatile unsigned *)0x56000068)	//Pull-up control G

#define rGPHCON    (*(volatile unsigned *)0x56000070)	//Port H control
#define rGPHDAT    (*(volatile unsigned *)0x56000074)	//Port H data
#define rGPHUP     (*(volatile unsigned *)0x56000078)	//Pull-up control H

#define rGPJCON    (*(volatile unsigned *)0x560000d0)	//Port J control
#define rGPJDAT    (*(volatile unsigned *)0x560000d4)	//Port J data
#define rGPJUP     (*(volatile unsigned *)0x560000d8)	//Pull-up control J

#define rMISCCR    (*(volatile unsigned *)0x56000080)	//Miscellaneous control
#define rDCLKCON   (*(volatile unsigned *)0x56000084)	//DCLK0/1 control
#define rEXTINT0   (*(volatile unsigned *)0x56000088)	//External interrupt control register 0
#define rEXTINT1   (*(volatile unsigned *)0x5600008c)	//External interrupt control register 1
#define rEXTINT2   (*(volatile unsigned *)0x56000090)	//External interrupt control register 2
#define rEINTFLT0  (*(volatile unsigned *)0x56000094)	//Reserved
#define rEINTFLT1  (*(volatile unsigned *)0x56000098)	//Reserved
#define rEINTFLT2  (*(volatile unsigned *)0x5600009c)	//External interrupt filter control register 2
#define rEINTFLT3  (*(volatile unsigned *)0x560000a0)	//External interrupt filter control register 3
#define rEINTMASK  (*(volatile unsigned *)0x560000a4)	//External interrupt mask
#define rEINTPEND  (*(volatile unsigned *)0x560000a8)	//External interrupt pending
#define rGSTATUS0  (*(volatile unsigned *)0x560000ac)	//External pin status
#define rGSTATUS1  (*(volatile unsigned *)0x560000b0)	//Chip ID(0x32440000)
#define rGSTATUS2  (*(volatile unsigned *)0x560000b4)	//Reset type
#define rGSTATUS3  (*(volatile unsigned *)0x560000b8)	//Saved data0(32-bit) before entering POWER_OFF mode 
#define rGSTATUS4  (*(volatile unsigned *)0x560000bc)	//Saved data0(32-bit) before entering POWER_OFF mode 

#endif
