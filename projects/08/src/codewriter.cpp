#include "codewriter.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

codewriter::codewriter(string s){

	if(s.find(".vm") != string::npos){
		s = s.substr(0, s.size()-2) + "asm";
	}
	else{
		size_t found;
		//set outfile's name as directory name and put it input dir
		if ((found = s.find_last_of("/")) == string::npos)
			found = -1;

		s = s + "/" + s.substr(found+1) + ".asm";
	}

	outfile.open(s.c_str());
}

codewriter::~codewriter(){}

void codewriter::close(){

	outfile.close();
}

void codewriter::setFileName(string s){
	size_t found;
	//if f s is a path, set filename to the pointed filename only
	if ((found = s.find_last_of("/")) != string::npos)
		filename = s.substr(found+1, s.size()-found-4);
	else
		filename = s.substr(0, s.size()-3);
	loop = 0;
}

void codewriter::writeArithmetic(string s){
	if(s == "add" || s == "sub" || s == "and" || s == "or"
		|| s == "neg" || s == "eq" || s == "gt" || s == "lt"
		|| s == "not"){
		outfile<<"//"<<s<<endl;

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

		outfile<<endl;

		loop++;
	}
}

void codewriter::writePushPop(string s, string arg1, int arg2){

	outfile<<"//"<<s<<" "<<arg1<<" "<<arg2<<endl;

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

	outfile<<endl;

	loop++;
}

void codewriter::writeInit(){

	//@set SP to 256
	outfile<<"//init"<<endl;
	outfile<<"@256"<<endl;
	outfile<<"D=A"<<endl;
	outfile<<"@SP"<<endl;
	outfile<<"M=D"<<endl;
	writeCall("Sys.init", 0);

	outfile<<endl;
}

void codewriter::writeLabel(string s){
	outfile<<"//label "<<s<<endl;

	stringstream ss;
	ss << loop;
	string index = ss.str();

	string label = funcname+"$"+s;
	outfile<<"("+label+")"<<endl;

	outfile<<endl;
}

void codewriter::writeGoto(string s){
	outfile<<"//goto "<<s<<endl;

	stringstream ss;
	ss << loop;
	string index = ss.str();

	string label = funcname+"$"+s;
	outfile<<"@"+label<<endl;
	outfile<<"0;JMP"<<endl;

	outfile<<endl;
}

void codewriter::writeIf(string s){	
	outfile<<"//if-goto "<<s<<endl;

	stringstream ss;
	ss << loop;
	string index = ss.str();

	string label = funcname+"$"+s;
	outfile<<"@SP"<<endl;			
	outfile<<"AM=M-1"<<endl;			
	outfile<<"D=M"<<endl;
	outfile<<"@"+label<<endl;
	outfile<<"D;JNE"<<endl;

	outfile<<endl;
}

void codewriter::writeCall(string arg1, int arg2){
	outfile<<"//call "<<arg1<<" "<<arg2<<endl;

	stringstream ss;
	ss << loop;
	string index = ss.str();

	funcname = arg1;
	string returnLabel = funcname+"&return."+index;

	for(int i=0; i<5; i++){
		switch(i){
			case(0):
				outfile<<"@"+returnLabel<<endl;
				break;
			case(1):
				outfile<<"@LCL"<<endl;
				break;
			case(2):
				outfile<<"@ARG"<<endl;
				break;
			case(3):
				outfile<<"@THIS"<<endl;
				break;
			case(4):
				outfile<<"@THAT"<<endl;
				break;
			default:
				break;
		}

		switch(i){
			case(0):
				outfile<<"D=A"<<endl;
				break;
			default:
				outfile<<"D=M"<<endl;
				break;
		}

		outfile<<"@SP"<<endl;
		outfile<<"A=M"<<endl;
		outfile<<"M=D"<<endl;
		outfile<<"@SP"<<endl;
		outfile<<"M=M+1"<<endl;
	}

		outfile<<"@SP"<<endl;
		outfile<<"D=M"<<endl;
		outfile<<"@5"<<endl;
		outfile<<"D=D-A"<<endl;
		outfile<<"@"<<arg2<<endl;
		outfile<<"D=D-A"<<endl;
		outfile<<"@ARG"<<endl;
		outfile<<"M=D"<<endl;

		outfile<<"@SP"<<endl;
		outfile<<"D=M"<<endl;
		outfile<<"@LCL"<<endl;
		outfile<<"M=D"<<endl;

		outfile<<"@"+funcname<<endl;
		outfile<<"0;JMP"<<endl;
		outfile<<"("+returnLabel+")"<<endl;

		outfile<<endl;

		loop++;
}


