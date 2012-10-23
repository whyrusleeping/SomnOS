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
	private:
		vector<int> instructions;
		vector<int> registers;
		int IC;
};

#endif
