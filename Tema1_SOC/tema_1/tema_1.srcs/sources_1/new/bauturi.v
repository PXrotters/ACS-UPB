        `timescale 1ns / 1ps
        //////////////////////////////////////////////////////////////////////////////////
        // Company: 
        // Engineer: 
        // 
        // Create Date: 05/18/2024 06:36:12 PM
        // Design Name: 
        // Module Name: bauturi
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
        
        // alegem sa putem primi 50 de bani, 1 leu sau 5 lei conform cerintei:
        // 1 tip de monezi si 2 tipuri de bancnote
        module bauturi(input clk, input reset,
                        input [0:0] bani50_in, input [0:0] leu1_in, input [0:0] lei5_in, input [0:0] produs_in, input [0:0] rest,
                        output reg [0:0] produs_out, output reg [0:0] bani50_rest, output reg [0:0] leu1_rest, output reg [0:0] lei5_rest);
                        
            // bani50_in -> input 50 de bani
            // leu1_in -> input 1 leu
            // lei5_in -> input 5 lei
            // produs_in -> input produs(de 3 lei)
            // rest -> input rest
        
            // produs_out -> output produs(de 3 lei) -> iesire[3]
            // bani50_rest -> output(rest) 50 de bani -> iesire[2]
            // leu1_rest -> output(rest) 1 leu -> iesire[1]
            // lei5_rest -> output(rest) 5 lei -> iesire[0]
            
            // starile pentru automatul Mealy; se pot introduce bani pana la maxim 10 lei
            // stari de input
            localparam stare_start = 6'b000001;
            localparam stare_50bani = 6'b000010;
            localparam stare_1leu = 6'b000011;
            localparam stare_1leu_50 = 6'b000100;
            localparam stare_2lei = 6'b000101;
            localparam stare_2lei_50 = 6'b000110;
            localparam stare_3lei = 6'b000111;
            localparam stare_3lei_50 = 6'b001000;
            localparam stare_4lei = 6'b001001;
            localparam stare_4lei_50 = 6'b001010;
            localparam stare_5lei = 6'b001011;
            localparam stare_5lei_50 = 6'b001100;
            localparam stare_6lei = 6'b001101;
            localparam stare_6lei_50 = 6'b001110;
            localparam stare_7lei = 6'b001111;
            localparam stare_7lei_50 = 6'b010000;
            localparam stare_8lei = 6'b010001;
            localparam stare_8lei_50 = 6'b010010;
            localparam stare_9lei = 6'b010011;
            localparam stare_9lei_50 = 6'b010100;
            localparam stare_10lei = 6'b010101;
            
            // stari de output(rest)
            localparam rest_50bani = 6'b010110;
            localparam rest_1leu = 6'b010111;
            localparam rest_1leu_50 = 6'b011000;
            localparam rest_2lei = 6'b011001;
            localparam rest_2lei_50 = 6'b011010;
            localparam rest_3lei = 6'b011011;
            localparam rest_3lei_50 = 6'b011100;
            localparam rest_4lei = 6'b011101;
            localparam rest_4lei_50 = 6'b011110;
            localparam rest_5lei = 6'b011111;
            localparam rest_5lei_50 = 6'b100000;
            localparam rest_6lei = 6'b100001;
            localparam rest_6lei_50 = 6'b100010;
            localparam rest_7lei = 6'b100011;
            localparam rest_7lei_50 = 6'b100100;
            localparam rest_8lei = 6'b100101;
            localparam rest_8lei_50 = 6'b100110;
            localparam rest_9lei = 6'b100111;
            localparam rest_9lei_50 = 6'b101000;
            localparam rest_10lei = 6'b101001;
            
            reg [5:0] stare_curenta, stare_urmatoare;
            reg [5:0] iesire;
            
            initial begin
                stare_curenta = stare_start;
                stare_urmatoare = stare_start;
                iesire = 6'b0;
            end
            
            always @ (posedge clk, posedge reset)
                if (reset) begin
                    stare_curenta = stare_start;
                    iesire = 6'b0;
        
                    produs_out = 1'b0;
                    bani50_rest = 1'b0;
                    leu1_rest = 1'b0;
                    lei5_rest = 1'b0;
                end
                else begin
                    stare_curenta = stare_urmatoare;
              
                    produs_out = iesire[3];
                    bani50_rest = iesire[2];
                    leu1_rest = iesire[1];
                    lei5_rest = iesire[0];
                    
                    iesire = 6'b0;
                end
            
            always @(*)
                    case (stare_curenta)
                        stare_start: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_50bani;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_1leu;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_5lei;
                                    end
                        stare_50bani: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_1leu;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_1leu_50;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_5lei_50;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = stare_start;
                                    iesire = 4'b0100;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                        stare_1leu: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_1leu_50;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_2lei;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_6lei;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = stare_start;
                                    iesire = 4'b0010;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                        stare_1leu_50: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_2lei;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_2lei_50;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_6lei_50;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_50bani;
                                    iesire = 4'b0010;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                         stare_2lei: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_2lei_50;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_3lei;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_7lei;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_1leu;
                                    iesire = 4'b0010;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                         stare_2lei_50: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_3lei;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_3lei_50;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_7lei_50;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_1leu_50;
                                    iesire = 4'b0010;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                         stare_3lei: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_3lei_50;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_4lei;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_8lei;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_2lei;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 0 lei, deci stare_start
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_start;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                         stare_3lei_50: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_4lei;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_4lei_50;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_8lei_50;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_2lei_50;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 50 de bani, deci stare_50bani
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_50bani;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                         stare_4lei: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_4lei_50;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_5lei;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_9lei;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_3lei;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 1 leu
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_1leu;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                         stare_4lei_50: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_5lei;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_5lei_50;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_9lei_50;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_3lei_50;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 1 leu 50
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_1leu_50;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                          stare_5lei: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_5lei_50;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_6lei;
                                else if (lei5_in == 1'b1)
                                    stare_urmatoare = stare_10lei;
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_4lei;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 2 lei
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_2lei;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                          stare_5lei_50: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_6lei;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_6lei_50;
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_5lei_50;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei introdusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_4lei_50;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 2 lei 50
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_2lei_50;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                          stare_6lei: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_6lei_50;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_7lei;
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_6lei;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei inrodusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_5lei;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 3 lei
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_3lei;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                          stare_6lei_50: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_7lei;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_7lei_50;
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_6lei_50;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei inrodusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_5lei_50;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 3 lei 50
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_3lei_50;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                           stare_7lei: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_7lei_50;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_8lei;
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_7lei;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei inrodusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_6lei;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 4 lei
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_4lei;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                           stare_7lei_50: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_8lei;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_8lei_50;
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_7lei_50;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei inrodusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_6lei_50;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 4 lei 50
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_4lei_50;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                           stare_8lei: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_8lei_50;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_9lei;
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_8lei;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei inrodusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_7lei;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 5 lei
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_5lei;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                           stare_8lei_50: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_9lei;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_9lei_50;
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_8lei_50;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei inrodusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_7lei_50;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 5 lei 50
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_5lei_50;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                           stare_9lei: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_9lei_50;
                                else if (leu1_in == 1'b1)
                                    stare_urmatoare = stare_10lei;
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_9lei;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei inrodusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_8lei;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 6 lei
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_6lei;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                           stare_9lei_50: begin
                                if (bani50_in == 1'b1)
                                    stare_urmatoare = stare_10lei;
                                else if (leu1_in == 1'b1) begin // starea nu se va modifica daca vrem sa introducem 1 leu intrucat nu se poate
                                    stare_urmatoare = stare_9lei_50;
                                    iesire = 4'b0010; // se va da inapoi leul introdus
                                end
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_9lei_50;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei inrodusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_8lei_50;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 6 lei 50
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_6lei_50;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                           stare_10lei: begin
                                if (bani50_in == 1'b1) begin // starea nu se va modifica daca vrem sa introducem 50 de bani intrucat nu se poate
                                    stare_urmatoare = stare_10lei;
                                    iesire = 4'b0100;
                                end
                                else if (leu1_in == 1'b1) begin // starea nu se va modifica daca vrem sa introducem 1 leu intrucat nu se poate
                                    stare_urmatoare = stare_10lei;
                                    iesire = 4'b0010; // se va da inapoi leul introdus
                                end
                                else if (lei5_in == 1'b1) begin// starea nu se va modifica daca vrem sa introducem 5 lei intrucat nu se poate
                                    stare_urmatoare = stare_10lei;
                                    iesire = 4'b0001; // se vor da inapoi cei 5 lei inrodusi
                                end
                                else if (rest == 1'b1) begin
                                    stare_urmatoare = rest_9lei;
                                    iesire = 4'b0010;
                                end
                                // daca se cere produs, vom ramane cu 7 lei
                                else if (produs_in == 1'b1) begin
                                    stare_urmatoare = stare_7lei;
                                    iesire = 4'b1000;
                                end
                                else
                                    stare_urmatoare = stare_curenta;
                                    end
                         // cazurile de rest
                         rest_50bani: begin
                                stare_urmatoare = stare_start;
                                iesire = 4'b0100;
                                end
                         rest_1leu: begin
                                stare_urmatoare = stare_start;
                                iesire = 4'b0010;
                                end
                         rest_1leu_50: begin
                                stare_urmatoare = rest_50bani;
                                iesire = 4'b0010;
                                end
                         rest_2lei: begin
                                stare_urmatoare = rest_1leu;
                                iesire = 4'b0010;
                                end
                         rest_2lei_50: begin
                                stare_urmatoare = rest_1leu_50;
                                iesire = 4'b0010;
                                end
                         rest_3lei: begin
                                stare_urmatoare = rest_2lei;
                                iesire = 4'b0010;
                                end
                         rest_3lei_50: begin
                                stare_urmatoare = rest_2lei_50;
                                iesire = 4'b0010;
                                end
                         rest_4lei: begin
                                stare_urmatoare = rest_3lei;
                                iesire = 4'b0010;
                                end
                         rest_4lei_50: begin
                                stare_urmatoare = rest_3lei_50;
                                iesire = 4'b0010;
                                end
                         rest_5lei: begin
                                stare_urmatoare = rest_4lei;
                                iesire = 4'b0010;
                                end
                         rest_5lei_50: begin
                                stare_urmatoare = rest_4lei_50;
                                iesire = 4'b0010;
                                end
                         rest_6lei: begin
                                stare_urmatoare = rest_5lei;
                                iesire = 4'b0010;
                                end
                         rest_6lei_50: begin
                                stare_urmatoare = rest_5lei_50;
                                iesire = 4'b0010;
                                end
                         rest_7lei: begin
                                stare_urmatoare = rest_6lei;
                                iesire = 4'b0010;
                                end
                         rest_7lei_50: begin
                                stare_urmatoare = rest_6lei_50;
                                iesire = 4'b0010;
                                end
                         rest_8lei: begin
                                stare_urmatoare = rest_7lei;
                                iesire = 4'b0010;
                                end
                         rest_8lei_50: begin
                                stare_urmatoare = rest_7lei_50;
                                iesire = 4'b0010;
                                end
                         rest_9lei: begin
                                stare_urmatoare = rest_8lei;
                                iesire = 4'b0010;
                                end
                         rest_9lei_50: begin
                                stare_urmatoare = rest_8lei_50;
                                iesire = 4'b0010;
                                end
                         rest_10lei: begin
                                stare_urmatoare = rest_9lei;
                                iesire = 4'b0010;
                                end
                         default:
                                stare_urmatoare = stare_start;
                endcase
        endmodule
