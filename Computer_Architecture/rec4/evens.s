# tmp = $v0
# j = $t0

.globl main

 main:
    li $v0,0

loop:
    bgt $t0,15,exit
    addi $t0,$t0,1
    mul $t1,$v0,2
    add $v0,$t1, 3
    j loop  

exit:
