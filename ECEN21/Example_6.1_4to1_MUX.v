// *****************************************************************************
// this module for 3-input AND gate
// *****************************************************************************
module ANDGate3Inputs(A, B, C, Y);
  // set inputs and outputs
  input A, B, C;
  output Y;
  assign  Y = A & B & C;
endmodule

// *****************************************************************************
// this module for 3-input OR gate
// *****************************************************************************
module ORGate4Inputs(A, B, C, D, Y);
  // set inputs and outputs
  input A, B, C, D;
  output  Y;
  assign  Y = A | B | C | D;
endmodule

// *****************************************************************************
// this module for 7-segment display
// *****************************************************************************
module MUX4to1(ValIn, S, ValOut);
  localparam  NIns = 4, NSelect = 2;
  // ***************************************************************************
  // set inputs and outputs
  // ***************************************************************************
  input [NIns-1:0] ValIn;
  input [NSelect-1:0] S;
  output ValOut;

  // ***************************************************************************
  // set variable
  // ***************************************************************************
  wire S0 = S[0], S1 = S[1];
  wire w0 = ValIn[0], w1 = ValIn[1], w2 = ValIn[2], w3 = ValIn[3];
  wire NotS1, NotS0;
  wire O1, O2, O3, O4;

  // ***************************************************************************
  // connections of inverters
  // ***************************************************************************
  not(NotS0, S0);
  not(NotS1, S1);

  // ***************************************************************************
  // connections of 3-input AND gates
  // ***************************************************************************
  ANDGate3Inputs U1(NotS0, w0, NotS1, O1);
  ANDGate3Inputs U2(S0, w1, NotS1, O2);
  ANDGate3Inputs U3(NotS0, w2, S1, O3);
  ANDGate3Inputs U4(S0, w3, S1, O4);

  // ***************************************************************************
  // connection of 4-input OR gate
  // ***************************************************************************
  ORGate4Inputs U5(O1, O2, O3, O4, ValOut);
endmodule

// *****************************************************************************
// this module generate truth table of variables
// *****************************************************************************
module GenInputPattern(out, Clk, Reset);
  parameter  N = 8;
  output    [N-1:0] out;
  input     Clk, Reset;

  // calculate maximum value of output
  localparam  MaxVal = 2 ** N;

  // ***************************************************************************
  // type of output and inputs
  // ***************************************************************************
  wire 	    Clk, Reset;

  // ***************************************************************************
  // type reg because it is used on right hand side (RHS)
  // inside "always" block
  // ***************************************************************************
  reg       [N-1:0] out;

  // ***************************************************************************
  // logic block
  // ***************************************************************************
  always @(posedge Clk or posedge Reset)
    if (Reset)
      out <= 0;
    else if (out >= MaxVal)
      out <= 0;
    else
      out <= out + 1;
endmodule

// *****************************************************************************
// this is the test module
// *****************************************************************************
module TestModule;
  /* Make a ResetSig that pulses once. */
  reg ResetSig = 0;
  initial begin
     # 4 ResetSig = 1;
     # 5 ResetSig = 0;
     // # 29 ResetSig = 1;
     // # 11 ResetSig = 0;
     # 200 $stop;
  end

  // ***************************************************************************
  // Make a regular pulsing clock.
  // ***************************************************************************
  reg        ClkSig = 0;
  always #5  ClkSig = !ClkSig;

  // ***************************************************************************
  // set the number of inputs
  // ***************************************************************************
  parameter NumSelect = 2, NumLine = 4;
  wire      [NumSelect-1:0] SelectVals;
  wire      [NumLine-1:0] LineVals = 4'b0110;
  wire      Y;

  // ***************************************************************************
  // instantiate Truth table module
  // ***************************************************************************
  GenInputPattern U0Table(.out(SelectVals), .Clk(ClkSig), .Reset(ResetSig));
  defparam U0Table.N = NumSelect;

  // ***************************************************************************
  // instantiate the function F
  // ***************************************************************************
  MUX4to1 TestU1 (.ValIn(LineVals), .S(SelectVals), .ValOut(Y));

  // ***************************************************************************
  // saving timing data
  // ***************************************************************************
  initial begin
    $dumpfile("Results.vcd");
    $dumpvars(0, TestModule);
    $monitor("At time %t, Select = %b, line val = %b", $time, SelectVals, Y);
  end
endmodule // test