void codewriter::writeFunction(string arg1, int arg2){
	outfile<<"//function "<<arg1<<" "<<arg2<<endl;

	stringstream ss;
	ss << loop;
	string index = ss.str();

	funcname = arg1;

	string loopLabel = funcname+".LOOP."+index;
	string endLabel = funcname+".END."+index;


	outfile<<"("+funcname+")"<<endl;
	outfile<<"@"<<arg2<<endl;
	outfile<<"D=A"<<endl;
	outfile<<"@R13"<<endl;
	outfile<<"M=D"<<endl;
	outfile<<"("+loopLabel+")"<<endl;
	outfile<<"@"+endLabel<<endl;
	outfile<<"D;JEQ"<<endl;
	outfile<<"@0"<<endl;
	outfile<<"D=A"<<endl;
	outfile<<"@SP"<<endl;
	outfile<<"A=M"<<endl;
	outfile<<"M=D"<<endl;
	outfile<<"@SP"<<endl;
	outfile<<"M=M+1"<<endl;
	outfile<<"@R13"<<endl;
	outfile<<"MD=M-1"<<endl;
	outfile<<"@"+loopLabel<<endl;
	outfile<<"0;JMP"<<endl;
	outfile<<"("+endLabel+")"<<endl;

	outfile<<endl;

	loop++;

}

void codewriter::writeReturn(){
	outfile<<"//return"<<endl;

	//FRAME = LCL
	outfile<<"@LCL"<<endl;
	outfile<<"D=M"<<endl;
	outfile<<"@R13"<<endl;
	outfile<<"M=D"<<endl;

	//RET = *(FRAME - 5)
	outfile<<"@5"<<endl;
	outfile<<"A=D-A"<<endl;
	outfile<<"D=M"<<endl;
	outfile<<"@R14"<<endl;
	outfile<<"M=D"<<endl;

	//*ARG = pop()
	outfile<<"@SP"<<endl;
	outfile<<"AM=M-1"<<endl;
	outfile<<"D=M"<<endl;
	outfile<<"@ARG"<<endl;
	outfile<<"A=M"<<endl;
	outfile<<"M=D"<<endl;

	//SP = ARG + 1
	//outfile<<"@ARG"<<endl;
	//outfile<<"D=M"<<endl;
	outfile<<"D=A"<<endl;
	outfile<<"@SP"<<endl;
	outfile<<"M=D+1"<<endl;

	//THAT = *(FRAME - 1);//THIS = *(FRAME - 2);ARG = *(FRAME - 3);LCL = *(FRAME - 4)
	for(int i=0; i<4; i++){
		outfile<<"@R13"<<endl;
		outfile<<"AM=M-1"<<endl;
		outfile<<"D=M"<<endl;
		switch(i){
			case(0):
				outfile<<"@THAT"<<endl;
				break;
			case(1):
				outfile<<"@THIS"<<endl;
				break;
			case(2):
				outfile<<"@ARG"<<endl;
				break;
			case(3):
				outfile<<"@LCL"<<endl;
				break;
			default:
				break;
		}
		outfile<<"M=D"<<endl;
	}


	//goto RET
	outfile<<"@R14"<<endl;
	outfile<<"A=M"<<endl;
	outfile<<"0;JMP"<<endl;

	outfile<<endl;
}