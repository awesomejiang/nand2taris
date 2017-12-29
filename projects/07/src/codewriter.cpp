#include "codewriter.h"

#include <string>
#include <sstream>
#include <algorithm>

codewriter::codewriter(string s){

	outfile.open(s.c_str());
}

codewriter::~codewriter(){}

void codewriter::setFileName(string s){
	
	filename = s.substr(0, s.size()-3);
	loop = 0;
}

void codewriter::writeArithmetic(string s){

	if(s == "add" || s == "sub" || s == "and" || s == "or"){
		outfile<<"@SP"<<endl;
		outfile<<"AM=M-1"<<endl;
		outfile<<"D=M"<<endl;
		outfile<<"A=A-1"<<endl;
		if(s == "add")
			outfile<<"M=M+D"<<endl;
		if(s == "sub")
			outfile<<"M=M-D"<<endl;
		if(s == "and")
			outfile<<"M=D&M"<<endl;
		if(s == "or")
			outfile<<"M=D|M"<<endl;
	}
	if(s == "neg"){
		outfile<<"@SP"<<endl;
		outfile<<"A=M-1"<<endl;
		outfile<<"M=-M"<<endl;
	}
	if(s == "eq" || s == "gt" || s == "lt"){
		string upper;
		transform(filename.begin(), filename.end(), upper.begin(), ::toupper);

		stringstream ss;
		ss << loop;
		string index = ss.str();

		outfile<<"@SP"<<endl;
		outfile<<"AM=M-1"<<endl;
		outfile<<"D=M"<<endl;
		outfile<<"A=A-1"<<endl;
		outfile<<"D=M-D"<<endl;
		outfile<<"@"+upper+".FALSE."+index<<endl;
		if(s == "eq")
			outfile<<"D;JNE"<<endl;
		if(s == "gt")
			outfile<<"D;JLE"<<endl;
		if(s == "lt")
			outfile<<"D;JGE"<<endl;
		outfile<<"@SP"<<endl;
		outfile<<"A=M-1"<<endl;
		outfile<<"M=-1"<<endl;
		outfile<<"@"+upper+".CONTINUE."+index<<endl;
		outfile<<"0;JMP"<<endl;
		outfile<<"("+upper+".FALSE."+index+")"<<endl;
		outfile<<"@SP"<<endl;
		outfile<<"A=M-1"<<endl;
		outfile<<"M=0"<<endl;
		outfile<<"("+upper+".CONTINUE."+index+")"<<endl;
	}
	if(s == "not"){
		outfile<<"@SP"<<endl;
		outfile<<"A=M-1"<<endl;
		outfile<<"M=!M"<<endl;
	}

	loop++;
}

void codewriter::writePushPop(string s, string arg1, int arg2){
	stringstream ss;
	ss<<arg2;
	string number = ss.str();

	if(s == "push"){
		if(arg1 == "constant"){
			outfile<<"@"+number<<endl;
			outfile<<"D=A"<<endl;

		}

		if(arg1 == "local" || arg1 == "argument" || arg1 == "this" || arg1 == "that"){
			outfile<<"@"+number<<endl;
			outfile<<"D=A"<<endl;
			if(arg1 == "local")
				outfile<<"@LCL"<<endl;
			if(arg1 == "argument")
				outfile<<"@ARG"<<endl;
			if(arg1 == "this")
				outfile<<"@THIS"<<endl;
			if(arg1 == "that")
				outfile<<"@THAT"<<endl;
			outfile<<"A=M+D"<<endl;
			outfile<<"D=M"<<endl;
		}

		if(arg1 == "pointer" || arg1 == "temp"){
			outfile<<"@"+number<<endl;
			outfile<<"D=A"<<endl;
			if(arg1 == "pointer")
				outfile<<"@THIS"<<endl;
			if(arg1 == "temp")
				outfile<<"@R5"<<endl;
			outfile<<"A=A+D"<<endl;
			outfile<<"D=M"<<endl;
		}

		if(arg1 == "static"){
			outfile<<"@"+filename+"."+number<<endl;
			outfile<<"D=M"<<endl;
		}

		outfile<<"@SP"<<endl;
		outfile<<"A=M"<<endl;
		outfile<<"M=D"<<endl;
		outfile<<"@SP"<<endl;
		outfile<<"M=M+1"<<endl;
	}

	if(s == "pop"){
		if(arg1 == "local" || arg1 == "argument" || arg1 == "this" || arg1 == "that"){
			outfile<<"@"+number<<endl;
			outfile<<"D=A"<<endl;
			if(arg1 == "local")
				outfile<<"@LCL"<<endl;
			if(arg1 == "argument")
				outfile<<"@ARG"<<endl;
			if(arg1 == "this")
				outfile<<"@THIS"<<endl;
			if(arg1 == "that")
				outfile<<"@THAT"<<endl;
			outfile<<"D=M+D"<<endl;
		}

		if(arg1 == "pointer" || arg1 == "temp"){
			outfile<<"@"+number<<endl;
			outfile<<"D=A"<<endl;
			if(arg1 == "pointer")
				outfile<<"@THIS"<<endl;
			if(arg1 == "temp")
				outfile<<"@R5"<<endl;
			outfile<<"D=A+D"<<endl;
		}

		if(arg1 == "static"){
			outfile<<"@"+filename+"."+number<<endl;
			outfile<<"D=A"<<endl;
		}

		outfile<<"@R13"<<endl;			
		outfile<<"M=D"<<endl;			
		outfile<<"@SP"<<endl;			
		outfile<<"AM=M-1"<<endl;			
		outfile<<"D=M"<<endl;			
		outfile<<"@R13"<<endl;			
		outfile<<"A=M"<<endl;			
		outfile<<"M=D"<<endl;	
	}

	loop++;
}

void codewriter::close(){

	outfile.close();
}
