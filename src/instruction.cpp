#include "instruction.h"

Instruction::Instruction()
{}

Instruction::Instruction(int ival)
{
	VALUE = ival;
}

int Instruction::getOpCode()
{
	return (VALUE & OPCODE) >> 27;
}

void Instruction::setOpCode(int op)
{
	VALUE = ((op << 27) | (VALUE & (~OPCODE)));
}

int Instruction::getOpda()
{
	return (VALUE & H_OPDA) >> 22;
}

void Instruction::setOpda(int opda)
{
	VALUE = ((opda << 22) | (VALUE & (~H_OPDA)));
}

int Instruction::getOpdb()
{
	return (VALUE & H_OPDB) >> 17;
}

void Instruction::setOpdb(int opdb)
{
	VALUE = ((opdb << 17) | (VALUE & (~H_OPDB)));
}

int Instruction::getOpdbAlt()
{
	return (VALUE & T_OPDB) >> 2;
}

void Instruction::setOpdbAlt(int opdb)
{
	VALUE = ((opdb << 2) | (VALUE & (~T_OPDB)));
}

int Instruction::getStoVal()
{
	return (VALUE & H_STO) >> 12;
}

void Instruction::setStoVal(int sto)
{
	VALUE = ((sto << 12) | (VALUE & (~H_STO)));
}

int Instruction::getFlagB()
{
	return (VALUE & H_FA) >> 1;
}


void Instruction::setFlagB(int fa)
{
	VALUE = ((fa << 1) | (VALUE & (~H_FA)));
}

int Instruction::getFlagA()
{
	return (VALUE & H_FB);
}

void Instruction::setFlagA(int fb)
{
	VALUE = (fb | (VALUE & (~H_FB)));
}

int Instruction::getJumpVal()
{
	return (VALUE & LABEL_GET) >> 1;
}

void Instruction::setJumpVal(int jval)
{
	VALUE = ((jval << 1) | (VALUE & (~LABEL_GET)));
}

void Instruction::print()
{
	switch(getOpCode())
	{
		case ADD: cout << "ADD ";
			cout << getOpda() << " " << getOpdb() << " " << getJumpVal(); break;
		case SUB: cout << "SUB ";
			cout << getOpda() << " " << getOpdb() << " " << getJumpVal(); break;
		case MUL: cout << "MUL ";
			cout << getOpda() << " " << getOpdb() << " " << getJumpVal(); break;
		case DIV: cout << "DIV ";
			cout << getOpda() << " " << getOpdb() << " " << getJumpVal(); break;
		case BEQ: cout << "BEQ ";
			cout << getOpda() << " " << getOpdb() << " " << getJumpVal(); break;
		case BNE: cout << "BNE ";
			cout << getOpda() << " " << getOpdb() << " " << getJumpVal(); break;
		case BLT: cout << "BLT ";
			cout << getOpda() << " " << getOpdb() << " " << getJumpVal(); break;
		case BGT: cout << "BGT ";
			cout << getOpda() << " " << getOpdb() << " " << getJumpVal(); break;
		case LI:  cout << "LI " << getOpda() << " " << getOpdbAlt(); break;
		case SR:
				  cout << "SR " << getOpda() << " " << getOpdb(); break;
		case LR:
				  cout << "LR " << getOpda() << " " << getOpdb(); break;
		case PRINT:
				  cout << "PRINT " << getOpda(); break;
		case HALT:
				  cout << "HALT"; break;

		default: cout << "OTHER";
	}

	cout << "\n";
}
