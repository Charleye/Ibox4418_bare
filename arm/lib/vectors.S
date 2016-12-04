/*
 * vectors - Generic ARM exception vector table code
 *
 * SPDX-License-Identifier: GPL-3.0
 */

.globl _start

    .section ".vectors", "ax"

_start:
    b   reset
    ldr pc, _undefined_instruction
    ldr pc, _software_interrupt
    ldr pc, _prefetch_abort
    ldr pc, _data_abort
    ldr pc, _not_used
    ldr pc, _irq
    ldr pc, _fiq

    .globl  _undefined_instruction
    .globl  _software_interrupt
    .globl  _prefetch_abort
    .globl  _data_abort
    .globl  _not_used
    .globl  _irq
    .globl  _fiq

_undefined_instruction:
    .word   undefined_instruction

_software_interrupt:
    .word   software_interrupt

_prefetch_abort:
    .word   prefetch_abort

_data_abort:
    .word   data_abort

_not_used:
    .word   not_used

_irq:
    .word   irq

_fiq:
    .word   fiq

    .balignl 16, 0xdeadbeef

.globle IRQ_STACK_START_IN
IRQ_STACK_START_IN:
    .word   0x0badc0de

@
@ IRQ stack frame
@
#define S_FRAME_SIZE    72
#define S_OLD_R0    68
#define S_PSR       64
#define S_PC        60
#define S_LR        56
#define S_SP        52

#define S_IP        48
#define S_FP        44
#define S_R10       40
#define S_R9        36
#define S_R8        32
#define S_R7        28
#define S_R6        24
#define S_R5        20
#define S_R4        16
#define S_R3        12
#define S_R2        8
#define S_R1        4
#define S_R0        0

#define MODE_SVC    0x13
#define I_BIT       0x80

    .macro  bad_save_user_regs
    sub sp, sp, #S_FRAME_SIZE
    stmia   sp, {r0 - r12}
    ldr r2, IRQ_STACK_START_IN
    ldmia   r2, {r2 - r3}
    add r0, sp, #S_FRAME_SIZE
    add r5, sp, #S_SP
    mov r1, lr
    stmia   r5, {r0 - r3}
    mov r0, sp
    .endm

    .macro irq_save_user_regs
    sub sp, sp, #S_FRAME_SIZE
    stmia   sp, {r0 -r12}   @calling r0 - r12
    @   !!!! R8 NEEDS to be saved !!!! a reserved stack spot would be good.
    add r8, sp, #S_PC
    stmdb   r8, {sp, lr}^   @calling SP, LR
    str lr, [r8, #0]
    mrs r6, spsr
    str r6, [r8, #4]
    str r0, [r8, #8]
    mov r0, sp
    .endm

    .macro irq_restore_user_regs
    ldmia   sp, {r0 - lr}^
    mov r0, r0      @nop
    ldr lr, [sp, #S_PC]
    add sp, sp, #S_FRAME_SIZE
    subs    pc, lr, #4
    .endm

    .macro get_bad_stack
    ldr r13, IRQ_STACK_START_IN

    str lr, [r13]
    mrs lr, spsr
    str lr, [r13, #4]
    mov r13, #MODE_SVC

    msr spsr, r13
    mov lr, pc
    movs    pc, lr
    .endm

/*
 * exception handlers
 */

    .align 5
undefined_instruction:
    b   .

software_interrupt:
    b   .

prefetch_abort:
    b   .

data_abort:
    b   .

not_used:
    b   .

    .globl irq
    .align 5
irq:
    ldr sp, _stack_end_irq
    irq_save_user_regs
    bl do_irq
    irq_restore_user_regs

fiq:
    b   .
