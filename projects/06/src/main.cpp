#include <vector>
#include <string>
#include <fstream>
#include "assembler.h"

using namespace std;

int main(int argv, char** argc){

	string in = argc[1];

	//main prog
	assembler A(in);
	A.firstPass();
	A.secondPass();

	//output
	string out = in.substr(0, in.size()-3) + "hack";
	
	ofstream out_file;
	out_file.open(out.c_str());
	for(auto i:A.Res)
		out_file << i;
	out_file.close();
}