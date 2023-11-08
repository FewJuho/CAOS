.text
.global solve

solve:
// x0 : A
// x1 : B
// x2 : C
// x3 : D
// x4 : x = [0, 254]
// x5 : sum
// x6 : Ax^3
// x7 : Bx^2
// x8 : Cx

mov x4, 0
.LoopBegin:
mov x5, 0
mov x6, 0
mov x7, 0
mov x8, 0
// Ax^3
add x6, x6, x0
mul x6, x6, x4
mul x6, x6, x4
mul x6, x6, x4
// Bx^2
add x7, x7, x1
mul x7, x7, x4
mul x7, x7, x4
// Cx
add x8, x8, x2
mul x8, x8, x4
// sum
add x5, x6, x7
add x5, x5, x8
add x5, x5, x3
// check
cmp x5, 0
beq .LoopEnd

add x4, x4, 1
b .LoopBegin

.LoopEnd:
mov x0, x5

ret
