#include <vector>
#include <string>

using namespace std;

class Analyzer{
	public:
		Analyzer(string);
		~Analyzer();

		void run();

	private:
		vector<string> files; //store jack files. No ".jack" includes.

};

