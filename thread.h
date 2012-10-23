#include <vector>

using std::vector;

class Thread
{
	public:
		Thread();
		Thread(char filename[]);
		Parse(char filename[]);

	private:
		vector<int> instructions;
		vector<int> registers;
}
