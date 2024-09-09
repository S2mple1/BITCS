`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Beijing Institude of Technology
// Engineer: 周豪捷
//
// Create Date: 2024/6/21 20:49:57
// Design Name: 
// Module Name: BrUnit
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

//  branch unit
module BrUnit(
        input [11:0] br_offset,
        input [19:0] jal_offset,
        input [31:0] rs1_data,
        input [31:0] rs2_data,
        input [2:0] branch,
        output reg jump,
        output reg [31:0] offset
    );
    //  active branch offset
    reg [31:0] act_br_offset, act_jal_offset;

    always @(*)
    begin
        //  active branch offset
        act_br_offset[12:0] = {br_offset[11], br_offset[0], br_offset[10:1], 1'b0};
        if (br_offset[11] == 1)//  sign extension
            begin
                act_br_offset[31:13] = 19'b1111_11111_11111_11111;
            end
        else //  zero extension
            begin
                act_br_offset[31:13] = 19'b0;
            end
        //  active jal offset
        act_jal_offset[20:0] = {jal_offset[19], jal_offset[7:0], jal_offset[8], jal_offset[18:9], 1'b0};
        //  sign extension
        if (jal_offset[19] == 1)
            begin
                act_jal_offset[31:21] = 11'b1_11111_11111;
            end
        else
            //  zero extension
            begin
                act_jal_offset[31:21] = 11'b0;
            end
    end

    always @(*)
    begin
        //  branch unit
        case (branch)
            //  beq
            3'b000:
                begin
                    jump = 0;
                end

            //  blt
            3'b011:
                begin
                    offset = act_br_offset;
                if ((rs1_data[31] == 0 && rs2_data[31] == 1) || (rs1_data[31] == rs2_data[31] && rs1_data >= rs2_data))
                    begin
                        jump = 0;
                    end
                else
                    begin
                        jump = 1;
                    end
                end

            //  bge
            3'b100:
            begin
                offset = act_br_offset;
                if ((rs1_data[31] == 0 && rs2_data[31] == 1) || (rs1_data[31] == rs2_data[31] && rs1_data >= rs2_data))
                    begin
                        jump = 1;
                    end
                else
                    begin
                        jump = 0;
                    end
            end

            //  beq
            3'b101:
                begin
                    offset = act_br_offset;
                if (rs1_data == rs2_data)
                    begin
                        jump = 1;
                    end
                else
                    begin
                        jump = 0;
                    end
                end

            //  bne
            3'b110:
                begin
                    offset = act_br_offset;
                if (rs1_data != rs2_data)
                    begin
                        jump = 1;
                    end
                else
                    begin
                        jump = 0;
                    end
                end

            //  jal
            3'b111:
                begin
                    //  jump to the target address
                    offset = act_jal_offset;
                    jump = 1;
                end
        endcase
    end

endmodule

