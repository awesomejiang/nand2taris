#include "whitespace.h"
#include "parser.h"
#include "code.h"
#include "symboltable.h"
#include <vector>
#include <string>
#include <stdlib.h>

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

using namespace std;

class assembler{
public:
	symboltable S;
	vector<string> Res;

	assembler();
	assembler(string);
	~assembler();

	void firstPass();
	void secondPass();

private:
	string filename;
	string ToBin(int);
};

assembler::assembler(string str){

	filename = str;
}

assembler::~assembler(){}

void assembler::firstPass(){
	parser F(filename);
	int line = 0;
	while(F.hasMoreCommands()){
		F.advance();

		string type = F.commandType();

		if(type != "L_COMMAND")
			line++;
		else{
			string label = *(F.currCommand);
			label = label.substr(1, label.size()-1);
			S.addEntry(label, line+1);
		}
	}
}

void assembler::secondPass(){
	parser F(filename);

	int ram_line = 16;
	while(F.hasMoreCommands()){
		F.advance();

		string type = F.commandType();
		string r;

		if(type == "A_COMMAND"){
			r += "0";
			string s = *(F.currCommand);
			s = s.substr(1);

			int flag = 0;
			for(auto c:s)
				if(c < 48 || c > 57){
					flag++;
					break;
				}

			if(flag == 1){
				if(!S.contains(s))
					S.addEntry(s, ram_line);
				r += ToBin(S.GetAddress(s));
			}
			else{
				r+= ToBin(atoi(s.c_str()));
			}
		}

		if(type == "C_COMMAND"){
			r += "111";

			//comp
			code C(F.comp());
			r += C.comp();

			//dest
			code D(F.dest());
			r += D.dest();

			//jump
			code J(F.jump());
			r += J.jump();
		}

		Res.push_back(r);

	}
}

string assembler::ToBin(int in){
	if(in>65536 || in<0)
		cout<<"Error in assembler::ToBin: Invalid ROM address!"<<endl;

	string out;
	while(in > 0){
		if(in%2) out = '1' + out;
		else out = '0' + out;
		in = in/2;
	}

	while(out.size()<15)
		out = '0' + out;

	return out;
}



#endif