#include <dirent.h>
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include "jackcompiler.h"
#include "compilationengine.h"

using namespace std;

JackCompiler::JackCompiler(string in_str){
	size_t found = in_str.find(".jack");
	if(found != string::npos){
		in_str.erase(in_str.begin()+found, in_str.end());
		files.push_back(in_str);
	}
	else{
		string file;
		DIR *dp;
		struct dirent *dirp;
		
		if(( dp = opendir(in_str.c_str()) ) == NULL){
	    	cout<<"Error when trying to open directory!"<<endl;
	    	exit(1);
	    }

		while( (dirp = readdir(dp)) ){
			file = in_str + "/" + dirp->d_name;
			found = file.find(".jack");

			if(found != string::npos){
				file.erase(file.begin()+found, file.end());
				files.push_back(file);
			}
		}
		closedir(dp);
	}
}


JackCompiler::~JackCompiler(){}


void JackCompiler::run(){
	for(auto file: files){
		//compile it into xml file
		CompilationEngine c(file);
		c.compileClass();
	}
}