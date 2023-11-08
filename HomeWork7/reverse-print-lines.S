.intel_syntax noprefix
  .text
  .global _start

_start:
  mov r13, 131072
  
  mov rax, 45
  mov rbx, 0
  int 0x80
  mov rsi, rax

  mov rax, 45
  add rsi, r13
  mov rbx, rsi
  int 0x80

  sub rax, r13
  mov rsi, rax
  mov r12, rax
  
  mov rax, 45
  mov rbx, 0
  int 0x80
  mov r14, rax
  
  mov rax, 45
  add r14, 4096
  mov rbx, r14
  int 0x80
  
  mov r14, rax
  sub r14, 4096
  mov QWORD PTR[r14], 0
  mov r15, 0
  mov rdi, 0

  read:
  mov rax, 3
  mov rbx, 0
  mov rcx, rsi
  mov rdx, r13
  int 0x80
  add r15, 1
  add rsi, rax
  add rdi, rax
  mov QWORD PTR[r14 + 8 * r15], rdi
  cmp rax, 1
  jg read

  write:
  cmp r15, 0
  je end
  mov rax, 4
  mov rbx, 1
  mov r9, QWORD PTR[r14 + 8 * r15]
  sub r15, 1
  mov r10, QWORD PTR[r14 + 8 * r15]
  mov r11, r12
  add r11, r10
  sub r9, r10
  mov rcx, r11
  mov rdx, r9
  int 0x80
  jmp write
  end:
  
  ret