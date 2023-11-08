.text
.global sum

sum:
// x0 (4 bytes)
// x1 : N (8 bytes)
// x2 : *X (4 bytes)
// x3 = current element
// x4 = end condition

.LoopBegin:
mov x3, 0
ldr x3, [x2]
add x0, x0, x3
add x2, x2, 4
sub x1, x1, 1
cmp x1, 0
bgt .LoopBegin

ret
