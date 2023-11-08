    .intel_syntax noprefix
    .global sum
    .text

sum:
    mov r10, 0
    .B_input:
        cmp rdi, r10
        jz .E_input

        mov r8d, [rsi + 4*r10]
        add r8d, [rdx + 4*r10]
        mov [rcx + 4*r10], r8d
        inc r10

        jmp .B_input

    .E_input:

    ret
