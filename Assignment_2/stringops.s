.text
.align 2
.globl main

main:
#get user input
	
	li $v0, 4	#print a string syscall
	la $a0, originalstr	#load address of originalstr into $a0
	syscall		#prompt user

	li $v0, 8	#read in a string syscall
	la $a0, buffer 	#load byte space into $a0
	li $a1, 80 	#allot 80 bytes of space for string into $a1
	move $t0, $a0	#move inputted string to $s0
	syscall		#store user input in register $a, not to exceed 256 bytes

#this loop cleans string by changing lowercase to upper and replacing non-alphanumeric with underscore

loop:
#get address of beginning of string
#look at first char
	lb $t1, 0($t0)
#check if \0
#if \0 jump exit
	beq $t1, $zero, exit

#increment to next char if newline char
	beq $t1, 10, increment

#else check for ascii value less than 65, between 90 - 97, and greater than 122
	blt $t1, 65, toUnderscore
	bgt $t1, 64, checkupper
	bgt $t1, 89, check90

#if between ASCII 65 - 90, uppercase, move on
checkupper:
	blt $t1, 91, increment

#if between ASCII 90 - 97, nonalph, change to underscore; otherwise check if lowercase
check90:
	blt $t1, 97, toUnderscore 
	bgt $t1, 96, checklower  

#if between ASCII 97 - 122, lowercase, change to Uppercase
checklower:
	blt $t1, 123, toUpper
	j toUnderscore

#move 1 byte (1 char) forward in string
increment:
	add $t0, $t0, 1
	j loop

toUpper:
	add $t1, $t1, -32
	sb $t1, 0($t0)
	j increment

toUnderscore:
	li $t1, 95
	sb $t1, 0($t0)
	j increment

exit:
	li $v0, 4
	la $a0, cleanedstr	#tells user cleaned string is coming
	syscall
	
	li $v0, 4		#load print string syscall into $v0
	la $a0, buffer	#reload byte space to primary address
	syscall

	li $v0, 10 	#done!
	syscall

.data
.align 2

originalstr: .asciiz "Enter string of choice (max 256 chars):\n"
cleanedstr: .asciiz "\nCleaned string:\n"
buffer: .space 80
