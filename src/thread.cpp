#include "thread.h"


Thread::Thread()
{
	registers.resize(32,0);
	instructions.resize(0);
	IC = 0;
	Alive = true;
	priority = 0;
	instrStart = 0;
}

Thread::Thread(char *filename)
{	
	registers.resize(32,0);
	instructions.resize(0);
	IC = 0;
	Alive = true;
	priority = 0;
	instrStart = 0;
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

void Thread::parseMath(vector<string> &tokens, Instruction &it, int line)
{
	it.setOpda(parseReg(tokens[1], line));
	it.setOpdb(parseReg(tokens[2], line));
	it.setStoVal(parseReg(tokens[3], line));
}

void Thread::Parse(char *filename)
{
	name = filename;
	DSTAT("Parsing...\n");
	Instruction it;
	ifstream asmf(filename);
	vector<string> parts;
	vector<string> lines;
	string line;
	instructions.resize(0);
	int labelCounter = 0;
	map<string, int> labels;
	map<string, string> stringLits;

	//Pre-parsing
	while(asmf.good())
	{
		getline(asmf, line);
		if(startsWith(line, "LAB"))
		{
			DSTAT("Adding label from line: " << line << "\n");
			string tmpLab = splitString(line, ' ')[1];
			labels[tmpLab] = labelCounter;
		}
		else if(startsWith(line ,"STR"))
		{
			vector<string> brkLine = splitString(line, ' ');
			stringLits[brkLine[1]] = brkLine[2];
		}
		else if(startsWith(line, "//"))
		{
			//do nothing, ignore comments
		}
		else
		{
			if(line != "")
			{
				labelCounter++;
				lines.push_back(line);
			}
		}
	}

	asmf.close();
	DSTAT("finished reading from file");

	//Tranlate string labels into memory locations
	for(map<string, string>::iterator i = stringLits.begin(); i != stringLits.end(); i++)
	{
		labels[(*i).first] = instructions.size();	
		for(int ix = 0; ix < (*i).second.length(); ix++)
		{
			instructions.push_back((*i).second[ix]);
		}
	}

	instrStart = instructions.size();
	//Compiling
	for(int j = 0; j < lines.size(); j++)
	{
		parts = splitString(lines[j], ' ');
		DSTAT("parsing" << lines[j]);
		DSTAT(parts.size());
		if(parts[0] == "LI")
		{
			it.setOpCode(LI);
			
			it.setOpda(parseReg(parts[1], j));

			if(parts[2][0] == '#')
			{
				it.setOpdbAlt(atoi(&(parts[2].c_str()[1])));
			}
			else
			{
				cout << "Invalid Parameter to LI on line: " << j << "\n";
				exit(1);
			}
		}
		else if(parts[0] == "LR")
		{
			it.setOpCode(LR);
			it.setOpda(parseReg(parts[1], j));
			it.setOpdb(parseReg(parts[2], j));
		}
		else if(parts[0] == "SR")
		{
			it.setOpCode(SR);
			it.setOpda(parseReg(parts[1], j));
			it.setOpdb(parseReg(parts[2], j));
		}
		else if(parts[0] == "ADD")
		{
			it.setOpCode(ADD);
			parseMath(parts, it, j);
		}
		else if(parts[0] == "SUB")
		{
			it.setOpCode(SUB);
			parseMath(parts, it, j);
		}
		else if(parts[0] == "MUL")
		{
			it.setOpCode(MUL);
			parseMath(parts, it, j);
		}
		else if(parts[0] == "DIV")
		{
			it.setOpCode(DIV);
			parseMath(parts, it, j);
		}
		else if(parts[0] == "MOV")
		{
			it.setOpCode(MOV);
			it.setOpda(parseReg(parts[1], j));
			it.setOpdb(parseReg(parts[2], j));
		}
		else if(parts[0] == "PRINT")
		{
			it.setOpCode(PRINT);
			it.setOpdb(parseReg(parts[1], j));

		}
		else if(parts[0] == "JR")
		{
			it.setOpCode(JR);
			it.setOpda(parseReg(parts[1], j));	
		}
		else if(parts[0] == "JMP")
		{
			it.setOpCode(JMP);
			if(isalpha(parts[1][0]))
			{
				it.setJumpVal(labels[parts[1]]);
			}			
			else
			{
				it.setJumpVal(atoi(parts[1].c_str()));
			}
		}
		else if(parts[0] == "JAL")
		{
			it.setOpCode(JAL);
			if(!isalpha(parts[1][0]))
			{
				cout << "JAL must point to a Label, Line " << j << "\n";
				exit(1);
			}
			else
			{
				it.setJumpVal(labels[parts[1]]);
			}
		}
		else if(parts[0] == "RET")
		{
			it.setOpCode(RET);
		}
		else if(parts[0] == "BEQ")
		{
			it.setOpCode(BEQ);
			it.setOpda(parseReg(parts[1], j));
			it.setOpdb(parseReg(parts[2], j));
			if(isalpha(parts[3][0]))
			{
				//jump to a label
				it.setJumpVal(labels[parts[3]]);
				it.setFlagA(0);
			}			
			else
			{
				//jump to a line number
				it.setJumpVal(atoi(parts[3].c_str()));
				it.setFlagA(1);
			}
		}
		else if(parts[0] == "BNE")
		{
			it.setOpCode(BNE);
			it.setOpda(parseReg(parts[1], j));
			it.setOpdb(parseReg(parts[2], j));
			if(isalpha(parts[3][0]))
			{
				//jump to a label
				it.setJumpVal(labels[parts[3]]);
				it.setFlagA(0);
			}			
			else
			{
				//jump to a line number
				it.setJumpVal(atoi(parts[3].c_str()));
				it.setFlagA(1);
			}
		}
		else if(parts[0] == "BGT")
		{
			it.setOpCode(BGT);
			it.setOpda(parseReg(parts[1], j));
			it.setOpdb(parseReg(parts[2], j));
			if(isalpha(parts[3][0]))
			{
				//jump to a label
				it.setJumpVal(labels[parts[3]]);
				it.setFlagA(0);
			}			
			else
			{
				//jump to a line number
				it.setJumpVal(atoi(parts[3].c_str()));
				it.setFlagA(1);
			}
		}
		else if(parts[0] == "BLT")
		{
			it.setOpCode(BLT);
			it.setOpdb(parseReg(parts[2], j));
			if(isalpha(parts[3][0]))
			{
				//jump to a label
				it.setJumpVal(labels[parts[3]]);
				it.setFlagA(0);
			}			
			else
			{
				//jump to a line number
				it.setJumpVal(atoi(parts[3].c_str()));
				it.setFlagA(1);
			}
		}
		else if(parts[0] == "HALT")
		{
			it.setOpCode(HALT);
		}
		else
		{
			continue;
		}
		instructions.push_back(it.VALUE);
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
	cout << "Mem start: " <<  l << "\n";
	IC = l + instrStart;
	memStart = l + instrStart;
	DSTAT("IC: " << IC);
	DSTAT("Memstart: " << memStart);
	for(int i = instrStart; i < instructions.size(); i++)
	{
		Instruction is;
		is.VALUE = instructions[i];	
		switch(is.getOpCode())
		{
			case JR:
				cout << "not sure how to link JR...\n";
				break;
			case JMP:
				is.setOpdbAlt(is.getOpdbAlt() + l);
			   	break;
			case BNE:
			case BEQ:
			case BGT:
			case BLT:
				cout << "Updating: ";
				is.print();
				is.setJumpVal(is.getJumpVal() + l);
				cout << "To: ";
				is.print();

		}
		instructions[i] = is.VALUE;
	}
}

void Thread::SetPriority(int p)
{
	if(p >= 0)
	{
		priority = p;
	}
}

void Thread::printProgram()
{
	for(int i = 0; i < instructions.size(); i++)
	{
		Instruction is(instructions[i]);
		is.print();
	}
}

void Thread::saveBinary(char *filename)
{
	
}
