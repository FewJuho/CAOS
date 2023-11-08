.intel_syntax noprefix
.section .text
.global avx_sin

avx_sin:
	movsd xmm1, xmm0
	mulsd xmm1, xmm1
	movsd xmm2, xmm0
	mov r12, -1
	cvtsi2sd xmm5, r12
	mulsd xmm1, xmm5
	mov r9, 21
	mov r10, 1
	mov r11, 1
	vxorpd xmm0, xmm0, xmm0

	.Begin:

	  cvtsi2sd xmm3, r11
          movsd xmm4, xmm2
          divsd xmm4, xmm3
          addsd xmm0, xmm4
          mulsd xmm2, xmm1
          add r10, 1
          mov rax, r11
          mul r10
          mov r11, rax
          add r10, 1
          mov rax, r11
          mul r10
          mov r11, rax
          cmp r9, r10
	  jz .End
          jmp .Begin

	.End:

	ret
    
