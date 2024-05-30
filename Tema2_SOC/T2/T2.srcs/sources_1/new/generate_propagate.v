
module generate_propagate(
    input wire A,
    input wire B,
    output wire G,
    output wire P
);
    assign G = A & B;
    assign P = A | B;
endmodule