`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 27.05.2024 14:07:39
// Design Name: 
// Module Name: tb_prefix_adder_16bit
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_prefix_adder_16bit;
    reg [15:0] A;
    reg [15:0] B;
    reg Cin;
    wire [15:0] Sum;
    wire Cout;

    prefix_adder_16bit uut (
        .A(A),
        .B(B),
        .Cin(Cin),
        .Sum(Sum),
        .Cout(Cout)
    );

    initial begin
        // Test cases
        A = 16'h1234; B = 16'h5678; Cin = 0;
        #10;
        A = 16'hFFFF; B = 16'h0001; Cin = 0;
        #10;
        A = 16'h0000; B = 16'h0000; Cin = 1;
        #10;
        A = 16'hAAAA; B = 16'h5555; Cin = 0;
        #10;
        A = 16'h1234; B = 16'h5678; Cin = 1; // 4660 + 22136 + 0 = 26797
        #10;
        A = 16'h1234; B = 16'h5678; Cin = 0;
        #10;
        $stop;
    end
endmodule
