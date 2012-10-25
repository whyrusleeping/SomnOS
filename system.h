#ifndef SOMN_SYST_H
#define SOMN_SYST_H

#include "thread.h"
#include <iostream>

#define MAXMEMSIZE 1024

using std::cout;

class System
{
	public:
		System();
		void Start();
		void LoadProcess(Thread t);
		void Execute(Thread &t, int count);		
	private:
		vector<Thread> threads;
		vector<int> memory;
		int freeMemI;

		bool run;
		void add(int a, int b, int sto);
		void subtract(int a, int b, int sto);
		void multiply(int a, int b, int sto);
		void divide(int a, int b, int sto);
		
		void jump(int offs);
		void jump_register(int nIC);
		void branch(int pos);
		void print(int reg);



};
#endif
