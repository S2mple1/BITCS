`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/12/24 17:39:50
// Design Name: 
// Module Name: mine
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


module mine(
 reset, in0, in1, op, cut, out, overflow, zero, carryout, parity, signal
    );
    input reset;               //���ڳ�ʼ������
    input[31:0] in0,in1;       //������
    input[10:0] op;            //���������
    input cut;
    output[31:0] out;          //������
    output overflow,zero,carryout,parity,signal;  //����ж�λ����ֵ�ж�λ������λ�ж�λ����żУ��λ������λ
    reg[31:0] out;             //����Ϊ�Ĵ������ͱ���
    reg overflow,zero,carryout,parity,signal;//����Ϊ�Ĵ������ͱ���
always@(*)                     //ʹ��always����������
begin
     if(reset)           //�ж�resetֵ��Ϊ1���г�ʼ����Ϊ0����ALU����
         begin
          out=0;
          overflow=0;
          zero=0;
          carryout=0;
          parity=0;
          signal=0;
         end
     else
         alutask( in0, in1, op, cut, out, overflow, zero, carryout, parity, signal);      //�Ѿ������㹦��ģ���װ��һ������
end
task alutask;                  //����������
   input[31:0] in0,in1;       
   input[10:0] op;   
   input cut;         
   output[31:0] out;         
   output overflow,zero,carryout,parity,signal;
   reg[31:0] out;
   reg tmp,pmt,overflow,zero,carryout,parity,signal;
   
begin
            overflow=0;            //ÿ�ν�������ǰ����־λ��0
            carryout=0;
            zero=0;
            parity=0;
            signal=0;
            
            case( op )
            11'b00000100000://�з������ӷ� 
                            begin
                            {tmp,out}=in0+in1;
                            end
            11'b00000100001://�з���������
                            begin
                            {tmp,out}=in0-in1;
                            end
            11'b00000100010: out=in0&in1;//��λ��
            11'b00000100011: out=in0|in1;//��λ��
            11'b00000100100: out=in0^in1;//���
            11'b00000100101: out=~(in0|in1);//���
            11'b00000100110: out=( $signed(in0)==$signed(in1) )? 1:0;//�з������������
            11'b00000100111: out=( $signed(in0)>$signed(in1) )? 1:0;//�з������Ƚ�����

            11'b00000000000: out=in0<<in1;
            11'b00000000010:                             
                            begin
                            out=in0>>in1;
                            case( cut )
                            1'b0://����
                            out[0]=out[0];             
                            1'b1://����1
                            out[0]=1;
                            endcase
                            end
            11'b00000000011: out=in0>>>in1;

            endcase
            zero=out==0;          //zeroͨ��ֱ���ж�out�Ƿ�Ϊ0
            carryout=tmp;
            overflow=in0[31]^in1[31]^out[31]^tmp;
            signal=out[31];
            parity=~^out;
end
endtask
endmodule
