#ifndef SOMN_THREAD_H
#define SOMN_THREAD_H

#include "instrDefs.h"
#include "utils.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>

using std::map;
using std::cout;
using std::ifstream;

class System;

class Thread
{
	public:
		friend System; 
		Thread();
		Thread(char *filename);
		void Parse(char *filename);
		int Compile();
		void Reset();
		void SetMemLoc(int l);
		void SetPriority(int p);
	private:
		vector<int> instructions;
		vector<int> registers;
		int IC;
		bool Alive;
		int priority;
		int memStart;
		string name;

		int parseReg(string token, int line);
		void parseMath(vector<string> &tokens, instr &it, int line);
};

#endif
