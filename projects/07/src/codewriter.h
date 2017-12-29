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
	string filename;

	void setFileName(string);
	void writeArithmetic(string);
	void writePushPop(string, string, int);
	void close();

private:
	int loop = 0;
};


#endif