// Sean Cajigal 2026-10-19
        .syntax         unified
        .cpu            cortex-m4
        .text

// void UseLDRB(void *dst, void *src)

        .global         UseLDRB
        .thumb_func
        .align
UseLDRB:
        //Implementation
        .rept 64
        LDRB    R2,[R1,1]!
        STRB    R2,[R0]
        .endr
        BX      LR

// void UseLDRH(void *dst, void *src)

        .global         UseLDRH
        .thumb_func
        .align
UseLDRH:
        //Implementation
        .rept 32
        LDRH    R2,[R1,2]!
        STRH    R2,[R0]
        .endr
        BX      LR

// void UseLDR(void *dst, void *src)

        .global         UseLDR
        .thumb_func
        .align
UseLDR:
        //Implementation
        .rept 16
        LDR     R2,[R1,4]!
        STR     R2,[R0]
        BX      LR

// void UseLDRD(void *dst, void *src)

        .global         UseLDRD
        .thumb_func
        .align
UseLDRD:
	//Implementation
        .rept 8
        LDRD    R2,R3,[R1,8]!
        STRD    R2,R3,[R0]
        BX      LR

// void UseLDM(void *dst, void *src)

        .global         UseLDM
        .thumb_func
        .align
UseLDM:
	//Implementation
        PUSH    {R4-R11}

        .rept 11
        LDMIA   R1!,{R2-R12}
        STMIA   R0!,{R2-R12}
        .endr

        LDMIA   R1,{R2-R8}
        STMIA   R0,{R2-R8}

        POP     {R4-R11}
        BX      LR
        .end