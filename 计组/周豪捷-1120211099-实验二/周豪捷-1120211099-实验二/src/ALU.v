`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
//
// Create Date: 2024/6/20 18:26:35
// Design Name: 
// Module Name: ALU
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


module ALU(
        OP,
        A,
        B,
        F,
        ZF,
        CF,
        OF,
        SF,
        PF
    );
    // 32位ALU
    parameter LEN = 32;
    // 4位操作码
    input [3:0] OP;
    // 32位输入
    input [LEN-1:0] A;
    // 32位输入
    input [LEN-1:0] B;
    // 32位输出
    output [LEN-1:0] F;
    // 5位标志位
    output ZF, CF, OF, SF, PF;
    // 32位寄存器
    reg [LEN-1:0] F;
    // 5位标志位
    reg C, ZF, CF, OF, SF, PF;
    // 逻辑运算
    always@(*)
    begin
        C = 0;
        case(OP)
            // 4'b0000:加法
            4'b0000:
                begin {C, F} = A + B;
                end
            // 4'b0001:减法
            4'b0001:
                begin {C, F} = A - B;
                end
            // 4'b0010:与
            4'b0010:
                begin F = A & B;
                end
            // 4'b0011:或
            4'b0011:
                begin F = A | B;
                end
            // 4'b0100:异或
            4'b0100:
                begin F = A ^ B;
                end
            // 4'b0101:非或
            4'b0101:
                begin F = ~(A | B);
                end
            // 4'b0110:左移
            4'b0110:
                begin F = A << B;
                end
            // 4'b0111:右移
            4'b0111:
                begin F = A >> B;
                end
            // 4'b1000:逻辑右移
            endcase

        // flags
        ZF = F == 0;

        CF = C;

        OF = A[LEN-1] ^ B[LEN-1] ^ F[LEN-1] ^ C;

        SF = F[LEN-1];

        PF = ~^F;
    end
endmodule