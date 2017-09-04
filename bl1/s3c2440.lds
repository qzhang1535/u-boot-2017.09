SECTIONS {
	. = 0x00000000;
	__program_start = .;
  	.text : {
			output/obj/start.o
			output/obj/lowlevel_init.o
			output/obj/nand_cp.o
			* (.text)
	}
	.rodata ALIGN(4) : {*(.rodata)} 
  	.data ALIGN(4) : { *(.data) }
	
	__bss_start = .;
  	.bss ALIGN(4)  : { *(.bss)  *(COMMON) }
	__end = .;
}
