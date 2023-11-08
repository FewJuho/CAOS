.data
    scanf_format: .string "%d %d"
    printf_format: .string "%d"
    a: .word 1
    b: .word 1

.text

.global main

main:
    sub sp, sp, 16
    str x30, [sp]

    adr x0, scanf_format
    adr x1, a
    adr x2, b
    bl scanf
 
    adr x1, a
    adr x2, b
    ldr w1, [x1]
    ldr w2, [x2]

    add w1, w1, w2
    adr x0, printf_format
    bl printf

    ldr x30, [sp]
    add sp, sp, 16
    mov x0, 0

    ret
