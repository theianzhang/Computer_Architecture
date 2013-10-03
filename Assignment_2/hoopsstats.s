.text
.align 2
.globl main

main:
	subu $sp, $sp, 32
	sw	$ra, 0($sp)
	sw 	$s0, 4($sp)	#numplayers
	sw 	$s1, 8($sp) #lastname

#give user the prompt
	li $v0, 4		# string syscall 
	la $a0, openingprompt	# load address of prompt
	syscall			

#read in num players and allocate stack accordingly
	li $v0, 5			# read in int
	syscall
	move $t0, $v0	#move user input into $t0
	move $s0, $v0	#move user input into $s0

	li $t7, 44
	mul $t0, $t0, $t7	#multiply 44 x whatever int the user inputs.
						#this is the equivalent of 40 bytes (name) + 4 bytes (float ppm)
						#times however many players there are to analyze

    li $v0, 9   #allocate syscall
    move $a0, $t0  #load byte space into $a0
    syscall     #allocated 44 bytes x user input into memory
	
	move $s1, $v0	#s0 now points to first byte in memory of allocated stack

	subu $sp, $sp, 32
	sw	$ra, 0($sp)
	sw 	$s0, 4($sp)	#numplayers
	sw 	$s1, 8($sp) #lastname

loop:
	li $t9, 0		#initialize counter
	beq $t9, $s0, sorttest	#if all inputs have occured up to user entry, go to sort subroutine
	add $t9, $t9, 1	#else, bump counter by 1 and continue adding inputs

#store last name

	li $v0, 4
	la $a0, lastnameprompt
	syscall

	li $v0, 8	#read string
	la $a0, 0($s1)	#load address to top of heap into $a0
	syscall

	add $s1, $s1, 40	#bump by max string length
	
#store ppg
	li $v0, 4
	la $a0, ppgprompt
	syscall

	li $v0, 6		# code to read int
	syscall			# read int res is $v0
	mov.s $f1, $f0	# put float in $f0

#store mpg
	li $v0, 4
	la $a0, mpgprompt
	syscall

	li $v0, 6		# code to read int
	syscall			# read int res is $v0
	mov.s $f2, $f0	# put float in $f2

#dive ppg by mpg to get ppm
	div.s $f3, $f1, $f2	#put ppm into $f3
	s.s	$f3, 0($s1)	#store ppm on stack
	
	add	$s1, $s1, 4	#bump by float length
	
	j loop

#bubble sort 
#sort:
	#lw $s1, 8($sp)	#restore stack pointer to top of heap (first lastname entered)
	#lw $s0, 4($sp)	#restore stack pointer to numplayers entered
	
	#l2 $s2, 0($s0)	#get num of entries to sort

	#take first look at list
	#loopone: 

		
	#sw $v0,0($t1)
	#addi $t1,$t1,4
	#addi $s2,$s2,1
	#j loopone
	
	#li $s1,40
	#li $s2,0
	#li $s3,4

	#loopthree: 
	
	#beq $s3, $s1, increment
	#add $t1, $t1, $s3
	#lw $t2, 0($t1)   
	#slt $t3, $t0, $t2
	#beq $t3, $zero, swap
	
	#loopfour: 
	#addi $s3, $s3, 4
	#j loopthree

	#swap:   
	#sw $t0, 0($t1)
	#sub $t1, $t1, $s2
	#sw $t2, 0($t1)
	#j loopfour

	#increment:
	#addi $s2, $s2, 4
	#j looptwo

sorttest:
#restore pointers
	lw $s0, 4($sp)	#get pointer to numplayers (for counting)
	lw $s1, 8($sp)	#get pointer to first lastname entered
	j exit	

#print names and floats
exit:

	li $t9, 0		#initialize counter
	beq $t9, $s0, end	#if all inputs have printed up to user entry, go to end subroutine
	add $t9, $t9, 1	#else, bump counter by 1 and continue adding inputs

#print lastname, ppg/mpg
	li $v0, 4		#print string syscall
	la $a0, 0($s1)	#load arg
	syscall	

	add $s1, $s1, 40	#bump past name
	
	li $v0, 2	#print int syscall
	la $a0, 0($s1)	#print float associated with player
	syscall

	add $s1, $s1, 4		#bump past float	

	j exit	

end:

	li $v0, 10
	syscall

.data 
.align 2

openingprompt: .asciiz "Welcome to stats analysis. Please begin by entering the number of players you'd like to analyze:\n"
lastnameprompt: .asciiz "Please enter the last name of a player:\n"
ppgprompt: .asciiz "Please enter the ppg of this player:\n"
mpgprompt: .asciiz "Please enter the mpg of this player:\n"
debug: .asciiz "Got Here\n"
