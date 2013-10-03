.text
.align 2
.globl main

fact:
	subu $sp, $sp, 32	# allocate stack
	sw $ra, 0($sp)		# save return address
	beqz $a0, base		# at base case
	sw $a0, 4($sp)		# save n
	addi $a0, $a0, -1	# decrement n
	jal fact			# call fact
	
	lw $t0, 4($sp)		# restore n
	li $t2, 2			# store int 2
	add $t3, $t0, -1	# store n - 1

	#mul $v0, $v0, $t0	# n*fac(n-1)

	mul $v0, $t2, $v0	# 2 * f(n-1)
	add $v0, $v0, $t3	# + (n-1)
	
	b fact_return		# branch to return

base:
	li $v0, 5			# return 5

fact_return:
	lw $ra, 0($sp)		# load return address
	addu $sp, $sp, 32	# pop stack
	jr $ra

main:
	subu $sp, $sp, 32
	sw $ra, 0($sp)
	
	li $v0, 5		# code to read int
	syscall			# read int res is $v0
	move $a0, $v0		# put int in $a0

	jal fact		# call fact
	move $a0, $v0		# put result of fact into $a0
	li $v0, 1		# print int code
	syscall

	lw $ra, 0($sp)		# load return address
	addu $sp, $sp, 32	# pop stack
	jr $ra
