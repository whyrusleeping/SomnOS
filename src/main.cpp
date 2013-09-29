#include "system.h"

int main()
{
	char f[] = "test.jasm";
	char f2[] = "test2.jasm";
	char f3[] = "test3.jasm";
	char f4[] = "test4.jasm";
	char f5[] = "test5.jasm";
	char f6[] = "test6.jasm";
	//char f7[] = "functest.jasm";

	System sys;
	Thread kb(f5);
	Thread th(f);	
	Thread re(f2);
	Thread ad(f3);
	Thread ne(f4);
	Thread fnc(f6);

	//th.SetPriority(20);

	DSTAT("loading processes...");


	cout << "This test routine will load two 'programs' and run them concurrently.\nThe first program counts down from 30 to zero.\n";
	cout << "The second program will count up to 20, they will execute at the same time.\npress any key to start...";
	std::cin.ignore();
	
	//sys.LoadProcess(kb);
	//sys.LoadProcess(th);
	sys.LoadProcess(re);
	sys.LoadProcess(ad);
	//sys.LoadProcess(ne);
	//sys.LoadProcess(fnc);
	//sys.Start();
	sys.Test();

	return 0;
}
