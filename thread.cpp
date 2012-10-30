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

int Thread::parseReg(string token, int line)
{
	if(token[0] == 'r')
	{
		return atoi(&(token.c_str()[1]));
	}
	else
	{
		cout << "Invalid parameter \'" << token << "\' on line " << line << "\n";
		exit(1);
	}
}

void Thread::parseMath(vector<string> &tokens, instr &it, int line)
{
	it.h.opda = parseReg(tokens[1], line);
	it.h.opdb = parseReg(tokens[2], line);
	it.h.sto =  parseReg(tokens[3], line);
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

	//Pre-parsing
	while(asmf.good())
	{
		getline(asmf, line);
		if(startsWith(line, "LAB"))
		{
			string tmpLab = line.substr(4);
			labels[tmpLab] = labelCounter;
		}
		else if(startsWith(line, "//"))
		{
			//do nothing, ignore comments
		}
		else
		{
			labelCounter++;
			lines.push_back(line);
		}
	}

	asmf.close();
	DSTAT("finished reading from file");

	//Compiling
	for(int j = 0; j < lines.size(); j++)
	{
		parts = splitString(lines[j], ' ');
		DSTAT("parsing" << lines[j]);
		DSTAT(parts.size());
		if(parts[0] == "LI")
		{
			it.t.op = LI;

			it.t.opda = parseReg(parts[1], j);
						
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
			it.t.opda = parseReg(parts[1], j);
			it.t.opdb = parseReg(parts[2], j);
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
			parseMath(parts, it, j);
		}
		else if(parts[0] == "SUB")
		{
			it.h.op = SUB;
			parseMath(parts, it, j);
		}
		else if(parts[0] == "MUL")
		{
			it.h.op = MUL;
			parseMath(parts, it, j);
		}
		else if(parts[0] == "DIV")
		{
			it.h.op = DIV;
			parseMath(parts, it, j);
		}
		else if(parts[0] == "MOV")
		{
			it.t.op = MOV;
			it.t.opda = parseReg(parts[1], j);
			it.t.opdb = parseReg(parts[2], j);
		}
		else if(parts[0] == "PRINT")
		{
			it.t.op = PRINT;
			it.t.opda = parseReg(parts[1], j);
		}
		else if(parts[0] == "JR")
		{
			it.t.op = JR;
			it.t.opda = parseReg(parts[1], j);	
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
			it.h.opda = parseReg(parts[1], j);
			it.h.opdb = parseReg(parts[2], j);
			if(isalpha(parts[3][0]))
			{
				//jump to a label
				it.h.sto = labels[parts[3]];
				it.h.pad = 0;
			}			
			else
			{
				//jump to a line number
				it.h.sto = atoi(parts[3].c_str());
				it.h.pad = 1;
			}
		}
		else if(parts[0] == "BNE")
		{
			it.h.op = BNE;
			it.h.opda = parseReg(parts[1], j);
			it.h.opdb = parseReg(parts[2], j);
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
			it.h.opda = parseReg(parts[1], j);
			it.h.opdb = parseReg(parts[2], j);
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
			it.h.opda = parseReg(parts[1], j);
			it.h.opdb = parseReg(parts[2], j);
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
	//'linking' sort of..
	IC = l;
	memStart = l;
	for(int i = 0; i < instructions.size(); i++)
	{
		instrHOP& is = *((instrHOP*)&instructions[i]);
		switch(is.op)
		{
			case JR:
				cout << "not sure how to link JR...\n";
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
