#include "instruction.h"
#include <iostream>

using std::cout;

int main()
{
	Instruction in;
	in.VALUE = 0;
	in.setOpCode(28);
	in.setOpda(31);
	in.setOpdb(19);
	in.setStoVal(23);
	in.setFlagA(1);
	in.setFlagB(0);
	cout << in.VALUE << "\n";
	std::cin.ignore();
	cout << in.getOpCode() << " " << in.getOpda() << " " << in.getOpdb() << " " << in.getStoVal() << " " << in.getFlagA() << " " << in.getFlagB() << "\n";
	return 0;
}
