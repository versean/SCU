// Sean Cajigal June 3, 2026

module ALU(F1, F0, A, B, S);
    input [3:0]A, B; //Inputs A and B,
    input F0, F1; //Input for F0 and F1 for command mode.
    output [3:0] S; //Final sum

    wire Co; // For ComparisonLogic to get the overflow bit
    wire [3:0] otherS; // The sum before going through the ResultSelection "RESULTMODULE"
    wire TF; // true if A < B, connects to ResultSelection and is treated as S[0] if "less than" compare mode is active
    wire ResultType; // Don't need CompareType if we only need the less than one.
    
    assign ResultType = F1 & F0; // when F1 and F0 are 1, that mean's we're in "less than" compare mode, so we care about true/false instead of the sum for output

    AddSub4 ADDSUBMODULE (A[3],A[2],A[1],A[0],B[3],B[2],B[1],B[0],F0,otherS[3],otherS[2],otherS[1],otherS[0],Co);
    ComparisonLogic COMPAREMODULE (Co,otherS[3],TF);
    ResultSelection RESULTMODULE (TF,ResultType,otherS[3],otherS[2],otherS[1],otherS[0],S[3],S[2],S[1],S[0]);

endmodule

module ResultSelection(TF,ResultType,In3,In2,In1,In0,Out3,Out2,Out1,Out0);
    input TF, ResultType, In3,In2,In1,In0;
    output Out3,Out2,Out1,Out0;

    // ResultType switches output between either the sum/diff or comparison result (T/F)
    MUX MUX1 (ResultType,In3,1'b0,Out3);
    MUX MUX2 (ResultType,In2,1'b0,Out2);
    MUX MUX3 (ResultType,In1,1'b0,Out1);
    MUX MUX4 (ResultType,In0,TF,Out0);
endmodule

module ComparisonLogic(Ovf,S3,TF);
    input Ovf, S3;
    output TF;

    // TF is XOR of the overflow bit and the sum/diff MSB   
    assign TF = (Ovf ^ S3);
endmodule

module Compl4 (i3, i2, i1, i0, Mode, o3, o2, o1, o0);
    input i3, i2, i1, i0, Mode;
    output o3, o2, o1, o0;

    // flipping the B input to negative if Mode == 1 (subtraction)
    assign o3 = (~Mode & i3) | (Mode & ~i3);
    assign o2 = (~Mode & i2) | (Mode & ~i2);
    assign o1 = (~Mode & i1) | (Mode & ~i1);
    assign o0 = (~Mode & i0) | (Mode & ~i0);
endmodule

module AddSub4 (x3, x2, x1, x0, y3, y2, y1, y0, Mode, s3, s2, s1, s0, Co);
    input x3, x2, x1, x0, y3, y2, y1, y0, Mode;
    output s3, s2, s1, s0, Co;
    wire B3, B2, B1, B0;

    // Flips B and puts mode as carry-in (~B+1) if necessary, then adds A and B as usual.
    Compl4 U1 (y3, y2, y1, y0, Mode, B3, B2, B1, B0);
    FullAdder4 U2 (Mode, x3, x2, x1, x0, B3, B2, B1, B0, s3, s2, s1, s0, Co);
endmodule

module FullAdder4 (Cin, x3, x2, x1, x0, y3, y2, y1, y0, s3, s2, s1, s0, Co);
    input Cin, x3, x2, x1, x0, y3, y2, y1, y0;
    output s3, s2, s1, s0, Co;
    wire c3, c2, c1;

    // Adds two numbers digit by digit, Cin = 1 when subtracting (Mode = 1)
    FullAdd1Bit FA0 (Cin, x0, y0, s0, c1);
    FullAdd1Bit FA1 (c1, x1, y1, s1, c2);
    FullAdd1Bit FA2 (c2, x2, y2, s2, c3);
    FullAdd1Bit FA3 (c3, x3, y3, s3, Co);
endmodule

module FullAdd1Bit (Cin, x, y, s, Cout);
    input Cin, x, y;
    output s, Cout;

    // Based on Full Add truth table.
    assign s = x ^ y ^ Cin;
    assign Cout = (x & y) | (x & Cin) | (y & Cin);
endmodule

module MUX (In1,In2,In3,Out);
    input In1,In2,In3;
    output Out;

    // In1 is the select line. In2 and In3 are the two possible outputs.
    assign Out = (~In1 & In2) | (In1 & In3);
endmodule

/* 

Command Codes (F1, F0)      Input Values (A, B)     Expected Outputs (S)        Explanation
0,0                         0001, 0001              0010                        1 + 1 = 2, testing addition (FullAdder4 and ResultSelection)
0,1                         1000, 0001              0111                        8 - 1 = 7, testing subtraction (FullAdder4, Compl4 and ResultSelection)
1,1                         1000, 0100              0000                        8 < 4 -> false/LSB=0 (ComparisonLogic and ResultSelection)
1,1                         0011, 0101              0001                        3 < 5 -> true/LSB=1 (ComparisonLogic and ResultSelection)
                                                                                All test cases also tested FullAdd1Bit and MUX

*/