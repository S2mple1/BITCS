`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: BIT
// Engineer: 周豪捷
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

// 声明输入和输出寄存器和线
reg reset;                 // 复位信号
reg [31:0] in_one, in_two; // 32位输入操作数
reg [10:0] operator;       // 11位操作符信号
reg rounding;              // 四舍五入标志
wire [31:0] out;           // 32位输出结果
wire of, zf, cf, pf, sf;   // 标志: 溢出、零、进位、奇偶校验、符号

// 实例化ALU模块
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
    // 初始复位序列
    #10 
        reset = 1;
    #10 
        reset = 0;
        in_one = 32'd3;   // 设置第一个输入操作数为3
        in_two = 32'd2;   // 设置第二个输入操作数为2
        rounding = 1'b1;  // 启用四舍五入

        // 测试一系列操作符值
        for(operator = 11'b00000100000; operator < 11'b00000100111; operator = operator + 1)
            #20; // 每个操作符等待20个时间单位

    #20 
        operator = 11'b00000000000; // 将操作符设置为特定值
    #20 
        operator = 11'b00000000010; // 将操作符设置为另一个特定值
    #20 
        operator = 11'b00000000011; // 将操作符设置为再一个特定值

    // 再次复位
    #10 
        reset = 1;
    #10 
        reset = 0;
        in_one = -32'd1;  // 设置第一个输入操作数为-1
        in_two = 32'd2;   // 设置第二个输入操作数为2
        rounding = 1'b0;  // 禁用四舍五入
        
        // 再次测试一系列操作符值
        for(operator = 11'b00000100000 ; operator < 11'b00000100111; operator = operator + 1)
            #20; // 每个操作符等待20个时间单位

    #20 
        operator = 11'b00000000000; // 将操作符设置为特定值
    #20 
        operator = 11'b00000000010; // 将操作符设置为另一个特定值
    #20 
        operator = 11'b00000000011; // 将操作符设置为再一个特定值
    
    // 在100个时间单位后结束仿真
    #100 
        $finish;
end

initial
    // 监视变化并在每个时间步显示值
    $monitor($time,,,
        "reset=%b in_one=%b in_two=%b operator=%b rounding=%b out=%b of=%b zf=%b cf=%b pf=%b sf=%b",
        reset, in_one, in_two, operator, rounding, out, of, zf, cf, pf, sf);

endmodule
