`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: BIT
// Engineer: 周豪捷
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
    input reset;                        //  初始化置零
    input[31:0] in_one, in_two;         //  操作数
    input[10:0] operator;               //  操作运算符
    input rounding;                     //  舍入控制
    output[31:0] out;                   //  运算结果
    output of, zf, cf, pf, sf;          //  溢出标志、零标志、进位/借位标志、奇偶标志、符号位
    reg[31:0] out;                       
    reg of,zf,cf,pf,sf;
    
always@(*)
                     
begin
     if(reset)
        //  reset = 1，进行初始化
        begin
            out=0;
            of=0;
            zf=0;
            cf=0;
            pf=0;
            sf=0;
        end
     else
        //  reset = 0，封装ALU任务
         alutask( in_one, in_two, operator, rounding, out, of, zf, cf, pf, sf);      
end

//  ALU任务定义
task alutask;                  
    input[31:0] in_one, in_two;       
    input[10:0] operator;   
    input rounding;         
    output[31:0] out;         
    output of, zf, cf, pf, sf;
    reg[31:0] out;
    reg temp, pmt, of, zf, cf, pf, sf;
   
    begin
        //  进行运算前将所有标志位清0
        of=0;            
        cf=0;
        zf=0;
        pf=0;
        sf=0;
        
        case( operator )
            //  有符号数的加法运算
            11'b00000100000:
                            begin
                                {temp,out} = in_one + in_two;
                            end
            //  有符号数的减法运算
            11'b00000100001:
                            begin
                                {temp,out } = in_one - in_two;
                            end
            //  按位或非
            11'b00000100101: 
                out = ~(in_one | in_two);
            //  按位与
            11'b00000100010: 
                out = in_one & in_two;
            //  按位或
            11'b00000100011: 
                out = in_one | in_two;
            //  按位异或
            11'b00000100100: 
                out = in_one ^ in_two;
            //  有符号数的相等比较运算
            11'b00000100110: 
                out = ( $signed(in_one) == $signed(in_two) )? 1:0;
            //  有符号数的大小比较运算
            11'b00000100111: 
                out = ( $signed(in_one) > $signed(in_two) )? 1:0;
            //  算术左移
            11'b00000000000: 
                out = in_one << in_two;
            //  算术右移
            11'b00000000010:                             
                            begin
                            out = in_one >> in_two;
                            //  舍入判断
                            case( rounding )
                                //  保持原值
                                1'b0:
                                    out[0]=out[0];
                                //  置1           
                                1'b1:
                                    out[0]=1;
                            endcase
                            end
            //  逻辑右移
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
