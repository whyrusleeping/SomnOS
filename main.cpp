#include "system.h"

int main()
{
	System sys;
	sys.Parse("test.jasm");
	sys.Run();
}
