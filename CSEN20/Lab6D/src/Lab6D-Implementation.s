// Sean Cajigal 2026-11-04

        .syntax         unified
        .cpu            cortex-m4
        .text

// uvoid Hanoi(int num, int fm, int to, int aux) ;

        .global         Hanoi
        .thumb_func
        .align
Hanoi:
        PUSH {R4-R8,LR}
        /*
        if (num > 1) Hanoi(num - 1, fm, aux, to) ;
        Move1Disk(fm, to) ;
        if (num > 1) Hanoi(num - 1, aux, to, fm) ;
         */

        // initialize
        MOV R4,R0 // num
        MOV R5,R1 // fm
        MOV R6,R2 // to
        MOV R7,R3 // aux

        // if
        CMP R4,#1
        BLE Skip1
        SUB R0,R4,#1
        MOV R1,R5
        MOV R2,R7
        MOV R3,R6
        BL Hanoi 
Skip1:
        MOV R0,R5
        MOV R1,R6
        BL Move1Disk

        // if
        CMP R4,#1
        BLE Skip2
        SUB R0,R4,#1
        MOV R1,R7
        MOV R2,R6
        MOV R3,R5
        BL Hanoi
Skip2:
        POP {R4-R8,LR}
        BX LR
        .end