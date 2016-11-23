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


