.globl lowlevel_init

lowlevel_init:
     mrc p15, 0, r1, c0, c0, 0  @ r1 has read Main ID Register (MIDR)
     and r0, r0, #0x03
     mov r1, #0x0F

    /* SCU Invalidate All Register */
     mov r0, r0, lsl #2
     mov r1, r1, lsl r0
     mrc p15, 0, r2, c15, c0, 0 @ Read Periph Base Address
     str r1, [r2, #0x0C]

    /* Enable SMP */
     mrc p15, 0, r0, c1, c0, 1  @ read ACTLR
     mov r1, r0
     orr r0, r0, #0x40          @ set bit[6] SMP
     cmp r0, r1
     mrcne p15, 0, r0, c1, c0, 1


     /* Enable Cache and TLB maintenance broadcast & Enable Dside prefetch */
     mrc p15, 0, r0, c1, c0, 1
     mov r1, r0
     orr r0, r0, #0x05
     cmp r0, r1
     mcrne  p15, 0, r0, c1, c0, 1
     isb

    mov pc, lr
