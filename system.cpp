#include "system.h"

System::System()
{
	IC = 0;
	registers.resize(32);
	memory.resize(MAXMEMSIZE);
}

void System::Run()
{
	int cur;
	instr i;


	while(i.h.op != HALT)
	{ 
		i.ival = instructions[IC];
		DSTAT(i.h.op << " " << IC);
		switch(i.h.op)
		{
			case ADD:
				add(i.h.opda, i.h.opdb, i.h.sto);
				break;
			case SUB:
				subtract(i.h.opda, i.h.opdb, i.h.sto);
				break;
			case MUL:
				multiply(i.h.opda, i.h.opdb, i.h.sto);
				break;
			case DIV:
				divide(i.h.opda, i.h.opdb, i.h.sto);
				break;
			
			case PRINTN:
				print(i.t.opda);
				break;

			case LI:
				registers[i.t.opda] = i.t.opdb;
				break;
			case JR:
				IC = registers[i.t.opda] - 1;
				break;
			case JMP:
				IC = i.t.opdb;
				break;
			case MOV:
				registers[i.t.opdb] = registers[i.t.opda];
				break;
			case BEQ:
				if(registers[i.h.opda] == registers[i.h.opdb])
					IC = registers[i.h.sto] - 1;
				break;
			case BNE:
				if(registers[i.h.opda] != registers[i.h.opdb])
					IC = registers[i.h.sto] - 1;
				break;
			case BGT:
				if(registers[i.h.opda] > registers[i.h.opdb])
					IC = registers[i.h.sto] - 1;
				break;
			case BLT:
				if(registers[i.h.opda] < registers[i.h.opdb])
					IC = registers[i.h.sto] - 1;
				break;

		}
		IC++;
	}	
}

void System::add(int a, int b, int sto)
{
	registers[sto] = registers[a] + registers[b];
}

void System::subtract(int a, int b, int sto)
{
	registers[sto] = registers[a] - registers[b];
}

void System::multiply(int a, int b, int sto)
{
	registers[sto] = registers[a] * registers[b];
}

void System::divide(int a, int b, int sto)
{
	registers[sto] = registers[a] / registers[b];
}

void System::print(int reg)
{
	cout << registers[reg] << "\n";
}

vector<string> splitString(string s, char delim)
{
	DSTAT("splitting string");
	vector<string> ret;
	string temp = "";
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] != delim)
			temp += s[i];
		else if(temp != "")
		{
			ret.push_back(temp);
			temp = "";
		}
	}
	if(temp != "")
		ret.push_back(temp);
	DSTAT("String Split");
	return ret;
}

void System::Parse(char *filename)
{
	DSTAT("Parsing...\n");
	instr it;
	ifstream asmf(filename);
	vector<string> parts;
	string line;
	instructions.resize(0);
	while(asmf.good())
	{
		getline(asmf, line);
		DSTAT(line);
		parts = splitString(line, ' ');
		DSTAT(parts.size());
		if(parts[0] == "LI")
		{
			it.t.op = LI;
			it.t.opda = atoi(parts[1].c_str());
			it.t.opdb = atoi(parts[2].c_str());
		}
		else if(parts[0] == "ADD")
		{
			it.h.op = ADD;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			it.h.sto = atoi(parts[3].c_str());	
		}
		else if(parts[0] == "SUB")
		{
			it.h.op = SUB;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			it.h.sto = atoi(parts[3].c_str());	

		}
		else if(parts[0] == "MUL")
		{
			it.h.op = MUL;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			it.h.sto = atoi(parts[3].c_str());	
		}
		else if(parts[0] == "DIV")
		{
			it.h.op = DIV;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			it.h.sto = atoi(parts[3].c_str());	
		}
		else if(parts[0] == "MOV")
		{
			it.t.op = MOV;
			it.t.opda = atoi(parts[1].c_str());
			it.t.opdb = atoi(parts[2].c_str());
		}
		else if(parts[0] == "PRINTN")
		{
			it.t.op = PRINTN;
			it.t.opda = atoi(parts[1].c_str());
		}
		else if(parts[0] == "JR")
		{
			it.t.op = JR;
			it.t.opda = atoi(parts[1].c_str());
		}
		else if(parts[0] == "JMP")
		{
			cout << "JMP NOT YET IMPLEMENTED.\n";
		}
		else if(parts[0] == "BEQ")
		{
			it.h.op = BEQ;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			it.h.sto = atoi(parts[3].c_str());
		}
		else if(parts[0] == "BNE")
		{
			it.h.op = BNE;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			it.h.sto = atoi(parts[3].c_str());
		}
		else if(parts[0] == "BGT")
		{
			it.h.op = BGT;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			it.h.sto = atoi(parts[3].c_str());
		}
		else if(parts[0] == "BLT")
		{
			it.h.op = BLT;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			it.h.sto = atoi(parts[3].c_str());
		}
		else if(parts[0] == "HALT")
		{
			it.h.op = HALT;
		}
		else
		{
			continue;
		}
		instructions.push_back(it.ival);
	}
	DSTAT("Parse Finished.");
}
