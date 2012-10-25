#include "system.h"

int main()
{
	char f[] = "test.jasm";
	char f2[] = "test2.jasm";
	char f3[] = "test3.jasm";
	char f4[] = "test4.jasm";
	System sys;
	Thread th(f);	
	Thread re(f2);
	Thread ad(f3);
	Thread ne(f4);

	DSTAT("loading processes...");

	sys.LoadProcess(th);
	sys.LoadProcess(re);
	sys.LoadProcess(ad);
	sys.LoadProcess(ne);

	sys.Start();

	return 0;
}
