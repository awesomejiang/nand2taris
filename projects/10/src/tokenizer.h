#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Tokenizer{
	public:
		Tokenizer();
		Tokenizer(string);
		~Tokenizer();

		bool hasMoreTokens();
		void advance();
		string lookAhead();

		string tokenType();
		string keyWord();
		string symbol();
		bool isOp();
		bool isUnaryOp();
		string identifier();
		int intVal();
		string stringVal();


	private:
		unordered_set<string> keywords;
		vector<string> tokens;
		vector<string>::iterator token;

};


#endif
