.text
main:
  lw   $r5,tos($r6)       # initialize $r5 as stack pointer

  ldia $r1,$r2,mystring   # load address of mystring into $r1
                          # could instead have done lw $r5,mystring($r6)
  jal  printstr           # print string starting at Mem[$r1]

  jal  readint            # $r2 = read int from keyboard

  ldi  $r1,1              #
  sub  $r5,$r5,$r1        # push the int onto stack
  sw   $r2,0($r5)         #

  ldia $r1,$r3,otherstring
  jal  printstr

  lw   $r1,0($r5)         #
  ldi  $r2,1              # pop the int off stack
  add  $r5,$r5,$r2        #
  jal  printint           # print int contained in $r1

  ldi  $r2,13             # $r2 = carriage return
  output $r2              # print $r2
  halt                    # done

readint:
  ldi   $r2,0
  ldi   $r4,1
  rotr  $r4,$r4,1

  readint_loop:
  input $r1
  rotr  $r3,$r4,7
  and   $r3,$r1,$r3
  bnez  $r3,readint_loop
  output $r1

  ldi   $r3,24
  rotl  $r3,$r3,1
  sub   $r1,$r1,$r3
  and   $r3,$r1,$r4
  bnez  $r3,readint_done
  ldi   $r3,9
  sub   $r3,$r3,$r1
  and   $r3,$r3,$r4
  bnez  $r3,readint_done
  rotl  $r3,$r2,3
  add   $r2,$r2,$r2
  add   $r2,$r2,$r3
  add   $r2,$r2,$r1
  j     readint_loop

  readint_done:
  ret

printint:
  ldi   $r4,0
  ldi   $r3,-2
  add   $r5,$r5,$r3
  ldi   $r3,15
  sw    $r3,0($r5)

  printint_outer:
  ldi   $r2,1
  rotr  $r2,$r2,1
  and   $r2,$r2,$r1
  xor   $r4,$r4,$r2
  xor   $r1,$r1,$r2
  rotl  $r4,$r4,1
  rotl  $r1,$r1,1

  lw    $r3,0($r5)
  bnez  $r3,printint_skip1
  j     printint_print
  printint_skip1:
  ldi   $r2,1
  sub   $r3,$r3,$r2
  sw    $r3,0($r5)

  ldi   $r3,4
  sw    $r3,1($r5)
  
    printint_inner:
  lw    $r3,1($r5)
  bnez  $r3,printint_skip2
  j     printint_outer
    printint_skip2:
  ldi   $r2,1
  sub   $r3,$r3,$r2
  sw    $r3,1($r5)

  rotl  $r4,$r4,4
  ldi   $r2,15
  and   $r2,$r2,$r4
  ldi   $r3,5
  sub   $r2,$r2,$r3
  ldi   $r3,1
  rotr  $r3,$r3,1
  and   $r3,$r3,$r2
  bnez  $r3,printint_skip3
  ldi   $r3,3
  add   $r4,$r4,$r3
    printint_skip3:
  j     printint_inner

  printint_print:
  ldi   $r3,4
  sw    $r3,1($r5)
  ldi   $r1,0
  
  printint_printloop:
  lw    $r3,1($r5)
  bnez  $r3,printint_skip4
  bnez  $r1,printint_ret
  ldi   $r1,24
  rotl  $r1,$r1,1
  output $r1

  printint_ret:
  ldi   $r2,2
  add   $r5,$r5,$r2
  ret

  printint_skip4:
  ldi   $r2,1
  sub   $r3,$r3,$r2
  sw    $r3,1($r5)

  rotl  $r4,$r4,4
  ldi   $r2,15
  and   $r2,$r2,$r4
  bnez  $r1,printint_doit
  bnez  $r2,printint_doit
  j     printint_printloop

  printint_doit:
  ldi   $r3,24
  rotl  $r3,$r3,1
  add   $r2,$r2,$r3
  output $r2
  ldi   $r1,1
  j     printint_printloop

printstr:
  lw    $r2,0($r1)
  bnez  $r2,printstr_doit
  ret

  printstr_doit:
  output $r2
  ldi   $r2,1
  add   $r1,$r1,$r2
  j     printstr

.data
tos:
.word 32768
mystring:
.asciiz "Give me n: "
otherstring:
.asciiz "n = "
