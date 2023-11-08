.text

.global calculate
.global R

calculate:
    adr x0, A
    ldr x0, [x0]
    adr x1, B
    ldr x1, [x1]
    adr x2, C
    ldr x2, [x2]
    adr x3, D
    ldr x3, [x3]

    mul x0, x0, x1
    mul x2, x2, x3
    add x0, x0, x2

    adr x4, R
    str x0, [x4]

    ret
.data
    R: .quad
