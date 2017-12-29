#include <vector>
#include <string>
#include <fstream>
#include <dirent.h>
#include <iostream>

#include "parser.h"
#include "codewriter.h"

using namespace std; 

vector<string> getFiles(string in){
	string file;
	DIR *dp;
	struct dirent *dirp;
	vector<string> res;
	
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
	if(in.find(".vm") != string::npos)
		files.push_back(in);
	else
		files = getFiles(in);


	//check if there is Sys.init function in tartget files
	int init_flag = 0;
	for(auto f: files){
		parser P(f);
		while(P.hasMoreCommands()){
			P.advance();
			string type = P.commandType();
			if(type == "C_FUNCTION" && P.arg1()=="Sys.init")
				init_flag++;
		}
	}

	//run main prom
	codewriter C(in);

	if(init_flag==1)
		C.writeInit();
	else
		cout<<"Do not find Sys.init function in vm files. DisObey the convention!"<<endl;
	for(auto f: files){
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
			if(type == "C_LABEL")
				C.writeLabel(P.arg1());
			if(type == "C_GOTO")
				C.writeGoto(P.arg1());
			if(type == "C_IF")
				C.writeIf(P.arg1());
			if(type == "C_CALL")
				C.writeCall(P.arg1(), P.arg2());
			if(type == "C_FUNCTION")
				C.writeFunction(P.arg1(), P.arg2());
			if(type == "C_RETURN")
				C.writeReturn();
		}
	}

	C.close();
}



int main(int argv, char** argc){

	string in = argc[1];
	Parse(in);
}
