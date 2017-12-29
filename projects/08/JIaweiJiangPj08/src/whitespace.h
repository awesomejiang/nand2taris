#ifndef WHITESPACE_H
#define WHITESPACE_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<vector>


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
	if(line.find_first_not_of(" \t\r\n") != string::npos){
		stringstream ss(line);
		string s;

		while(ss >> s)
			res += s;
	}

	return res;
}

vector<string> stripWhiteSpace(string filename, int strip, int comment){
	vector<string> res;
	
	fstream file;
	file.open(filename.c_str());

	string line;
	while(getline(file, line)){
		if(strip == 1)
			line = deleteBlank(line);
		if(comment == 1)
			line = deleteComments(line);
		if(/*line.empty() != 0 &&*/ line.find_first_not_of(" \t") != string::npos)
			res.push_back(line);
	}

	file.close();

	return res;
}

#endif