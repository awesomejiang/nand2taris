#include <string>
#include <unordered_map>

using namespace std;

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

class symboltable{

public:
	unordered_map<string, int> M;

	symboltable();
	~symboltable();

	void addEntry(string, int);
	bool contains(string);
	int GetAddress(string);

};

symboltable::symboltable(){
	unordered_map<string, int> T = {
		{"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3}, 
		{"THAT", 4}, {"R0", 0}, {"R1", 1}, {"R2",2}, 
		{"R3", 3}, {"R4", 4}, {"R5", 5}, {"R6", 6}, 
		{"R7", 7}, {"R8", 8}, {"R9", 9}, {"R10", 10}, 
		{"R11", 11}, {"R12", 12}, {"R13", 13}, {"R14", 14}, 
		{"R15", 15}, {"SCREEN", 16384}, {"KBD", 24576} 
	};

	M = T;
}

symboltable::~symboltable(){}

void symboltable::addEntry(string symbol, int address){
	if(contains(symbol))
		cout<<"Error in symboltable::addEntry: already have symbol in table"<<endl;
	else{
		M[symbol] = address;	
	}
}

bool symboltable::contains(string symbol){

	return M.find(symbol) != M.end();
}

int symboltable::GetAddress(string symbol){
	if(contains(symbol))
		return M[symbol];
	else{
		cout<<"Error in symboltable::GetAddress: no symbol in table"<<endl;
		return 1;
	}
}


#endif