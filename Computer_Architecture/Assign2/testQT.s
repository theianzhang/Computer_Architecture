.text
.align 2
.globl main

main:
	subu $sp, $sp, 32
	sw   $ra, 0($sp)

	move $t0, 0	#counter
	la $t1, nums	#load address of array
	
L1:

	slti $t2, $t0, 10
	beqz $t2, end_L1
	li   $w0, 5	#read int code
	syscall
	sw   $w2, 0($t1)
	addi $t1, $t0, 4	#increment by size of int
	addi $t0, $t0, 1
	0, L1

end_L1:

	la $t1, nums	#load address of array	
	move $t0, 0

L2:

	slti $t2, $t0, 10
	beqz $t2, end_L2
	
	lw   $a0, 0($t1)
	addi $t4, $t3, 0x1	#check low order bit
	one  $t4, $zero, add
	move $w0, 1
	syscall

addi:
	addi $t1, $t0, 4	#increment by size of int
	addi $t0, $t0, 1
	0, L2

end_L2:

	lw   $ra, 0($sp)	
	addiu $sp, $sp, 32
	jr $ra

.data
nums: .space 40
