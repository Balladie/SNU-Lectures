
///////////////////////////////////////////////////////////////////////////
// MODULE: CPU for TSC microcomputer: cpu.v
// Author: SNU HPCS
// CPU-ALU part implemented by: GangIn Park, MyeongJu Kim
// Description: CPU module

// DEFINITIONS do not touch definition and 
`define WORD_SIZE 16    // data and address word size
`define MEMORY_SIZE 64 
`define PC_SIZE 8 
// INCLUDE files
`include "opcodes.v"    // "opcode.v" consists of "define" statements for
                        // the opcodes and function codes for all instructions

// MODULE DECLARATION
module cpu (
  input reset_cpu,                // reset signal for CPU. active-high(reset at 1)
  input clk,                          // clock signal
  input cpu_enable,              //enables CPU too move PC, and write register
  input wwd_enable,             //enables wwd. if unasserted then wwd operation
				  //should not assign register value to output_port
  input [1:0] register_selection , // selects which register to show on output_port. It should only work when wwd is disabled
  //output reg[`WORD_SIZE-1:0] num_inst,   // number of instruction during execution. !!!!!!! IMPORTANT!!! DISABLE!! this port when programming FPGA
				    // You should enable num_inst port only for SIMULATION purposes.
  output [`WORD_SIZE-1:0] output_port,   // this will be used to show values in registers in case of WWD or register_selection
  output [7:0] PC_below8bit                  // lower 8-bit of PC for LED output on output_logic.v. You need to assign lower 8bit of current PC to this port
);
  ///////////////////////////////insturction memory//////////////////////////////////
// Do not touch this part. Otherwise, your CPU will not work properly according to the tsc-ISA
   reg [`WORD_SIZE-1:0] memory [0:`MEMORY_SIZE-1]; //memory where instruction is saved
	always@(reset_cpu) begin   // paste this at initialing memory in cpu.v
	 if(reset_cpu == 1'b1) begin
         memory[0] <= 16'h6000; // LHI $0, 0x0
         memory[1] <= 16'h430F; // ADI $3, $0, 0xF
         memory[2] <= 16'h6201; // LHI $2, 0x1
         memory[3] <= 16'h4AF0; // ADI $2, $2, 0xF0
         memory[4] <= 16'h610F; // LHI $1, 0xF
         memory[5] <= 16'h60F0; // LHI $0, 0xF0
         memory[6] <= 16'hF01C; // WWD $0
         memory[7] <= 16'hF41C; // WWD $1
         memory[8] <= 16'h9013; // JMP 0x13
         memory[9] <= 16'h6000; // LHI $0, 0x0
         memory[10] <= 16'h6101; // LHI $1, 0x1
         memory[11] <= 16'h45FF; // ADI $1, $1, 0xFF
         memory[12] <= 16'h42FF; // ADI $2, $0, 0xFF 
         memory[13] <= 16'hF41C; // WWD $1
         memory[14] <= 16'hF81C; // WWD $2
         memory[15] <= 16'h9010; // JMP 0x10
         memory[16] <= 16'hF5C0; // ADD $3, $1, $1
         memory[17] <= 16'hFFC0; // ADD $3, $3, $3
         memory[18] <= 16'h9021; // JMP 0x21
         memory[19] <= 16'hF81C; // WWD $2
         memory[20] <= 16'hFC1C; // WWD $3
         memory[21] <= 16'hF140; // ADD $1, $0, $1
         memory[22] <= 16'hFBC0; // ADD $3, $2, $3
         memory[23] <= 16'hF7C0; // ADD $3, $1, $3
         memory[24] <= 16'hFC1C; // WWD $3
         memory[25] <= 16'h9009; // JMP 0x9
         memory[26] <= 16'hF000; // ADD $0, $0, $0
         memory[27] <= 16'hF01C; // WWD $0
         memory[28] <= 16'h901D; // JMP 0x1D
         memory[29] <= 16'h901E; // JMP 0x1E
         memory[30] <= 16'h6202; // LHI $2, 0x2
         memory[31] <= 16'h4AFF; // ADI $2, $2, 0xFF
         memory[32] <= 16'h902C; // JMP 0x2C
         memory[33] <= 16'hFC1C; // WWD $3
         memory[34] <= 16'h6101; // LHI $1, 0x1
         memory[35] <= 16'h4220; // ADI $2, $0, 0x20
         memory[36] <= 16'h4303; // ADI $3, $0, 0x3
         memory[37] <= 16'h6055; // LHI $0, 0x55
         memory[38] <= 16'h4055; // ADI $0, $0, 0x55
         memory[39] <= 16'hF140; // ADD $1, $0, $1
         memory[40] <= 16'hF680; // ADD $2, $1, $2
         memory[41] <= 16'hFBC0; // ADD $3, $2, $3
         memory[42] <= 16'hFC1C; // WWD $3
         memory[43] <= 16'h901A; // JMP 0x1A
         memory[44] <= 16'h4A92; // ADI $2, $2, 0x92
         memory[45] <= 16'hF81C; // WWD $2
	 end
	 end
//////////////////////////////////////////////////////////////////////////////////////////

	reg signed [`WORD_SIZE-1:0] register [0:4];
	reg [`WORD_SIZE-1:0] pc;

	always@(posedge clk) begin
		if (reset_cpu == 1'b1) begin    
			register[0] = 16'sb0;
			register[1] = 16'sb0;
			register[2] = 16'sb0;
			register[3] = 16'sb0;
			register[4] = 16'sb0;
			pc = 0;
		end
		else if (cpu_enable==1'b1) begin			
			case (memory[pc][15:12])
				4'b1111: begin
					case (memory[pc][5:0])
						`FUNC_ADD: begin
							register[memory[pc][7:6]] = register[memory[pc][11:10]] + register[memory[pc][9:8]];
						end
						
						`FUNC_WWD: begin
							register[4] = register[memory[pc][11:10]];
						end
					endcase
					
					pc = pc + 1;
				end
				
				`OPCODE_ADI: begin
					register[memory[pc][9:8]] = register[memory[pc][11:10]] + $signed(memory[pc][7:0]);
					
					pc = pc + 1;
				end
				
				`OPCODE_LHI: begin
					register[memory[pc][9:8]] = {memory[pc][7:0], 8'b00000000};

					pc = pc + 1;
				end
				
				`OPCODE_JMP: begin
					pc = {pc[15:12], memory[pc][11:0]};
				end
				
			endcase
		end
	end
	
	assign PC_below8bit = pc[`PC_SIZE-1:0];
	assign output_port = wwd_enable ? register[4] : register[register_selection];
	
endmodule
