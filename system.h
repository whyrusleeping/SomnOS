#include <vector>
#include "instrDefs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>

#define MAXMEMSIZE 128




using std::string;
using std::ifstream;
using std::cout;
using std::vector;

#ifdef DEBUG
	#define DSTAT(VAR) cout << VAR  << "\n";
#else
	#define DSTAT(VAR) 
#endif

typedef struct inst_thrOP
{
	unsigned short op : 4;
	unsigned short opda : 5;
	unsigned short opdb : 5;
	unsigned short sto : 5;
	unsigned short pad : 13;
}instrHOP;

typedef struct instr_twoOP
{
	unsigned short op : 4;
	unsigned short opda : 5;
	unsigned int opdb : 23;
}instrTOP;

typedef struct jumpInstr
{
	unsigned short op : 4;
	unsigned short opt : 1;
	unsigned int val : 27;
}jumpInstr;

typedef union instr
{
	jumpInstr j;
	instrTOP t;
	instrHOP h;
	int ival;
}instr;

class System
{
	public:
		System();
		void Run();		
		void Parse(char *filename);
	private:
		int IC;
		vector<int> instructions;
		vector<int> registers;
		vector<int> memory;

		void add(int a, int b, int sto);
		void subtract(int a, int b, int sto);
		void multiply(int a, int b, int sto);
		void divide(int a, int b, int sto);
		
		void jump(int offs);
		void jump_register(int nIC);
		void branch(int pos);
		void print(int reg);



};
