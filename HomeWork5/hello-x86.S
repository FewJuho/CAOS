.intel_syntax noprefix
.global very_important_function
.section .text

very_important_function:
  push rbp
  push r12
  push r13

  sub rsp, 16
  mov r12, rdi
  mov r13, 0

  LoopBegin:
    cmp r12, r13
    jz LoopEnd

    lea rdi, input_fmt[rip]
    mov rsi, rsp
    call scanf

    mov rax, [rsp]
    mov r9, A[rip]
    MOVSXD r9, [r9 + r13*4]
    imul r9

    mov rsi, rax
    lea rdi, output_fmt[rip]
    call printf
    inc r13
    jmp LoopBegin

  LoopEnd:
    add rsp, 16
    pop r13
    pop r12
    pop rbp

  ret

.section  .rodata
  input_fmt:
    .string "%lld"
  output_fmt:
    .string "%lld\n"
