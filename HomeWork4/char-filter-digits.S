.text
.global main

main:
    sub sp, sp, 16
    str x30, [sp]

    .Begin:
        bl getchar_unlocked

	cmp w0, 0
        blt .End

        cmp w0, '0'
        blt .Begin
        cmp w0, '9'
        bgt .Begin

        bl putchar_unlocked
        b .Begin
    .End:

    ldr x30, [sp]
    add sp, sp, 16
    mov x0, 0

    ret
