#include <vector>
#include <string>

using namespace std;

class JackCompiler{
	public:
		JackCompiler(string);
		~JackCompiler();

		void run();

	private:
		vector<string> files; //store jack files. No ".jack" includes.

};

