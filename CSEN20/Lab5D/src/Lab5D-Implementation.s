// Sean Cajigal 2026-10-28 implementing TireDiam and TireCirc
        .syntax         unified
        .cpu            cortex-m4
        .text

// uint64_t TireDiam(uint32_t W, uint32_t A, uint32_t R)

        .global         TireDiam
        .thumb_func
        .align
TireDiam:
        //Implementation
        PUSH    {R4-R11}

        // Step 1, get A x W (steps in slides w/ pseudocode)
        MUL     R4,R0,R1

        // Step 2, quotient and remainder
        LDR     R5,=1270
        UDIV    R6,R4,R5
        MLS     R0,R5,R6,R4

        // Step 3, get integer part by adding R and quotient (R6)
        ADD     R1,R2,R6

        POP     {R4-R11}
        BX      LR

// uint64_t TireCirc(uint32_t W, uint32_t A, uint32_t R)

        .global         TireCirc
        .thumb_func
        .align
TireCirc:
        //Implementation
        PUSH    {R4-R11, LR}

        // Step 0: initialize values for step 1 (steps from the pseudocode on slides)
        LDR     R4,=4987290
        LDR     R5,=3927
        BL      TireDiam

        // Step 1
        MUL     R4,R4,R1
        MUL     R5,R5,R0
        ADD     R6,R4,R5

        // Step 2 (Step 3 is just the final values which is already set in R1 and R0)
        LDR     R7,=1587500
        UDIV    R1,R6,R7
        MLS     R0,R7,R1,R6
        
        POP     {R4-R11, LR}
        BX      LR
        .end