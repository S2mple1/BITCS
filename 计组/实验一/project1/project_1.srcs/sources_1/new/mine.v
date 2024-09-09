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
    input reset;               //用于初始化置零
    input[31:0] in0,in1;       //操作数
    input[10:0] op;            //操作运算符
    input cut;
    output[31:0] out;          //运算结果
    output overflow,zero,carryout,parity,signal;  //溢出判断位、零值判断位、进借位判断位、奇偶校验位、符号位
    reg[31:0] out;             //标明为寄存器类型变量
    reg overflow,zero,carryout,parity,signal;//标明为寄存器类型变量
always@(*)                     //使用always语句进行运算
begin
     if(reset)           //判断reset值，为1进行初始化，为0进行ALU运算
         begin
          out=0;
          overflow=0;
          zero=0;
          carryout=0;
          parity=0;
          signal=0;
         end
     else
         alutask( in0, in1, op, cut, out, overflow, zero, carryout, parity, signal);      //把具体运算功能模块封装成一个任务
end
task alutask;                  //运算任务定义
   input[31:0] in0,in1;       
   input[10:0] op;   
   input cut;         
   output[31:0] out;         
   output overflow,zero,carryout,parity,signal;
   reg[31:0] out;
   reg tmp,pmt,overflow,zero,carryout,parity,signal;
   
begin
            overflow=0;            //每次进行运算前，标志位置0
            carryout=0;
            zero=0;
            parity=0;
            signal=0;
            
            case( op )
            11'b00000100000://有符号数加法 
                            begin
                            {tmp,out}=in0+in1;
                            end
            11'b00000100001://有符号数减法
                            begin
                            {tmp,out}=in0-in1;
                            end
            11'b00000100010: out=in0&in1;//按位与
            11'b00000100011: out=in0|in1;//按位或
            11'b00000100100: out=in0^in1;//异或
            11'b00000100101: out=~(in0|in1);//或非
            11'b00000100110: out=( $signed(in0)==$signed(in1) )? 1:0;//有符号数相等运算
            11'b00000100111: out=( $signed(in0)>$signed(in1) )? 1:0;//有符号数比较运算

            11'b00000000000: out=in0<<in1;
            11'b00000000010:                             
                            begin
                            out=in0>>in1;
                            case( cut )
                            1'b0://恒舍
                            out[0]=out[0];             
                            1'b1://恒置1
                            out[0]=1;
                            endcase
                            end
            11'b00000000011: out=in0>>>in1;

            endcase
            zero=out==0;          //zero通过直接判断out是否为0
            carryout=tmp;
            overflow=in0[31]^in1[31]^out[31]^tmp;
            signal=out[31];
            parity=~^out;
end
endtask
endmodule
