#include "instruction.h"
#include <iostream>

using std::cout;

int main()
{
	Instruction in;
	int opc = 28;
	bool pass = true;
	in.VALUE = 0;
	in.setOpCode(opc);
	in.setOpda(31);
	in.setOpdb(19);
	in.setStoVal(23);
	in.setFlagA(1);
	in.setFlagB(0);
		
	pass &= (opc == in.getOpCode());
	pass &= (31 == in.getOpda());
	pass &= (19 == in.getOpdb());
	pass &= (23 == in.getStoVal());
	pass &= (1 == in.getFlagA());
	pass &= (0 == in.getFlagB());

	in.VALUE = 0;
	in.setOpCode(17);
	in.setOpda(27);
	in.setOpdbAlt(987321);
	
	pass &= (17 == in.getOpCode());
	pass &= (27 == in.getOpda());
	pass &= (987321 == in.getOpdbAlt());

	in.VALUE = 0;
	in.setOpCode(27);
	in.setOpda(19);
	in.setOpdb(31);
	in.setJumpVal(34476);
	in.setFlagA(1);

	pass &= (27 == in.getOpCode());
	pass &= (19 == in.getOpda());
	pass &= (31 == in.getOpdb());
	pass &= (34476 == in.getJumpVal());
	pass &= (1 == in.getFlagA());


	if(!pass)
		return 1;

	return 0;
}
