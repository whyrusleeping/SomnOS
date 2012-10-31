#ifndef SOMN_INSTRUCTIONS_H
#define SOMN_INSTRUCTIONS_H

#include "instrDefs.h"

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

		int VALUE;
};

#endif
