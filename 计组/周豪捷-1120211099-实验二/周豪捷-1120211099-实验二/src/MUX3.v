`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
//
// Create Date: 2024/6/24 10:35:21
// Design Name: 
// Module Name: MUX3
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

// 3-to-1 multiplexer
module MUX3(
        input wire [31:0] src1,
        input wire [31:0] src2,
        input wire [31:0] src3,         
        input wire [1:0] control,
        output reg [31:0] out
    );

    always @(*) begin
        case (control)
            2'b00:
                begin out = src1; end

            2'b01:
                begin out = src2; end

            2'b10:
                begin out = src3; end
        endcase
    end
endmodule
