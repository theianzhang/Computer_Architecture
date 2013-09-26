strlen:

	li $t0, 0 # initialize the count to zero

loop:

	lbu $t1, 0($a0) # load the next character into t1

	beqz $t1, exit # check for the null character

	addi $a0, $a0, 1 # increment the string pointer

	addi $t0, $t0, 1 # increment the count

	j loop # return to the top of the loop

exit:
