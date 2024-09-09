`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
//
// Create Date: 2024/6/24 9:26:31
// Design Name: 
// Module Name: MUX1
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

// 12-bit MUX1
module MUX1(
        input wire [11:0] src1,
        input wire [11:0] src2,
        input wire control,
        output reg [11:0] out
    );


    always @(*) begin
        case (control)
            1'b0:
                begin out = src1; end

            1'b1:
                begin out = src2; end
        endcase
    end
endmodule
