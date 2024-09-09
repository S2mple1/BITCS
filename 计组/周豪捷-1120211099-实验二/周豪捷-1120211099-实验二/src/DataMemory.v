`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
//
// Create Date: 2024/6/22 14:54:15
// Design Name: 
// Module Name: DataMemory
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

// DataMemory
module DataMemory(
        input clk,
        input [31:0] in_addr,
        input we,
        input [31:0] wdata,
        output [31:0] rdata
    );

    reg [31:0] Dmem [255:0];

    // 读取机器码
    initial begin
        $readmemh("../machine_code/data_machine_code.txt", Dmem);
    end

    // 读取地址
    wire [7:0] addr = in_addr[9:2];

    // 读取数据
    assign rdata = Dmem[addr];

    // 写入数据
    always @(negedge clk) begin
        if (we)
            begin
                Dmem[addr] <= wdata;
            end
        end
endmodule