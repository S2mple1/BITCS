`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: �ܺ���
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
    // 32λALU
    parameter LEN = 32;
    // 4λ������
    input [3:0] OP;
    // 32λ����
    input [LEN-1:0] A;
    // 32λ����
    input [LEN-1:0] B;
    // 32λ���
    output [LEN-1:0] F;
    // 5λ��־λ
    output ZF, CF, OF, SF, PF;
    // 32λ�Ĵ���
    reg [LEN-1:0] F;
    // 5λ��־λ
    reg C, ZF, CF, OF, SF, PF;
    // �߼�����
    always@(*)
    begin
        C = 0;
        case(OP)
            // 4'b0000:�ӷ�
            4'b0000:
                begin {C, F} = A + B;
                end
            // 4'b0001:����
            4'b0001:
                begin {C, F} = A - B;
                end
            // 4'b0010:��
            4'b0010:
                begin F = A & B;
                end
            // 4'b0011:��
            4'b0011:
                begin F = A | B;
                end
            // 4'b0100:���
            4'b0100:
                begin F = A ^ B;
                end
            // 4'b0101:�ǻ�
            4'b0101:
                begin F = ~(A | B);
                end
            // 4'b0110:����
            4'b0110:
                begin F = A << B;
                end
            // 4'b0111:����
            4'b0111:
                begin F = A >> B;
                end
            // 4'b1000:�߼�����
            endcase

        // flags
        ZF = F == 0;

        CF = C;

        OF = A[LEN-1] ^ B[LEN-1] ^ F[LEN-1] ^ C;

        SF = F[LEN-1];

        PF = ~^F;
    end
endmodule