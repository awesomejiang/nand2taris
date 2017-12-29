#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <iostream>

#include "whitespace.h"
#include "tokenizer.h"

using namespace std;


Tokenizer::Tokenizer(){}


Tokenizer::Tokenizer(string in_str){
	//delete comments, blanks and put codes into 1 string.
	string inStream = stripWhiteSpace(in_str+".jack", 0 , 1);

	//build a set for keywords
	keywords.insert({"class", "constructor", "function", 
		"method", "field", "static", "var", "int", "char", 
		"boolean", "void", "true", "false", "null", "this", 
		"let", "do", "if", "else", "while", "return"});
	

	stringstream ss(inStream);
	string s;
	size_t found;
	while(ss >> s){
		while(!s.empty()){
			if(s[0] == '\"'){
				found = s.find("\"", 1, s.size());
				if(found != string::npos){
					tokens.push_back( s.substr(0, found+1) );
					s.erase(0, found+1);
				}
				else{
					char tmp[512];
					ss.getline(tmp, 512, '\"');

					tokens.push_back(s+tmp+"\"");

					if(!(ss >> s))
						break;
				}
			}

			found = s.find_first_of("{}()[].,;+-*/&|<>=~");
			if(found != string::npos){
				found = (found>0)?found:1;
				tokens.push_back( s.substr(0, found) );
				s.erase(0, found);
			}
			else{
				tokens.push_back(s);
				break;
			}
		}
	}

	token = tokens.begin() - 1;
}


Tokenizer::~Tokenizer(){}


bool Tokenizer::hasMoreTokens(){

	return token + 1 != tokens.end();
}


void Tokenizer::advance(){
	if(hasMoreTokens())
		token++;
	else
		cout<<"Error in Tokenizer::advance(): called when hasMoreTokens() is false."<<endl;
}


string Tokenizer::lookAhead(){

	return *(token+1);
}

string Tokenizer::tokenType(){
	if((*token).find("\"") != string::npos)
		return "STRING_CONST";
	if((*token).find_first_of("0123456789") == 0)
		return "INT_CONST";
	if((*token).find_first_of("{}()[].,;+-/*&|<>=~") == 0)
		return "SYMBOL";
	if(keywords.find((*token)) != keywords.end())
		return "KEYWORD";
	else
		return "IDENTIFIER";
}


string Tokenizer::keyWord(){

	return *token;
}


string Tokenizer::symbol(){
	if(*token == "<")
		return "&lt;";
	if(*token == ">")
		return "&gt;";
	if(*token == "&")
		return "&amp;";

	return *token;
}


bool Tokenizer::isOp(){

	return (*token).find_first_of("+-*/&|<>=") != string::npos;
}


bool Tokenizer::isUnaryOp(){

	return (*token).find_first_of("-~") != string::npos;
}


string Tokenizer::identifier(){

	return (*token);
}


int Tokenizer::intVal(){
	stringstream ss((*token));
	int i;
	ss >> i;

	return i;
}


string Tokenizer::stringVal(){

	return (*token).substr(1, (*token).size()-2);
}
