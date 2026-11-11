        .syntax     unified
        .cpu        cortex-m4
        .text

// uint32_t GetNibble(void *nibbles, uint32_t index) ;

        .global     GetNibble
        .thumb_func
        .align

GetNibble:
	//Implementation
        LSR     R2,R1,#1
        LDRB    R2,[R0,R2]
        AND     R3,R1,#1
        CMP     R3,#1
        IT      EQ
        LSREQ   R2,R2,#4
        AND     R0,R2,#0b00001111
        BX      LR

// void PutNibble(void *nibbles, uint32_t index, uint32_t nibble) ;

        .global     PutNibble
        .thumb_func
        .align

PutNibble:
	//Implementation
        PUSH    {R4}
        ADD     R4,R0,R1,LSR #1
        LDRB    R3,[R4]
        
        AND     R1,R1,#1
        CMP     R1,#1
        ITTEE   EQ
        ANDEQ   R3,R3,#0b00001111
        ORREQ   R3,R3,R2,LSL #4
        ANDNE   R3,R3,#0b11110000
        ORRNE   R3,R3,R2

        STRB    R3,[R4]
        POP     {R4}
        BX      LR
        .end
