#include "system.h"

int main()
{
	char f[] = "test.jasm";
	char f2[] = "test2.jasm";
	char f3[] = "test3.jasm";
	char f4[] = "test4.jasm";
	char f5[] = "test5.jasm";
	char f6[] = "test6.jasm";
	char f7[] = "functest.jasm";

	System sys;
	Thread kb(f5);
	Thread th(f);	
	Thread re(f2);
	Thread ad(f3);
	Thread ne(f4);
	Thread fnc(f6);

	//th.SetPriority(20);

	DSTAT("loading processes...");


	//sys.LoadProcess(kb);
	//sys.LoadProcess(th);
	//sys.LoadProcess(re);
	sys.LoadProcess(ad);
	//sys.LoadProcess(ne);
	//sys.LoadProcess(fnc);
	//sys.Start();
	sys.Test();

	return 0;
}
