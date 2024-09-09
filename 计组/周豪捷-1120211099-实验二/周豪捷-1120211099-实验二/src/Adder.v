`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
// 
// Create Date: 2024/6/20 21:15:24
// Design Name: Adder.v
// Module Name: Adder
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

// module Adder
module Adder(
        input [31:0] opnd1,
        input [31:0] opnd2,
        output [31:0] res
    );

    reg [31:0] out;

    always @(*) begin
        out = opnd1 + opnd2;
    end

    assign res = out;
endmodule

