
module black_cell(
    input wire Gk_j, Pk_j,
    input wire Gj_i, Pj_i,
    output wire G, P
);
    assign G = Gk_j | (Pk_j & Gj_i);
    assign P = Pk_j & Pj_i;
endmodule