`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/19/2024 04:02:34 PM
// Design Name: 
// Module Name: simulare_bauturi
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


module simulare_bauturi();

    reg clk;
    reg reset;
    reg [0:0] bani50_in;
    reg [0:0] leu1_in;
    reg [0:0] lei5_in;
    reg [0:0] produs_in;
    reg [0:0] rest;
    
    wire [0:0] produs_out;
    wire [0:0] bani50_rest;
    wire [0:0] leu1_rest;
    wire [0:0] lei5_rest;
    
    bauturi automat_bauturi(clk, reset,
                            bani50_in, leu1_in, lei5_in, produs_in, rest,
                            produs_out, bani50_rest, leu1_rest, lei5_rest);

    initial begin
        reset = 1;
        clk = 0;
        bani50_in = 1'b0;
        leu1_in = 1'b0;
        lei5_in = 1'b0;
        produs_in = 1'b0;
        rest = 1'b0;

        #40
        reset = 0;
        
        #40
        // introducem 5 lei
        lei5_in = 1'b1;
        
        #40
        lei5_in = 1'b0;
        
        // bagam 50 de bani timp de 2 perioade <=> 1 leu
        bani50_in = 1'b1;
        #40
        
        #40
        bani50_in = 1'b0;
        
        // incercam sa introducem 5 lei, nu ar trebui sa functioneze
        lei5_in = 1'b1;
        
        #40
        lei5_in = 1'b0;
        
        leu1_in = 1'b1;
        
        #40
        leu1_in = 1'b0;
        #40

        // perioada de stationare
        #40
        
        // cerem produsul
        produs_in = 1'b1;

        #40
        produs_in = 1'b0;
        
        // introducem 5 lei
        lei5_in = 1'b1;

        #40
        
        #40
        lei5_in = 1'b0;
        
        // cerem produsul
        produs_in = 1'b1;

        #40
        produs_in = 1'b0;
        
        // cerem restul
        rest = 1'b1;

        #40
        bani50_in = 1'b0;
        leu1_in = 1'b0;
        lei5_in = 1'b0;
        produs_in = 1'b0;
        rest = 1'b0;

        #250
        $finish;
    end
    
        always
        #20 clk = ~clk;
endmodule
