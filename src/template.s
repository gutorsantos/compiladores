################################################
#                    MACROS                    #
################################################
.macro read_int(%reg)
    li a7 5
    ecall
    mv %reg a0
.end_macro

.macro print_int(%reg)
    li a7 1
    mv a0 %reg
    ecall
.end_macro

.macro push()
    addi sp, sp, -4
    sw a0, 0(sp)
.end_macro

.macro pop2()
    lw a0 0(sp)
    lw a1 4(sp)
    addi sp, sp, 8
.end_macro

##############################################
#                    DATA                    #
##############################################
.data 

##############################################
#                    CODE                    #
##############################################
.text 
j main
__exit:
    li a7 10
    ecall

__main:
    // Parser leu "5":
    li a0 5
    push()

    // Parser leu "10":
    li a0 10
    push()

    // Parser leu "5 + 10":
    pop2()
    add a0 a0 a1
    push()

