#include "system.h"

System::System()
{
	//Nothing to do here yet...
	run = true;
	freeMemI = 0;
	memory.resize(MAXMEMSIZE);
}

void System::LoadProcess(Thread t)
{
	t.SetMemLoc(freeMemI);
	threads.push_back(t);

	for(int i = 0; i < t.instructions.size(); i++)
	{
		memory[freeMemI + i] = t.instructions[i];
	}
	freeMemI += t.instructions.size();
	
}

void System::Start()
{
	DSTAT("Num Threads: " << threads.size());
	while(run)
	{
		for(int i = 0; i < threads.size(); i++)
		{
			Execute(threads[i],2);
			if(!threads[i].Alive)
			{
				DSTAT("Killing Thread.");
				threads.erase(threads.begin() + i);
			}
		}
		if(threads.size() == 0)
			run = false;
	}
}

void System::Execute(Thread &t, int count)
{
	instr i;
	i.ival = 0;

	while(i.h.op != HALT && count-- > 0 && t.Alive) 
	{ 
		//i.ival = t.instructions[t.IC];
		i.ival = memory[t.IC];
		//DSTAT("Operand: " << i.h.op << "  IC: " << t.IC);
		switch(i.h.op)
		{
			case ADD:
				t.registers[i.h.sto] = t.registers[i.h.opda] + t.registers[i.h.opdb];
				break;
			case SUB:
				t.registers[i.h.sto] = t.registers[i.h.opda] - t.registers[i.h.opdb];
				break;
			case MUL:
				t.registers[i.h.sto] = t.registers[i.h.opda] * t.registers[i.h.opdb];
				break;
			case DIV:
				t.registers[i.h.sto] = t.registers[i.h.opda] / t.registers[i.h.opdb];
				break;
			
			case PRINT:
				DSTAT(t.name << ":" << t.IC);
				cout << t.registers[i.t.opda] << "\n";
				break;

			case LI:
				t.registers[i.t.opda] = i.t.opdb;
				break;
			case JR:
				t.IC = t.registers[i.t.opda] - 1;
				break;
			case JMP:
				t.IC = i.t.opdb - 1;
				break;
			case MOV:
				t.registers[i.t.opdb] = t.registers[i.t.opda];
				break;
			case BEQ:
				if(t.registers[i.h.opda] == t.registers[i.h.opdb])
				{
					if(i.h.pad == 1)
						t.IC = t.registers[i.h.sto] - 1;
					else
						t.IC = i.h.sto - 1;
				}
				break;
			case BNE:
				if(t.registers[i.h.opda] != t.registers[i.h.opdb])
				{
					if(i.h.pad == 1)
						t.IC = t.registers[i.h.sto] - 1;
					else
						t.IC = i.h.sto - 1;
				}	
				break;
			case BGT:
				if(t.registers[i.h.opda] > t.registers[i.h.opdb])
				{
					if(i.h.pad == 1)
						t.IC = t.registers[i.h.sto] - 1;
					else
						t.IC = i.h.sto - 1;
				}
				break;
			case BLT:
				if(t.registers[i.h.opda] < t.registers[i.h.opdb])
				{
					if(i.h.pad == 1)
						t.IC = t.registers[i.h.sto] - 1;
					else
						t.IC = i.h.sto - 1;
				}
				break;

		}
		t.IC++;
	}	
	if(i.h.op == HALT)
	{
		t.Alive = false;
	}
}

