.text
.global _start
_start:
	b	reset
		
		@ 0x04: 未定义指令中止模式的向量地址
HandleUndef:
	b   HandleUndef 
 
@ 0x08: 管理模式的向量地址，通过SWI指令进入此模式
HandleSWI:
    b   HandleSWI

@ 0x0c: 指令预取终止导致的异常的向量地址
HandlePrefetchAbort:
    b   HandlePrefetchAbort

@ 0x10: 数据访问终止导致的异常的向量地址
HandleDataAbort:
    b   HandleDataAbort

@ 0x14: 保留
HandleNotUsed:
    b   HandleNotUsed

@ 0x18: 中断模式的向量地址
HandleIRQ:
    b   HandleIRQ

@ 0x1c: 快中断模式的向量地址
HandleFIQ:
    b   HandleFIQ
		

.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word __end
	
reset: 
		ldr     r0, =0x53000000     @ WATCHDOG寄存器地址
		mov     r1, #0x0                     
		str     r1, [r0]              @ 写入0，禁止WATCHDOG，否则CPU会不断重启
		
		bl	    lowlevel_init
		
		ldr  	sp, =(0x30000000 + 4096)	
		
		bl 		main
		


