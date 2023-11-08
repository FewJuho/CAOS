.text
.global main

main:
    sub sp, sp, 16
    str x30, [sp]

    mov x0, 0
    mov x1, 8
    mov x19, 0 
    mov x20, 8
    mov x21, 0 
    mov x22, 2
    bl realloc

    mov x19, x0

    .B_input:

        bl getchar_unlocked
        cmp w0, 0
        blt .E_input

        str w0, [x19, x21]
        add x21, x21, 1
        cmp x21, x20
        bne .Skip
	
        mul x20, x20, x22
        mov x1, x20
	mov x0, x19
        bl realloc

        mov x19, x0

        .Skip:
        b .B_input

    .E_input:

    .B_output:

        cmp x21, 1
        blt .E_output

        sub x21, x21, 1
        ldr x0, [x19, x21]
        bl putchar_unlocked
        b .B_output

    .E_output: 

    mov x0, x19
    bl free
    ldr x30, [sp]
    add sp, sp, 16

    ret