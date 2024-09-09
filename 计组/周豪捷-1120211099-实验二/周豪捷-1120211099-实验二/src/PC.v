`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
//
// Create Date: 2024/6/24 14:06:01
// Design Name: 
// Module Name: PC
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

// PC模块
module PC(
        input clk,
        input [31:0] nxt_inst,
        output [31:0] now_inst
    );

    // 本周期指令
    reg [31:0] getinst;

    // 初始状态
    initial begin
        getinst = 0;
    end

    // 时钟上升沿
    always @(posedge clk) begin
        getinst = nxt_inst;
    end

    // 输出本周期指令
    assign now_inst = getinst;

endmodule