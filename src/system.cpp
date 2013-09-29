#include "system.h"

System::System()
{
	//Nothing to do here yet...
	run = true;
	freeMemI = 0;
	memory.resize(MAXMEMSIZE,0);
}

void System::LoadProcess(Thread t)
{
	t.SetMemLoc(freeMemI);
	threads.push_back(t);

	for(size_t i = 0; i < t.instructions.size(); i++)
	{
		memory[freeMemI + i] = t.instructions[i];
	}
	freeMemI += t.instructions.size();
	
}

void System::RestoreKeyboardBlocking()
{
	tcsetattr(0, TCSANOW, &initial_settings);
}

void System::SetKeyboardNonBlock()
{
	
	struct termios new_settings;
  	tcgetattr(0,&initial_settings);

   new_settings = initial_settings;
   new_settings.c_lflag &= ~ICANON;
   new_settings.c_lflag &= ~ECHO;
   new_settings.c_lflag &= ~ISIG;
   new_settings.c_cc[VMIN] = 0;
   new_settings.c_cc[VTIME] = 0;

   tcsetattr(0, TCSANOW, &new_settings);
}

void System::Test()
{
	SetKeyboardNonBlock();
	//bool nrun = true;
	//int a = 50;
	char inp = 0;
	while(run)
	{
		inp = getchar();
		if(inp > 0)
		{
			memory[KEYBOARD_BUFFER] = inp;
			inp = 0;
		}

		if(memory[SCREEN_BUFFER] != 0)
		{
			cout << (char)memory[SCREEN_BUFFER];
			memory[SCREEN_BUFFER] = 0;
			std::cin.ignore();
		}

		for(size_t i = 0; i < threads.size(); i++)
		{
			Execute(threads[i],2 + threads[i].priority);
			if(!threads[i].Alive)
			{
				DSTAT("Killing Thread.");
				threads.erase(threads.begin() + i);
			}
		}

		if(threads.size() == 0)
			run = false;

	}
	RestoreKeyboardBlocking();
}

//Main system scheduler
void System::Start()
{
	SetKeyboardNonBlock();
	DSTAT("Num Threads: " << threads.size());
	char inp = 0;
	//int nr = 0;
	while(run)
	{
		
		for(size_t i = 0; i < threads.size(); i++)
		{
			cout << "Thread Count: " << threads.size() << "\n";
			Execute(threads[i],2 + threads[i].priority);
			if(!threads[i].Alive)
			{
				DSTAT("Killing Thread.");
				threads.erase(threads.begin() + i);
			}
		}
		

		inp = getchar();
		if(inp > 0)
		{
			memory[KEYBOARD_BUFFER] = inp;
			cout << "Read " << inp << "\n";
			inp = 0;
		}

		if(threads.size() == 0)
			run = false;
	}
	RestoreKeyboardBlocking();
}

void System::Execute(Thread &t, int count)
{
	Instruction i;
	i.VALUE = 0;

	while(i.getOpCode() != HALT && count-- > 0 && t.Alive) 
	{ 
		//i.ival = t.instructions[t.IC];
		i.VALUE = memory[t.IC];
		DSTAT("Operand: " << i.getOpCode() << "  IC: " << t.IC);
		switch(i.getOpCode())
		{
			case ADD:
				t.registers[i.getStoVal()] = t.registers[i.getOpda()] + t.registers[i.getOpdb()];
				break;
			case SUB:
				t.registers[i.getStoVal()] = t.registers[i.getOpda()] - t.registers[i.getOpdb()];
				break;
			case MUL:
				t.registers[i.getStoVal()] = t.registers[i.getOpda()] * t.registers[i.getOpdb()];
				break;
			case DIV:
				t.registers[i.getStoVal()] = t.registers[i.getOpda()] / t.registers[i.getOpdb()];
				break;
			case PRINT:
				DSTAT(t.name << ":" << t.IC);
				cout << t.registers[i.getOpda()] << "\n";
				break;
			case LI:
				t.registers[i.getOpda()] = i.getOpdbAlt();
				break;
			case LR:
				DSTAT("Memory at: " << i.getOpda() << " " << i.getOpdbAlt());
				DSTAT("READING: " << memory[t.registers[i.getOpdb()]]); 
				t.registers[i.getOpda()] = memory[t.registers[i.getOpdb()]];
				break;
			case SR:
				DSTAT("Storing Value " << t.registers[i.getOpda()]);
				memory[t.registers[i.getOpdb()]] = t.registers[i.getOpda()];
				break;
			case JR:
				t.IC = t.registers[i.getOpda()] - 1;
				break;
			case JMP:
				t.IC = i.getOpdbAlt() - 1;
				break;
			case MOV:
				t.registers[i.getOpdb()] = t.registers[i.getOpda()];
				break;
			case BEQ:
				DSTAT("reg[a] = " << t.registers[i.getOpda()] << " reg[b] = " << t.registers[i.getOpdb()]);
				if(t.registers[i.getOpda()] == t.registers[i.getOpdb()])
				{
					if(i.getFlagA() == 1)
						t.IC = t.registers[i.getStoVal()] - 1;
					else
						t.IC = i.getJumpVal() - 1;
				}
				break;
			case BNE:
				if(t.registers[i.getOpda()] != t.registers[i.getOpdb()])
				{
					if(i.getFlagA() == 1)
						t.IC = t.registers[i.getStoVal()] - 1;
					else
						t.IC = i.getJumpVal() - 1;
				}	
				break;
			case BGT:
				if(t.registers[i.getOpda()] > t.registers[i.getOpdb()])
				{
					if(i.getFlagA() == 1)
						t.IC = t.registers[i.getStoVal()] - 1;
					else
						t.IC = i.getJumpVal() - 1;
				}
				break;
			case BLT:
				if(t.registers[i.getOpda()] < t.registers[i.getOpdb()])
				{
					if(i.getFlagA() == 1)
						t.IC = t.registers[i.getStoVal()] - 1;
					else
						t.IC = i.getJumpVal() - 1;
				}
				break;
			case RET:
				t.IC = t.registers[31];
				DSTAT("Returned to " << t.IC << "\n");
				break;
			case JAL:
				t.registers[31] = t.IC;
				t.IC = i.getJumpVal() - 1;
				DSTAT("Stored Line " << t.registers[31] << "\n");
				DSTAT("Jumped to " << t.IC << "\n");
				break;


		}
		t.IC++;
	}	
	if(i.getOpCode() == HALT)
	{
		t.Alive = false;
	}
}

