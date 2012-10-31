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

int Instruction::getStoVal()
{
	return (VALUE & H_STO) >> 12;
}

void Instruction::setStoVal(int sto)
{
	VALUE = ((sto << 12) | (VALUE & (~H_STO)));
}

int Instruction::getFlagA()
{
	return (VALUE & H_FA) >> 11;
}

void Instruction::setFlagA(int fa)
{
	VALUE = ((fa << 11) | (VALUE & (~H_FA)));
}

int Instruction::getFlagB()
{
	return (VALUE & H_FB) >> 10;
}

void Instruction::setFlagB(int fb)
{
	VALUE = ((fb << 10) | (VALUE & (~H_FB)));
}
