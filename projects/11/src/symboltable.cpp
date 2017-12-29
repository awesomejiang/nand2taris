#include <unordered_map>
#include <iostream>

#include "symboltable.h"

SymbolTable::SymbolTable(){}

SymbolTable::~SymbolTable(){}


void SymbolTable::startSubroutine(){
	argumentTable.clear();
	varibleTable.clear();
}


void SymbolTable::define(string name, string type, string kind){
	if(kind == "static"){
		pair<string, int> p = {type, staticTable.size()};
		staticTable.insert({name, p});
	}
	if(kind == "field"){
		pair<string, int> p = {type, fieldTable.size()};
		fieldTable.insert({name, p});
	}
	if(kind == "arg"){
		pair<string, int> p = {type, argumentTable.size()};
		argumentTable.insert({name, p});
	}
	if(kind == "var"){
		pair<string, int> p = {type, varibleTable.size()};
		varibleTable.insert({name, p});
	}
}

void SymbolTable::print(){
	cout<<"static:"<<endl;
	for(auto i: staticTable){
		cout<<i.first<<"\t"<<i.second.first<<"\t"<<i.second.second<<endl;
	}
	cout<<"\nfield:"<<endl;
	for(auto i: fieldTable){
		cout<<i.first<<"\t"<<i.second.first<<"\t"<<i.second.second<<endl;
	}
	cout<<"\nargument:"<<endl;
	for(auto i: argumentTable){
		cout<<i.first<<"\t"<<i.second.first<<"\t"<<i.second.second<<endl;
	}
	cout<<"\nvarible:"<<endl;
	for(auto i: varibleTable){
		cout<<i.first<<"\t"<<i.second.first<<"\t"<<i.second.second<<endl;
	}
}

int SymbolTable::varCount(string kind){
	if(kind == "static"){
		return staticTable.size();
	}
	if(kind == "field"){
		return fieldTable.size();
	}
	if(kind == "arg"){
		return argumentTable.size();
	}
	if(kind == "var"){
		return varibleTable.size();
	}

	cout<<"SymbolTable::VarCount: Input "<<kind<<" is not valid \"kind\"."<<endl;
	exit(1);

}


string SymbolTable::kindOf(string name){
	
	string res;
	if(findingName != name){
		if(varibleTable.find(name) != varibleTable.end()){
			res = "var";
		}
		else{
			if(argumentTable.find(name) != argumentTable.end()){
				res = "arg";
			}
			else{
				res = "none";
				findingName = name;
			}
		}
	}
	else{
		if(staticTable.find(name) != staticTable.end()){
		res = "static";
		}
		else{
			if(fieldTable.find(name) != fieldTable.end()){
				res = "field";
			}
			else{
				res = "none";
			}
		}
		findingName = "";
	}

	return res;
	/*
	if(varibleTable.find(name) != varibleTable.end()){
		return "var";
	}
	if(argumentTable.find(name) != argumentTable.end()){
		return "arg";
	}
	if(staticTable.find(name) != staticTable.end()){
		return "static";
	}
	if(fieldTable.find(name) != fieldTable.end()){
		return "field";
	}

	return "none";
	*/
}


string SymbolTable::typeOf(string name){
	if(varibleTable.find(name) != varibleTable.end()){
		return varibleTable[name].first;
	}
	if(argumentTable.find(name) != argumentTable.end()){
		return argumentTable[name].first;
	}
	if(staticTable.find(name) != staticTable.end()){
		return staticTable[name].first;
	}
	if(fieldTable.find(name) != fieldTable.end()){
		return fieldTable[name].first;
	}

	//prog should not run at here.
	cout<<"SymbolTable::typeOf: do not find "<<name<<" in current symboltable."<<endl;
	exit(1);
}


int SymbolTable::indexOf(string name){
	unordered_map<string, pair<string, int> >::iterator found;

	if((found = varibleTable.find(name)) != varibleTable.end()){
		return (found->second).second;
	}
	if((found = argumentTable.find(name)) != argumentTable.end()){
		return (found->second).second;
	}
	if((found = staticTable.find(name)) != staticTable.end()){
		return (found->second).second;
	}
	if((found = fieldTable.find(name)) != fieldTable.end()){
		return (found->second).second;
	}	

	//prog should not run at here.
	cout<<"SymbolTable::indexOf: do not find "<<name<<" in current symboltable."<<endl;
	exit(1);
}