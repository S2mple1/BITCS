`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: BIT
// Engineer: �ܺ���
// 
// Create Date: 2024/06/05 15:32:37
// Design Name: 
// Module Name: ALU
// Project Name: 32bit ALU
// Target Devices: 
// Tool Versions: Vivado 2019.2
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
    reset, in_one, in_two, operator, rounding, out, of, zf, cf, pf, sf
    );
    input reset;                        //  ��ʼ������
    input[31:0] in_one, in_two;         //  ������
    input[10:0] operator;               //  ���������
    input rounding;                     //  �������
    output[31:0] out;                   //  ������
    output of, zf, cf, pf, sf;          //  �����־�����־����λ/��λ��־����ż��־������λ
    reg[31:0] out;                       
    reg of,zf,cf,pf,sf;
    
always@(*)
                     
begin
     if(reset)
        //  reset = 1�����г�ʼ��
        begin
            out=0;
            of=0;
            zf=0;
            cf=0;
            pf=0;
            sf=0;
        end
     else
        //  reset = 0����װALU����
         alutask( in_one, in_two, operator, rounding, out, of, zf, cf, pf, sf);      
end

//  ALU������
task alutask;                  
    input[31:0] in_one, in_two;       
    input[10:0] operator;   
    input rounding;         
    output[31:0] out;         
    output of, zf, cf, pf, sf;
    reg[31:0] out;
    reg temp, pmt, of, zf, cf, pf, sf;
   
    begin
        //  ��������ǰ�����б�־λ��0
        of=0;            
        cf=0;
        zf=0;
        pf=0;
        sf=0;
        
        case( operator )
            //  �з������ļӷ�����
            11'b00000100000:
                            begin
                                {temp,out} = in_one + in_two;
                            end
            //  �з������ļ�������
            11'b00000100001:
                            begin
                                {temp,out } = in_one - in_two;
                            end
            //  ��λ���
            11'b00000100101: 
                out = ~(in_one | in_two);
            //  ��λ��
            11'b00000100010: 
                out = in_one & in_two;
            //  ��λ��
            11'b00000100011: 
                out = in_one | in_two;
            //  ��λ���
            11'b00000100100: 
                out = in_one ^ in_two;
            //  �з���������ȱȽ�����
            11'b00000100110: 
                out = ( $signed(in_one) == $signed(in_two) )? 1:0;
            //  �з������Ĵ�С�Ƚ�����
            11'b00000100111: 
                out = ( $signed(in_one) > $signed(in_two) )? 1:0;
            //  ��������
            11'b00000000000: 
                out = in_one << in_two;
            //  ��������
            11'b00000000010:                             
                            begin
                            out = in_one >> in_two;
                            //  �����ж�
                            case( rounding )
                                //  ����ԭֵ
                                1'b0:
                                    out[0]=out[0];
                                //  ��1           
                                1'b1:
                                    out[0]=1;
                            endcase
                            end
            //  �߼�����
            11'b00000000011: 
                out = in_one >>> in_two;
    
        endcase
        
        if(out == 0)
            zf = 1;
        else
            zf = 0;
        cf = temp;
        of = in_one[31] ^ in_two[31] ^ out[31] ^ temp;
        sf = out[31];
        pf = ~^out;
        
    end
endtask
endmodule
