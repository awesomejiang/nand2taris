#include <string>
#include <unordered_map>

#ifndef CODE_H
#define CODE_H

using namespace std;

class code
{
public:
	code();
	code(string);
	~code();

	string in;
	string out;

	string dest();
	string comp();
	string jump();
	
};


code::code(string s){

	in = s;
}

code::~code(){}

string code::dest(){
	if(in.empty())	return "000";
	if(in == "M")	return "001";
	if(in == "D")	return "010";
	if(in == "MD")	return "011";
	if(in == "A")	return "100";
	if(in == "AM")	return "101";
	if(in == "AD")	return "110";
	if(in == "AMD")	return "111";

	cout<<"Error in code::dest: wrong input!"<<endl;
	return "";
}

string code::comp(){
	if(in == "0")	return "0101010";
	if(in == "1")	return "0111111";
	if(in == "-1")	return "0111010";
	if(in == "D")	return "0001100";
	if(in == "A")	return "0110000";
	if(in == "!D")	return "0001101";
	if(in == "!A")	return "0110001";
	if(in == "-D")	return "0001111";
	if(in == "-A")	return "0110011";
	if(in == "D+1")	return "0011111";
	if(in == "A+1")	return "0110111";
	if(in == "D-1")	return "0001110";
	if(in == "A-1")	return "0110010"; 
	if(in == "D+A")	return "0000010";
	if(in == "D-A")	return "0010011";
	if(in == "A-D")	return "0000111";
	if(in == "D&A")	return "0000000";
	if(in == "D|A")	return "0010101";
	if(in == "M")	return "1110000";
	if(in == "!M")	return "1110001";
	if(in == "-M")	return "1110011";
	if(in == "M+1")	return "1110111";
	if(in == "M-1")	return "1110010";
	if(in == "D+M")	return "1000010";
	if(in == "D-M")	return "1010011";
	if(in == "M-D")	return "1000111";
	if(in == "D&M")	return "1000000";
	if(in == "D|M")	return "1010101";

	cout<<"Error in code::comp: wrong input!"<<endl;
	return "";
}

string code::jump(){
	if(in.empty())	return "000";
	if(in == "JGT")	return "001";
	if(in == "JEQ")	return "010";
	if(in == "JGE")	return "011";
	if(in == "JLT")	return "100";
	if(in == "JNE")	return "101";
	if(in == "JLE")	return "110";
	if(in == "JMP")	return "111";

	cout<<"Error in code::jump: wrong input!"<<endl;
	return "";
}

#endif