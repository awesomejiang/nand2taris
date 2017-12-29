#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

using namespace std;


class SymbolTable {
public:
	SymbolTable();
	~SymbolTable();
	void startSubroutine();
	void define(string, string, string);
	int varCount(string);
	string kindOf(string);
	string typeOf(string);
	int indexOf(string);


private:
	unordered_map<string, pair<string, int> > staticTable;
	unordered_map<string, pair<string, int> > fieldTable;
	unordered_map<string, pair<string, int> > argumentTable;
	unordered_map<string, pair<string, int> > varibleTable;

	string findingName;
	void print();

};



#endif