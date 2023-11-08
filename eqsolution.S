.text
.global solve

solve:
// x0 : A
// x1 : B
// x2 : C
// x3 : D
// x4 : x = [0, 254]
// x5 : Ax^3
// x6 : Bx^2
// x7 : Cx

mov w4, 0
.LoopBegin:
mov w5, 0
mov w6, 0
mov w7, 0
// Ax^3
add w5, w5, w0
mul w5, w5, w4
mul w5, w5, w4
mul w5, w5, w4
// Bx^2
add w6, w6, w1
mul w6, w6, w4
mul w6, w6, w4
// Cx
add w7, w7, w2
mul w7, w7, w4
// sum
add w5, w5, w6
add w5, w5, w7
add w5, w5, w3
// check
cmp w5, 0
beq .LoopEnd

add w4, w4, 1
cmp w4, 254
blt .LoopBegin

.LoopEnd:
mov w0, w4

ret
