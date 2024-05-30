`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 27.05.2024 14:06:07
// Design Name: 
// Module Name: prefix_adder_16bit
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

module prefix_adder_16bit(
    input wire [15:0] A,
    input wire [15:0] B,
    input wire Cin,
    output wire [15:0] Sum,
    output wire Cout
);
    wire [15:0] G, P;
    wire [15:0] C;

    // Generate and Propagate
    generate
        genvar i;
        for (i = 0; i < 16; i = i + 1) begin : gen_prop
            generate_propagate gp (.A(A[i]), .B(B[i]), .G(G[i]), .P(P[i]));
        end
    endgenerate

    // Prefix Calculation
    wire [15:0] Gp1, Pp1, Gp2, Pp2, Gp3, Pp3, Gp4, Pp4;

    // First level
    generate
        for (i = 1; i < 16; i = i + 2) begin : level1
            black_cell bc1 (.Gk_j(G[i]), .Pk_j(P[i]), .Gj_i(G[i-1]), .Pj_i(P[i-1]), .G(Gp1[i]), .P(Pp1[i]));
        end
    endgenerate

    // Second level
    generate
        for (i = 3; i < 16; i = i + 4) begin : level2
            black_cell bc2 (.Gk_j(Gp1[i]), .Pk_j(Pp1[i]), .Gj_i(Gp1[i-2]), .Pj_i(Pp1[i-2]), .G(Gp2[i]), .P(Pp2[i]));
        end
    endgenerate

    // Third level
    generate
        for (i = 7; i < 16; i = i + 8) begin : level3
            black_cell bc3 (.Gk_j(Gp2[i]), .Pk_j(Pp2[i]), .Gj_i(Gp2[i-4]), .Pj_i(Pp2[i-4]), .G(Gp3[i]), .P(Pp3[i]));
        end
    endgenerate

    // Fourth level
    generate
        for (i = 15; i < 16; i = i + 16) begin : level4
            black_cell bc4 (.Gk_j(Gp3[i]), .Pk_j(Pp3[i]), .Gj_i(Gp3[i-8]), .Pj_i(Pp3[i-8]), .G(Gp4[i]), .P(Pp4[i]));
        end
    endgenerate

    // Calculate Carry
    assign C[0] = Cin;
    generate
        for (i = 1; i < 16; i = i + 1) begin : carry
            assign C[i] = G[i-1] | (P[i-1] & C[i-1]);
        end
    endgenerate

    // Calculate Sum
    generate
        for (i = 0; i < 16; i = i + 1) begin : sum
            assign Sum[i] = A[i] ^ B[i] ^ C[i];
        end
    endgenerate

    // Carry Out
    assign Cout = C[15];

endmodule
