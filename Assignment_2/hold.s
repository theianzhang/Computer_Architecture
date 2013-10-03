#load values to manipulate

#get int
	li $t0, 0($a0)
#get lastname
	lw $t1, 0($a1)
#get ppg
	l.s $f4, 0($f0)
#get mpg
	l.s $f6, 0($f2)


	sll $t0, $v0, 2	# shift bits left (mult by 4)

	li $v0, 9     	# code 9 == allocate memory
	li $a0, 0($t0)	# 
	syscall         # call the service.
                	# $v0 <-- the address of the first byte
                	# of the dynamically allocated block

	move $t1, $v0	# $t1 now points to first byte of memory containing int
