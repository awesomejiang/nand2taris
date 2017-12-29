#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<vector>

#ifndef WHITESPACE_H
#define WHITESPACE_H

using namespace std;


//delete comments in single line
string deleteComments(string line){
	size_t found = line.find("//");
	if(found != string::npos)
		line.erase(line.begin()+found,line.end());

	return line;
}

string deleteBlank(string line){
	string res;
	if(line.find_first_not_of(" \t") != string::npos){
		stringstream ss(line);
		string s;

		while(ss >> s)
			res += s;
	}

	return res;
}

string stripWhiteSpace_line(string in_str, int comment){
	string res = deleteBlank(in_str);
	if(comment)
		res = deleteComments(res);

	return res;
}

vector<string> stripWhiteSpace(string filename, int comment){
	vector<string> res;
	
	fstream file;
	file.open(filename.c_str());

	string line;
	while(getline(file, line)){
		line = stripWhiteSpace_line(line, comment);
		if(!line.empty())
			res.push_back(line);
	}

	file.close();

	return res;
}

#endif