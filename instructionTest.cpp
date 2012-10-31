#include "instruction.h"
#include <iostream>

using std::cout;

int main()
{
	Instruction in;
	int opc = 28;
	in.VALUE = 0;
	in.setOpCode(opc);
	in.setOpda(31);
	in.setOpdb(19);
	in.setStoVal(23);
	in.setFlagA(1);
	in.setFlagB(0);
	cout << in.VALUE << "\n";
	cout << opc << " = " << in.getOpCode() << "\n";
	
	in.VALUE = 0;
	in.setOpCode(17);
	in.setOpdbAlt(987321);
	cout << in.getOpCode() << " 987321= " << in.getOpdbAlt() << "\n";

	return 0;
}
