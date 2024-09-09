`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/12/24 17:40:16
// Design Name: 
// Module Name: mine1
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


module mine1;
reg reset;           
reg [31:0] in0,in1;      
reg [10:0] op;  
reg cut;          
wire [31:0] out;         
wire overflow,zero,carryout,parity,signal;

mine unit(            //Ä£¿éÊµÀý»¯
    .reset(reset),
    .in0(in0),
    .in1(in1),
    .op(op),
    .cut(cut),
    .out(out),
    .overflow(overflow),
    .zero(zero),
    .carryout(carryout),
    .parity(parity),
    .signal(signal)
);
initial
begin
    #10 reset=1;
    #10 reset=0;in0=32'd3;in1=32'd2;cut=1'b1;
    for(op=11'b00000100000;op<11'b00000100111;op=op+1)
    #20;
    #20 op=11'b00000000000;
    #20 op=11'b00000000010;
    #20 op=11'b00000000011;
    
    #10 reset=1;
    #10 reset=0;in0=-32'd1;in1=32'd2;cut=1'b0;            
    for(op=11'b00000100000;op<11'b00000100111;op=op+1)
    #20;
    #20 op=11'b00000000000;
    #20 op=11'b00000000010;
    #20 op=11'b00000000011;
    
    #100 $finish;
end
initial
$monitor ($time,,,"reset=%b in0=%b in1=%b op=%b cut=%b out=%b overflow=%b zero=%b carryout=%b parity=%b signal=%b",
reset,in0,in1,op,cut,out,overflow,zero,carryout,parity,signal);
endmodule
