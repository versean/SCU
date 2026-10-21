// *****************************************************************************
// this module describes behavioral model of a full adder
// *****************************************************************************
module BehaviorAdder(Cin, A, B, Sum, Cout);
  // ***************************************************************************
  // input and output port
  // ***************************************************************************
  input  Cin, A, B;
  output Sum, Cout;

  // ***************************************************************************
  // add operation
  // ***************************************************************************
  assign Sum  = A ^ B ^ Cin;
  assign Cout = (A & B) | (A & Cin) | (B & Cin);
endmodule

// *****************************************************************************
// this module generate truth table of variables
// *****************************************************************************
module GenInputPattern(Out, Clk, Reset);
  parameter  N = 8;
  output    [N-1:0] Out;
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
  reg       [N-1:0] Out;

  // ***************************************************************************
  // logic block
  // ***************************************************************************
  always @(posedge Clk or posedge Reset)
    if (Reset)
      Out <= 0;
    else if (Out >= MaxVal)
      Out <= 0;
    else
      Out <= Out + 1;
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
     # 155 $stop;
  end

  // ***************************************************************************
  // Make a regular pulsing clock.
  // ***************************************************************************
  reg        ClkSig = 0;
  always #4  ClkSig = !ClkSig;

  // ***************************************************************************
  // set the number of inputs
  // ***************************************************************************
  parameter NumInputs = 3;
  wire      [NumInputs-1:0] InputVals;
  wire      Sum, Cout;
  wire      Cin, InA, InB;

  // ***************************************************************************
  // Generate input pattern
  // ***************************************************************************
  GenInputPattern U0Input(.Out(InputVals), .Clk(ClkSig), .Reset(ResetSig));
  defparam U0Input.N = NumInputs;

  // ***************************************************************************
  // set the input bits
  // ***************************************************************************
  assign Cin = InputVals[2];
  assign InA = InputVals[1];
  assign InB = InputVals[0];

  // ***************************************************************************
  // instantiate the function F
  // ***************************************************************************
  BehaviorAdder TestU0(.Cin(Cin), .A(InA), .B(InB), .Sum(Sum), .Cout(Cout));

  // ***************************************************************************
  // saving timing data
  // ***************************************************************************
  initial begin
    $dumpfile("Results.vcd");
    $dumpvars(0, TestModule);
    $display("+--------------------------------------------+");
    $display("|                   t | Cin A B | Cout | Sum |");
    $display("+--------------------------------------------+");
    $monitor("|%t |   %b   |   %b  |  %b  |", $time, InputVals, Cout, Sum);
  end
endmodule // test
