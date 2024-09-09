`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: BIT
// Engineer: �ܺ���
// 
// Create Date: 2024/06/05 15:34:58
// Design Name: 
// Module Name: ALUsim
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



module ALUsim;

// �������������Ĵ�������
reg reset;                 // ��λ�ź�
reg [31:0] in_one, in_two; // 32λ���������
reg [10:0] operator;       // 11λ�������ź�
reg rounding;              // ���������־
wire [31:0] out;           // 32λ������
wire of, zf, cf, pf, sf;   // ��־: ������㡢��λ����żУ�顢����

// ʵ����ALUģ��
ALU unit(            
    .reset(reset),
    .in_one(in_one),
    .in_two(in_two),
    .operator(operator),
    .rounding(rounding),
    .out(out),
    .of(of),
    .zf(zf),
    .cf(cf),
    .pf(pf),
    .sf(sf)
);

initial begin
    // ��ʼ��λ����
    #10 
        reset = 1;
    #10 
        reset = 0;
        in_one = 32'd3;   // ���õ�һ�����������Ϊ3
        in_two = 32'd2;   // ���õڶ������������Ϊ2
        rounding = 1'b1;  // ������������

        // ����һϵ�в�����ֵ
        for(operator = 11'b00000100000; operator < 11'b00000100111; operator = operator + 1)
            #20; // ÿ���������ȴ�20��ʱ�䵥λ

    #20 
        operator = 11'b00000000000; // ������������Ϊ�ض�ֵ
    #20 
        operator = 11'b00000000010; // ������������Ϊ��һ���ض�ֵ
    #20 
        operator = 11'b00000000011; // ������������Ϊ��һ���ض�ֵ

    // �ٴθ�λ
    #10 
        reset = 1;
    #10 
        reset = 0;
        in_one = -32'd1;  // ���õ�һ�����������Ϊ-1
        in_two = 32'd2;   // ���õڶ������������Ϊ2
        rounding = 1'b0;  // ������������
        
        // �ٴβ���һϵ�в�����ֵ
        for(operator = 11'b00000100000 ; operator < 11'b00000100111; operator = operator + 1)
            #20; // ÿ���������ȴ�20��ʱ�䵥λ

    #20 
        operator = 11'b00000000000; // ������������Ϊ�ض�ֵ
    #20 
        operator = 11'b00000000010; // ������������Ϊ��һ���ض�ֵ
    #20 
        operator = 11'b00000000011; // ������������Ϊ��һ���ض�ֵ
    
    // ��100��ʱ�䵥λ���������
    #100 
        $finish;
end

initial
    // ���ӱ仯����ÿ��ʱ�䲽��ʾֵ
    $monitor($time,,,
        "reset=%b in_one=%b in_two=%b operator=%b rounding=%b out=%b of=%b zf=%b cf=%b pf=%b sf=%b",
        reset, in_one, in_two, operator, rounding, out, of, zf, cf, pf, sf);

endmodule
