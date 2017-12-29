#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

#ifndef WHITESPACE_H
#define WHITESPACE_H

using namespace std;


string outPutPath(string in_str){
	int len = in_str.size();
	if(in_str.substr(len-3,len-1) == ".in"){
		in_str.erase(len-2,2);
		return in_str += "out";
	}
	else{
		cout<<"Invalid input file!(input file must end with \".in\""<<endl;
		exit(1);
	}
}

//delete comments in single line
string deleteComments(string line){
	size_t found = line.find("//");
	if(found != string::npos)
		line.erase(line.begin()+found,line.end());
	return line;
}

void deleteBlank(int* flag, string& line, ofstream* out_file){
	if(line.find_first_not_of(" \t\n\r") != string::npos){
		if(*flag == 0) (*flag)++;
		else *out_file<<endl;

		stringstream ss(line);
		string s;

		while(ss>>s){
			*out_file<<s;
		}
	}	
}

//strip all whitespace in in file and write new text into output file.
void stripWhiteSpace(string in_str, int comment){
	//open input file
	ifstream in_file(in_str.c_str());
	if( !in_file ){
		cout<<"fail to open "<<in_str<<endl;
		exit(1);
	}
	//build output file
	string out_str = outPutPath(in_str);
	ofstream out_file(out_str.c_str());

	//read files by line
	string line;
	int flag = 0;
	while(getline(in_file, line)){
		//delete comments if in comment mode
		if(comment)
			line = deleteComments(line);

		deleteBlank(&flag, line, &out_file);
	}

	//close files
	in_file.close();
	out_file.close();

}


#endif