#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <fstream>
#include <string>

using namespace std;

class codewriter
{
public:
	codewriter();
	codewriter(string);
	~codewriter();

	ofstream outfile;
	string filename = "Sys";
	string funcname;

	void setFileName(string);
	void writeArithmetic(string);
	void writePushPop(string, string, int);
	void writeInit();
	void writeLabel(string);
	void writeGoto(string);
	void writeIf(string);
	void writeCall(string, int);
	void writeReturn();
	void writeFunction(string, int);
	void writeInitFunction();

	void close();

private:
	int loop = 0;
};


#endif