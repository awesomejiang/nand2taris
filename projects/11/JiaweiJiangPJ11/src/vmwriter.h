#ifndef VMWRITER_H
#define VMWRITER_H

#include <string>
#include <fstream>

using namespace std;

class VMWriter{
public:
	VMWriter();
	~VMWriter();
	VMWriter(string);

	void writePush(string, int);
	void writePop(string, int);
	void writeArithmetic(string);
	void writeLabel(string);
	void writeGoto(string);
	void writeIf(string);
	void writeCall(string, int );
	void writeFunction(string, int);
	void writeReturn();

	void close();

private:
	ofstream outfile;
};



#endif