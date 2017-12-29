#include "whitespace.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#ifndef PARSER_H
#define PARSER_H

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
	string symbol();
	string dest();
	string comp();
	string jump();

private:
	bool isCcommand();

};


parser::parser(string filename){
	commands = stripWhiteSpace(filename, 1);
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
	if(command[0] == '@')
		return "A_COMMAND";
	if(command[0] == '(')
		return "L_COMMAND";

	return "C_COMMAND";
}

string parser::symbol(){
	string type = commandType();
	string command = *currCommand;
	if(type == "A_COMMAND")
		return command.substr(1);
	if(type == "L_COMMAND")
		return command.substr(1,command.size()-1);

	cout<<"The type of command is C_COMMAND, parser::symbol() is wrongly called!"<<endl;
	return "";
}

string parser::dest(){
	string command = *currCommand;
	if(isCcommand()){
		int eqPos = command.find("=");
		if(eqPos != string::npos)
			return command.substr(0,eqPos);
	}
	else
		cout<<"The type of command is not C_COMMAND, parser::dest() is wrongly called!"<<endl;

	return "";
}

string parser::comp(){
	string command = *currCommand;
	if(isCcommand()){
		int eqPos = command.find("=");
		int semPos = command.find(";");
		return command.substr((eqPos != string::npos)?(eqPos+1):0, semPos);
	}
	else
		cout<<"The type of command is not C_COMMAND, parser::dest() is wrongly called!"<<endl;

	return "";
}

string parser::jump(){
	string command = *currCommand;
	if(isCcommand()){
		int semPos = command.find(";");
		if(semPos != string::npos && semPos != command.size()-1)
			return command.substr(semPos+1);
	}
	else
		cout<<"The type of command is not C_COMMAND, parser::dest() is wrongly called!"<<endl;

	return "";
}

bool parser::isCcommand(){

	return commandType() == "C_COMMAND";
}




#endif