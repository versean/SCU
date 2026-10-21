// Sean Cajigal 2026-10-21
        .syntax         unified
        .cpu            cortex-m4
        .text

// void UseLDRB(void *dst, void *src)

        .global         UseLDRB
        .thumb_func
        .align
UseLDRB:
        //Implementation
        .rept 512
        LDRB    R2,[R1],1
        STRB    R2,[R0],1
        .endr
        BX      LR

// void UseLDRH(void *dst, void *src)

        .global         UseLDRH
        .thumb_func
        .align
UseLDRH:
        //Implementation
        .rept 256
        LDRH    R2,[R1],2
        STRH    R2,[R0],2
        .endr
        BX      LR

// void UseLDR(void *dst, void *src)

        .global         UseLDR
        .thumb_func
        .align
UseLDR:
        //Implementation
        .rept 128
        LDR     R2,[R1],4
        STR     R2,[R0],4
        .endr
        BX      LR

// void UseLDRD(void *dst, void *src)

        .global         UseLDRD
        .thumb_func
        .align
UseLDRD:
	//Implementation
        .rept 64
        LDRD    R2,R3,[R1],8
        STRD    R2,R3,[R0],8
        .endr
        BX      LR

// void UseLDM(void *dst, void *src)

        .global         UseLDM
        .thumb_func
        .align
UseLDM:
	//Implementation
        PUSH    {R4-R11} // pushing all of the preserve registers just in case

        .rept 16
        LDMIA   R1!,{R2-R9}
        STMIA   R0!,{R2-R9}
        .endr

        POP     {R4-R11}
        BX      LR