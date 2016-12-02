
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

     mov r5, lr
     mrc p15, 0, r1, c0, c0, 0  @ r1 has read Main ID Register (MIDR)
     mov r3, r1, lsr #20        @ get variant field
     and r3, r3, #0x0f          @ r3 has CPU variant
     and r4, r1, #0x0f          @ r4 has CPU revision
     mov r2, r3, lsl #4         @ shift variant field for combined value
     orr r2, r4, r2             @ r2 has combined CPU variant + revision
     cmp r2, #0x30
     mrceq  p15, 0, r0, c1, c0, 1   @ read ACTLR
     orreq  r0, r0, #0x05           @ Enable Cache and TLB maintenance broadcast & Enable Dside prefetch
     orreq  r0, r0, #0x40           @ set bit[6] SMP
     mcreq  p15, 0, r0, c1, c0, 1
     isb

     mov pc, r5
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
