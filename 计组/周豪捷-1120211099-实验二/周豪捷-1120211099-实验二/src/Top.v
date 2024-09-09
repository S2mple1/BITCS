`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
//
// Create Date: 2024/6/25 19:40:25
// Design Name: 
// Module Name: Top
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

// Top module
module Top(
    input clk, // Clock signal
    input rst  // Reset signal
    );

    integer const_4 = 32'd4; // Constant value of 4

    // PC
    wire [31:0] current_instr_addr, next_instr_addr; // Current and next instruction addresses
    wire [31:0] instr; // Instruction

    // RegFile
    wire [4:0] rs1_addr, rs2_addr, rd_addr; // Source 1, source 2, and destination register addresses
    wire [31:0] rs1_data, rs2_data, rd_data; // Source 1, source 2, and destination register data

    // ControlUnit
    wire [6:0] opcode; // Opcode
    wire [2:0] funct3; // Function 3
    wire [6:0] funct7; // Function 7
    wire c1, c2, dmem_we, reg_we; // Control signals
    wire [3:0] alu_op; // ALU operation
    wire [1:0] c3; // Control signal 3

    // BrUnit
    wire [31:0] act_offset, offset; // Active offset and offset
    wire jump; // Jump signal
    wire [19:0] jal_offset; // Jump and link offset
    wire [11:0] br_offset; // Branch offset
    wire [2:0] branch; // Branch signal

    // MUX1
    wire [11:0] imm_I, imm_S; // Immediate I and S
    wire [11:0] imm; // Immediate

    // ALU
    wire [31:0] alu_opnd1, alu_opnd2, alu_res; // ALU operands and result
    wire SF, CF, ZF, OF, PF; // Status flags

    // ImmGen
    wire [31:0] imm_expand; // Expanded immediate

    // jal
    wire [31:0] reg_jal; // Register for jal

    // Dmem
    wire [31:0] read_dmem_data; // Data read from data memory

    // Instantiate modules
    // PC, InstructionMemory, BrUnit, MUX2, ControlUnit, MUX1, ImmGen, ALU, RegFile, MUX2, Adder, DataMemory, MUX3 modules

    PC Pc(
        .clk(clk),
        .nxt_inst(next_instr_addr),
        .now_inst(current_instr_addr)
    );

    InstructionMemory Imem(
        .in_addr(current_instr_addr),
        .instruction(instr)
    );

    assign jal_offset = instr[31:12];
    assign br_offset = {instr[31:25], instr[11:7]};
    BrUnit BrU(
        .br_offset(br_offset),
        .jal_offset(jal_offset),
        .rs1_data(rs1_data),
        .rs2_data(rs2_data),
        .branch(branch),
        .jump(jump),
        .offset(offset)
    );
    MUX2 MUX_BR(
        .src1(const_4),
        .src2(offset),
        .control(jump),
        .out(act_offset)
    );

    assign opcode = instr[6:0];
    assign funct3 = instr[14:12];
    assign funct7 = instr[31:25];

    // ControlUnit
    ControlUnit CU(
        .opcode(opcode),
        .funct3(funct3),
        .funct7(funct7),
        .c1(c1),
        .c2(c2),
        .c3(c3),
        .alu_op(alu_op),
        .branch(branch),
        .dmem_we(dmem_we),
        .reg_we(reg_we)
    );

    assign imm_I = instr[31:20];
    assign imm_S = {instr[31:25], instr[11:7]};

    // MUX1
    MUX1 MUX_1(
        .src1(imm_I),
        .src2(imm_S),
        .control(c1),

        .out(imm)
    );

    // ImmGen
    ImmGen IG(
        .in(imm),
        .out(imm_expand)
    );

    // ALU
    assign alu_opnd1 = rs1_data;
    ALU Alu(
        .OP(alu_op),
        .A(alu_opnd1),
        .B(alu_opnd2),
        .F(alu_res),
        .ZF(ZF),
        .CF(CF),
        .OF(OF),
        .SF(SF),
        .PF(PF)
    );

    // RegFile
    assign rs2_addr = instr[24:20];
    assign rs1_addr = instr[19:15];
    assign rd_addr = instr[11:7];
    RegFile RF(
        .clk(clk),
        .rst(rst),
        .reg_we(reg_we),
        .rs_addr(rs1_addr),
        .rt_addr(rs2_addr),
        .wb_addr(rd_addr),
        .wb_data(rd_data),

        .rs_data(rs1_data),
        .rt_data(rs2_data)
    );

    // MUX2
    MUX2 MUX_2(
        .src1(rs2_data),
        .src2(imm_expand),
        .control(c2),
        .out(alu_opnd2)
    );

    // Adder
    Adder Add_J(
        .opnd1(current_instr_addr),
        .opnd2(act_offset),
        .res(next_instr_addr)
    );

    // jal
    Adder Add_4(
        .opnd1(const_4),
        .opnd2(current_instr_addr),

        .res(reg_jal)
    );

    // Dmem
    DataMemory Dmem(
        .clk(clk),
        .in_addr(alu_res),
        .we(dmem_we),
        .wdata(rs2_data),
        .rdata(read_dmem_data)
    );

    // MUX3
    MUX3 MUX_3(
        .src1(alu_res),
        .src2(read_dmem_data),
        .src3(reg_jal),
        .control(c3),

        .out(rd_data)
    );

endmodule