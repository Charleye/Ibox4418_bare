
#include <linux/linkage.h>

/******************************************************************
 *
 * Startup Code (reset vector)
 *
 ******************************************************************/
    .globl reset

reset:
    /* Set CPU to supervisor mode */
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0xd3
    msr cpsr, r0

    /* Enable NEON & VFP unit */
    mrc p15, 0, r1, c1, c0, 2   /* Read CPACR */
    orr r1, r1, #(0xf << 20)
    mcr p15, 0, r1, c1, c0, 2
    isb
    mov r0, #0x40000000
    vmsr fpexc, r0


    bl  cpu_init_cp15
    bl  cpu_init_crit

    /* Normal exception vectors */
    mrc p15, 0, r0, c1, c0, 0
    bic r0, #(1<<13)
    mcr p15, 0, r0, c1, c0, 0
    /* Setup vector base address register */
    ldr r0, =_start
    mcr p15, 0, r0, c12, c0, 0      @ Set VBAR to r0

    bl init_stacks

    /* copy data section to data_shadow section */
copy_data:
    ldr r0, _text_start
    ldr r1, _text_end
    sub r0, r1, r0
    adr r1, _start
    add r0, r0, r1
    ldr r1, _data_start
    ldr r2, _data_shadow_start
    ldr r3, _data_shadow_end
    sub r2, r3, r2
    add r2, r0, r2
    bl memory_copy  /* r0 = source  r1 = destination r2 = size */


/******************************************************************
 *
 * cpu_init_cp15
 *
 * Setup CP15 registers (cache, MMU, TLBs).
 *
 *****************************************************************/
 ENTRY(cpu_init_cp15)
    /*
     * Invalidate L1 I/D
     */
     mov r0, #0
     mcr p15, 0, r0, c8, c7, 0  @ invalidate TLBs TLBIALL
     mcr p15, 0, r0, c7, c5, 0  @ invalidate icache  ICIALLU
     mcr p15, 0, r0, c7, c5, 6  @ invalidate BP array BPIALL(branch predictor)
     dsb
     isb

     /*
      * Disable MMU stuff and caches
      */
     mrc p15, 0, r0, c1, c0, 0
     bic r0, r0, #0x00002000    @ clear bit[13] (--V--)
     bic r0, r0, #0x00000007    @ clear bits[2:0] (-CAM)
     orr r0, r0, #0x00000002    @ set bit[1] (--A-) Align
     orr r0, r0, #0x00000800    @ set bit[11] (Z---) BTB
     orr r0, r0, #0x00001000    @ set bit[12] (I) I-Cache
     mcr p15, 0, r0, c1, c0, 0

     mov pc, lr
ENDPROC(cpu_init_cp15)

/*****************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 ****************************************************************/
ENTRY(cpu_init_crit)
    b lowlevel_init             @ go setup pll, mux, memory
ENDPROC

/****************************************************************
 *
 * the locations of stacks
 * ld script provide address to these variable
 *
 ***************************************************************/
    __ALIGN
_stack_end_fiq:
    .long __stack_end_fiq
_stack_end_irq:
    .long __stack_end_irq
_stack_end_abt:
    .long __stack_end_abt
_stack_end_und:
    .long __stack_end_und
_stack_end_srv:
    .long __stack_end_srv

/**************************************************************
 *
 * the location of sections
 *
 *************************************************************/
    __ALIGN
_text_start:
    .long __text_start
_text_end:
    .long __text_end
_data_shadow_start:
    .long __data_shadow_start
_data_shadow_end:
    .long __data_shadow_end
_data_start:
    .long __data_start
_data_end:
    .long __data_end
_bss_start:
    .long __bss_start
_bss_end:
    .long __bss_end
