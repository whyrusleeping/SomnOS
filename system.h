#ifndef SOMN_SYST_H
#define SOMN_SYST_H

#include "thread.h"
#include <iostream>

#define MAXMEMSIZE 128

using std::cout;

class System
{
	public:
		System();
		void Run(Thread &t, int count);		
	private:
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
