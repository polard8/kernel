;;
;; i/o delay
;;

%macro IODELAY 0 

    pushf
    popf
    jmp $+2

%endmacro


;; Defines.

KERNEL_DS EQU 0x10
KERNEL_SS EQU 0x10



