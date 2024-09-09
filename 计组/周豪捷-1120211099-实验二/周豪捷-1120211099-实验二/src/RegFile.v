`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
//
// Create Date: 2024/6/24 19:24:32
// Design Name: 
// Module Name: RegFile
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

// RegFile module
module RegFile(
        input clk, // Clock signal
        input rst, // Reset signal
        input reg_we, // Write enable signal
        input [4:0] rs_addr, // Source register address
        input [4:0] rt_addr, // Target register address
        input [4:0] wb_addr, // Write back address
        input [31:0] wb_data, // Write back data
        output [31:0] rs_data, // Source register data
        output [31:0] rt_data // Target register data
    );

    reg [31:0] gpr [31:0]; // General purpose registers

    integer i; // Loop counter

    // Always block for handling reset and write operations
    always @(negedge clk or negedge rst)
    begin
        if(!rst)
            begin
                // If reset is active, clear all registers
                for(i = 0; i < 32; i = i + 1)
                    begin
                        gpr[i] <= 32'b0;
                    end
            end
        else if (reg_we)
            begin
                // If write enable is active, write data to the specified register
                gpr[wb_addr] = wb_data;
            end
    end

    // Assign output data from the specified registers
    assign rs_data = gpr[rs_addr];
    assign rt_data = gpr[rt_addr];

endmodule
