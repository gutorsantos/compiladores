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
    li a7 11
    li a0 '\n'
    ecall
.end_macro

##############################################
#                    CODE                    #
##############################################
.text 
main:
  # s11 é o ponteiro de variáveis e não deve ser alterado
  la s11 variables

