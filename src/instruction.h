#ifndef SOMN_INSTRUCTIONS_H
#define SOMN_INSTRUCTIONS_H

#include <iostream>

using std::cout;

//Command opcodes
#define OPCODE 0xF8000000
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define SR 4
#define LR 5
#define PRINT 6
#define LI 7
#define JR 8
#define JMP 9
#define MOV 10
#define BEQ 11
#define BNE 12
#define BLT 13
#define BGT 14
#define RET 15
#define JAL 16
#define HALT 17



//Three operand bitmasks
#define H_OPDA 0x7C00000
#define H_OPDB 0x3E0000
#define H_STO  0x1F000
#define H_FA   0x2
#define H_FB   0x1

//for labels
#define LABEL_GET 0x1FFFE

//For two operand commands, the second longer operand:
#define T_OPDB 0x3FFFFC

class Instruction
{
	public:
		Instruction();
		Instruction(int ival);

		int getOpCode();
		void setOpCode(int op);

		int getOpda();
		void setOpda(int opda);

		int getOpdb();
		void setOpdb(int opdb);

		int getOpdbAlt();
		void setOpdbAlt(int opdbA);

		int getStoVal();
		void setStoVal(int sto);

		int getFlagA();
		void setFlagA(int flaga);

		int getFlagB();
		void setFlagB(int optb);

		int getJumpVal();
		void setJumpVal(int jval);

		int VALUE;

		void print();
};

#endif
