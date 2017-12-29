#include <vector>
#include <string>
#include <fstream>
#include <dirent.h>
#include <iostream>

#include "parser.h"
#include "codewriter.h"

using namespace std; 

vector<string> getFiles(string in){
	vector<string> res;

	string file;
	DIR *dp;
	struct dirent *dirp;

	if(( dp = opendir(in.c_str()) ) == NULL){
    	cout<<"Error when trying to open directory!"<<endl;
    	exit(1);
    }

	while( (dirp = readdir(dp)) ){
		file = in + "/" + dirp->d_name;
		if(file.find(".vm") != string::npos)
			res.push_back(file);
	}
	closedir(dp);

	return res;
}

void Parse(string in){
	vector<string> files;
	string out;
	if(in.find(".vm") != string::npos){
		files.push_back(in);
		out = in.substr(0, in.size()-2) + "asm";
	}
	else{
		files = getFiles(in);
		out = in+".asm";
	}

	codewriter C(out);

	for(auto f: files)
		if(f.find(".vm") != string::npos){
			C.setFileName(f);
			parser P(f);
			while(P.hasMoreCommands()){
				P.advance();
				string type = P.commandType();
				if(type == "C_ARITHMETIC")
					C.writeArithmetic(P.arg1());
				if(type == "C_PUSH")
					C.writePushPop("push", P.arg1(), P.arg2());
				if(type == "C_POP")
					C.writePushPop("pop", P.arg1(), P.arg2());
			}
		}

	C.close();
}



int main(int argv, char** argc){

	string in = argc[1];

	Parse(in);
}
