#include "system.h"

int main()
{
	char f[] = "test.jasm";
	char f2[] = "test2.jasm";
	System sys;
	Thread th(f);	
	Thread re(f2);

	for(int i = 0; i < 5; i++)
	{
		cout << "thread one:\n";
		sys.Run(th, 10);
		cout << "thread two:\n";
		sys.Run(re, 10);
	}
	return 0;
}
