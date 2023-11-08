.intel_syntax noprefix
.text
.global dot_product

dot_product:
	mov r9, 0
	mov r10, 0
	mov r11, 8
    	vxorpd xmm0, xmm0, xmm0
   	.Begin:

        	add r10, r9
		add r10, r11
        	cmp rdi, r10
        	jae .End

        	vmovups ymm1, [rsi + 4*r9]
        	vmovups ymm2, [rdx + 4*r9]
        	vmulps ymm1, ymm1, ymm2

        	vextractf128 xmm2, ymm1, 1
        	haddps xmm2, xmm1
        	haddps xmm2, xmm2
        	haddps xmm2, xmm2

        	addps xmm0, xmm2

        	add r9, 8

        	jmp .Begin

    	.End:

    	sub r9, 8

    	remain_begin:
        	cmp r9, rdi
        	jae remain_end

        	movss xmm3, [rsi + 4*r9]
        	movss xmm4, [rdx + 4*r9]
        	mulss xmm3, xmm4
        	addss xmm0, xmm3

        	add r9, 1

        	jmp remain_begin

    	remain_end:

    	ret