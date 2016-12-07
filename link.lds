OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

STACK_FIQ_SIZE 	= 0x0400;
STACK_IRQ_SIZE 	= 0x0400;
STACK_ABT_SIZE 	= 0x0400;
STACK_UND_SIZE 	= 0x0400;
STACK_SRV_SIZE 	= 0x8000;

MEMORY
{
	rom (rx)	: org = 0x42C00000, len = 0x01000000	/* 16 MB */
	ram (rwx)	: org = 0x43C00000, len = 0x0a000000	/* 160 MB */
}

SECTIONS
{
	.text :
	{
		. = ALIGN(8);
		PROVIDE (__text_start = .);
        *(.vectors)
		arm/start.o (.text)
		*(.text)
		*(.text.*)

		. = ALIGN(8);
		*(.rodata);
		*(.rodata.*);

		. = ALIGN(8);
		*(.glue_7);
		*(.glue_7t);

		. = ALIGN(8);
		PROVIDE (__text_end = .);
	} > rom

	.data_shadow ALIGN(8) :
	{
		PROVIDE (__data_shadow_start = .);
		PROVIDE (__data_shadow_end = (. + SIZEOF (.data)) );
	} > rom

	.data : AT ( ADDR (.data_shadow) )
	{
		PROVIDE (__data_start = .);
		*(.data)
		. = ALIGN(8);
  		PROVIDE (__data_end = .);
	} > ram

	.ARM.exidx :
	{
		. = ALIGN(8);
		PROVIDE (__exidx_start = .);
		*(.ARM.exidx*)
		PROVIDE (__exidx_end = .);
	} > ram

	.ARM.extab :
	{
		PROVIDE (__extab_start = .);
		*(.ARM.extab*)
		PROVIDE (__extab_end = .);
	} > ram

	.bss ALIGN(8) (NOLOAD) :
	{
		PROVIDE (__bss_start = .);
		*(.bss)
		*(.bss.*)
		*(.sbss)
		*(COMMON)
		PROVIDE (__bss_end = .);

		. = ALIGN(8);
		PROVIDE (__heap_start = .);
		*(.heap)
		. = ALIGN(8);
		PROVIDE (__heap_end = .);

		. = ALIGN(8);
		PROVIDE (__stack_start = .);
		PROVIDE (__stack_start_fiq = .);
		. += STACK_FIQ_SIZE;
		PROVIDE (__stack_end_fiq = .);
		. = ALIGN(8);
		PROVIDE (__stack_start_irq = .);
		. += STACK_IRQ_SIZE;
		PROVIDE (__stack_end_irq = .);
		. = ALIGN(8);
		PROVIDE (__stack_start_abt = .);
		. += STACK_ABT_SIZE;
		PROVIDE (__stack_end_abt = .);
		. = ALIGN(8);
		PROVIDE (__stack_start_und = .);
		. += STACK_UND_SIZE;
		PROVIDE (__stack_end_und = .);
		. = ALIGN(8);
		PROVIDE (__stack_start_svc = .);
		. += STACK_SRV_SIZE;
		PROVIDE (__stack_end_svc = .);
		. = ALIGN(8);
		PROVIDE (__stack_end = .);
	} > ram

	/*
	 * Stabs debugging sections.
	 */
	.stab 0 : { *(.stab) }
	.stabstr 0 : { *(.stabstr) }
	.stab.excl 0 : { *(.stab.excl) }
	.stab.exclstr 0 : { *(.stab.exclstr) }
	.stab.index 0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment 0 : { *(.comment) }
	.debug_abbrev 0 : { *(.debug_abbrev) }
	.debug_info 0 : { *(.debug_info) }
	.debug_line 0 : { *(.debug_line) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_aranges 0 : { *(.debug_aranges) }
}
