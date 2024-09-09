`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
//
// Create Date: 2024/6/23 16:17:04
// Design Name: 
// Module Name: InstructionMemory
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

// Instruction Memory
module InstructionMemory(
        input [31:0] in_addr,   
        output [31:0] instruction
    );
    
    reg [31:0] Imem [255:0];

    // Read the machine code from the file and store it in the Imem
    initial begin
        $readmemh("../machine_code/text_machine_code.txt", Imem);
    end

    // Read the instruction from the Imem
    wire [7:0] addr = in_addr[9:2];

    // Output the instruction
    assign instruction = Imem[addr];

endmodule 