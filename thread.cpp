#include "thread.h"


Thread::Thread()
{
	registers.resize(32,0);
	instructions.resize(0);
	IC = 0;
	Alive = true;
	priority = 0;
}

Thread::Thread(char *filename)
{	
	registers.resize(32,0);
	instructions.resize(0);
	IC = 0;
	Alive = true;
	priority = 0;
	Parse(filename);
}

void Thread::Parse(char *filename)
{
	name = filename;
	DSTAT("Parsing...\n");
	instr it;
	ifstream asmf(filename);
	vector<string> parts;
	vector<string> lines;
	string line;
	instructions.resize(0);
	int labelCounter = 0;
	map<string, int> labels;
	while(asmf.good())
	{
		getline(asmf, line);
		lines.push_back(line);
		if(startsWith(line, "LAB"))
		{
			string tmpLab = line.substr(4);
			labels[tmpLab] = labelCounter;
		}
		else
			labelCounter++;
	}

	asmf.close();
	DSTAT("finished reading from file");

	for(int j = 0; j < lines.size(); j++)
	{
		parts = splitString(lines[j], ' ');
		DSTAT("parsing" << lines[j]);
		DSTAT(parts.size());
		if(parts[0] == "LI")
		{
			it.t.op = LI;

			if(parts[1][0] == 'r')
			{
				it.t.opda = atoi(&(parts[1].c_str()[1]));
			}
			else
			{
				cout << "Invalid Parameter to LI on line: " << j << "\n";
			}
						
			if(parts[2][0] == '#')
				it.t.opdb = atoi(&(parts[2].c_str()[1]));
			else
			{
				cout << "Invalid Parameter to LI on line: " << j << "\n";
				exit(1);
			}
		}
		else if(parts[0] == "LR")
		{
			it.t.op = LR;
			it.t.opda = atoi(parts[1].c_str());
			it.t.opdb = atoi(parts[2].c_str());
		}
		else if(parts[0] == "SR")
		{
			it.t.op = SR;
			it.t.opda = atoi(parts[1].c_str());
			it.t.opdb = atoi(parts[2].c_str());
		}
		else if(parts[0] == "ADD")
		{
			it.h.op = ADD;
			if(parts[1][0] == 'r')
			{
				it.t.opda = atoi(&(parts[1].c_str()[1]));
			}
			else
			{
				cout << "Invalid Parameter to ADD on line: " << j << "\n";
			}
			it.h.opdb = atoi(parts[2].c_str());
			if(parts[2][0] == 'r')
			{
				it.t.opdb = atoi(&(parts[2].c_str()[1]));
			}
			else
			{
				cout << "Invalid Parameter to ADD on line: " << j << "\n";
			}
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
		else if(parts[0] == "PRINT")
		{
			it.t.op = PRINT;
			it.t.opda = atoi(parts[1].c_str());
		}
		else if(parts[0] == "JR")
		{
			it.t.op = JR;
			it.t.opda = atoi(parts[1].c_str());
		}
		else if(parts[0] == "JMP")
		{
			it.t.op = JMP;
			if(isalpha(parts[1][0]))
			{
				it.t.opda = labels[parts[1]];
			}			
			else
			{
				it.t.opda = atoi(parts[1].c_str());
			}
		}
		else if(parts[0] == "BEQ")
		{
			it.h.op = BEQ;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			if(isalpha(parts[3][0]))
			{
				it.h.sto = labels[parts[3]];
				it.h.pad = 0;
			}			
			else
			{
				it.h.sto = atoi(parts[3].c_str());
				it.h.pad = 1;
			}
		}
		else if(parts[0] == "BNE")
		{
			it.h.op = BNE;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			if(isalpha(parts[3][0]))
			{
				it.h.sto = labels[parts[3]];
				it.h.pad = 0;
			}			
			else
			{
				it.h.sto = atoi(parts[3].c_str());
				it.h.pad = 1;
			}
		}
		else if(parts[0] == "BGT")
		{
			it.h.op = BGT;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			if(isalpha(parts[3][0]))
			{
				it.h.sto = labels[parts[3]];
				it.h.pad = 0;
			}			
			else
			{
				it.h.sto = atoi(parts[3].c_str());
				it.h.pad = 1;
			}
		}
		else if(parts[0] == "BLT")
		{
			it.h.op = BLT;
			it.h.opda = atoi(parts[1].c_str());
			it.h.opdb = atoi(parts[2].c_str());
			if(isalpha(parts[3][0]))
			{
				it.h.sto = labels[parts[3]];
				it.h.pad = 0;
			}			
			else
			{
				it.h.sto = atoi(parts[3].c_str());
				it.h.pad = 1;
			}
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

void Thread::Reset()
{
	IC = 0;
	Alive = true;
}

void Thread::SetMemLoc(int l)
{
	IC = l;
	memStart = l;
	for(int i = 0; i < instructions.size(); i++)
	{
		instrHOP& is = *((instrHOP*)&instructions[i]);
		switch(is.op)
		{
			case JR:
				cout << "not sure what to do with JR...\n";
				break;
			case JMP:
				is.opdb += l;
			   	break;
			case BNE:
			case BEQ:
			case BGT:
			case BLT:
				is.sto += l;

		}
	}
}

void Thread::SetPriority(int p)
{
	if(p >= 0)
	{
		priority = p;
	}
}
