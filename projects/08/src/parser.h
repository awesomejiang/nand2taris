#ifndef PARSER_H
#define PARSER_H


#include <vector>
#include <string>

using namespace std;

class parser
{
public:
	vector<string> commands;
	vector<string>::iterator currCommand;

	parser();
	parser(string);
	~parser();

	bool hasMoreCommands();
	void advance();
	string commandType();
	string arg1();
	int arg2();


};



#endif