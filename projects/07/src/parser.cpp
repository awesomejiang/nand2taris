#include "parser.h"
#include "whitespace.h"
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

parser::parser(string filename){
	commands = stripWhiteSpace(filename, 0, 1);
	currCommand = commands.begin()-1;
}

parser::~parser(){}

bool parser::hasMoreCommands(){

	return currCommand+1 < commands.end();
}

void parser::advance(){
	if(hasMoreCommands())
		currCommand++;
	else
		cout<<"No more commands, parser::advance() is wrongly called!"<<endl;
}

string parser::commandType(){
	string command = *currCommand;

	stringstream ss(command);
	string s;
	ss>>s;

	if(s == "push" || s == "pop" || s == "label" || s == "goto" || s == "if" || s == "function"
	|| s == "return" || s == "call"){
		transform(s.begin(), s.end(), s.begin(), ::toupper);
		return "C_"+s;
	}

	return "C_ARITHMETIC";
}

string parser::arg1(){
	string command = *currCommand;
	string type = commandType();

	stringstream ss(command);
	string s;
	ss>>s;

	if(type == "C_ARITHMETIC")
		return s;
	if(type != "C_RETURN"){
		ss>>s;
		return s;
	}
	else{
		cout<<"Error in parser::arg1: Unexpected calling!"<<endl;
		return "";
	}

}

int parser::arg2(){
	string command = *currCommand;
	string type = commandType();

	if(type == "C_PUSH" || type == "C_POP" || type == "C_FUNCTION" || type == "C_CALL"){
		stringstream ss(command);
		string s;
		ss>>s;
		ss>>s;
		ss>>s;

		stringstream ress(s);
		int res;
		ress>>res;
		return res;
	}
	else{
		cout<<"Error in parser::arg2: Unexpected calling!"<<endl;
		return -1;
	}

}
