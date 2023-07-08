.global main

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

##############################################
#                    CODE                    #
##############################################
.text 
j main
__exit:
    li a7 10
    ecall

main:
