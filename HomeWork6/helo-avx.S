.intel_syntax noprefix
.text
.global very_important_function 

very_important_function:
    xor rax, rax
    vxorpd ymm2, ymm2, ymm2

    .Begin:

        cmp rax, rdi
        jz .End

        vmovaps ymm0, [rsi + 4*rax]
        vmovaps ymm1, [rdx + 4*rax]
        vaddps ymm0, ymm0, ymm1
        vaddps ymm2, ymm2, ymm0
        vmovaps [rcx + 4*rax], ymm0
        add rax, 8
        jmp .Begin

    .End:

    vmovaps ymm0, ymm2
    vextractf128 xmm1, ymm0, 1
    haddps xmm1, xmm0
    haddps xmm1, xmm1
    haddps xmm1, xmm1

    vcvtsi2sd xmm0, xmm0, rdi
    vcvtss2sd xmm1, xmm1, xmm1
    vdivsd xmm0, xmm1, xmm0
    
    ret