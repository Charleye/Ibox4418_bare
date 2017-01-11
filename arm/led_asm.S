.globl led_on
led_on:
    ldr r0, =0xC001C004
    mov r1, #0x1000
    str r1, [r0]
    ldr r0, =0xC001C000
    mov r1, #0x00
    str r1, [r0]

    mov pc, lr
