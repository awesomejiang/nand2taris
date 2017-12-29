#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>

#include "tokenizer.h"
#include "symboltable.h"
#include "vmwriter.h"
#include "compilationengine.h"

using namespace std;

CompilationEngine::CompilationEngine(string infile) : t(infile), v(infile){

	cout<<"Compiling "+infile<<endl;
}


CompilationEngine::~CompilationEngine(){}


//class A{}
void CompilationEngine::compileClass(){

	t.advance();
	//class
	t.advance();
	//A
	className = t.identifier();
	t.advance();
	//{
	t.advance();

	//calssvardecs and subroutines
	while(t.tokenType() == "KEYWORD")
		if(t.keyWord() == "field" || t.keyWord() == "static")
			while(t.keyWord() == "field" || t.keyWord() == "static")
				compileClassVarDec();
		else
			while(t.tokenType() == "KEYWORD"){
				label = 0;
				compileSubroutine();
			}

	v.close();
}


//field int a, int b;
void CompilationEngine::compileClassVarDec(){

	//read type name ,/; as a step
	string name, type, kind;
	kind = t.keyWord();
	t.advance();
	if(t.tokenType() == "KEYWORD"){
		type = t.keyWord();
	}
	else{
		type = t.identifier();
	}
	while(t.tokenType() != "SYMBOL" || t.symbol() != ";"){
		t.advance();
		name = t.identifier();
		t.advance();

		s.define(name, type, kind);
	}

	t.advance();
}


//method int foo(...){...}
void CompilationEngine::compileSubroutine(){
	s.startSubroutine();
	//is constructor, function or method?
	subroutineKind = t.identifier();
	if(subroutineKind == "method"){
		s.define("this", className, "arg");
	}

	//method int
	t.advance();
	subroutineType = t.identifier();
	t.advance();
	//foo
	subroutineName = t.identifier();
	t.advance();
	//(
	t.advance();
	//parameterList
	compileParameterList();

	//){
	t.advance();
	t.advance();

	//VarDecs and statements
	if(t.tokenType() == "KEYWORD"){
		if(t.keyWord() == "var" || t.keyWord() == "local")
			while(t.keyWord() == "var" || t.keyWord() == "local")
				compileVarDec();

//s.print();
		//before compile statements, we have to write function command
		v.writeFunction(className+"."+subroutineName, s.varCount("var"));
		if(subroutineKind == "method"){
			v.writePush("arg", 0);
			v.writePop("pointer", 0);
		}
		if(subroutineKind == "constructor"){
			v.writePush("constant", s.varCount("field"));
			v.writeCall("Memory.alloc", 1);
			v.writePop("pointer", 0);
		}
		compileStatements();
	}

	//}
	t.advance();
}


//int a, Array b
void CompilationEngine::compileParameterList(){
	string name, type, kind;
	kind = "arg";
	int flag = 0;
	while(t.tokenType() != "SYMBOL" || t.symbol() != ")"){
		if(flag != 0){
			t.advance();
		}
		if(t.tokenType() == "KEYWORD"){
			type = t.keyWord();
		}
		else{
			type = t.identifier();
		}
		t.advance();
		name = t.identifier();
		t.advance();
		s.define(name, type, kind);

		flag++;
	}
}


//var int a, int b;
void CompilationEngine::compileVarDec(){
	//read type name ,/; as a step
	string name, type, kind;
	kind = "var";	
	t.advance();
	if(t.tokenType() == "KEYWORD"){
		type = t.keyWord();
	}
	else{
		type = t.identifier();
	}
	while(t.tokenType() != "SYMBOL" || t.symbol() != ";"){
		t.advance();
		name = t.identifier();
		t.advance();

		s.define(name, type, kind);
	}

	t.advance();
}


void CompilationEngine::compileStatements(){
	while(t.tokenType() == "KEYWORD"){
		if(t.keyWord() == "do")
			compileDo();
		if(t.keyWord() == "let")
			compileLet();
		if(t.keyWord() == "while")
			compileWhile();
		if(t.keyWord() == "return")
			compileReturn();
		if(t.keyWord() == "if")
			compileIf();
	}
}


//do foo();
void CompilationEngine::compileDo(){
	//do
	t.advance();

	//subroutineCall
	compileSubroutineCall();

	//ignore the return value
	v.writePop("temp", 0);

	//;
	t.advance();
}


void CompilationEngine::compileSubroutineCall(){
	args = 0;

	string name;
	//(xxx).yyy(
	while(t.tokenType() != "SYMBOL" || t.symbol() != "("){
		if(t.tokenType() == "identifier")
			name += t.identifier();
		else
			name += t.symbol();

		t.advance();
	}
	t.advance();

	//if xxx is in symbol table, its a method; or its a function
	int found;
	if((found = name.find(".")) != string::npos){
		string tmp = name.substr(0, found);
		//find in class scope
		string kind = s.kindOf(tmp);
		if(kind == "none"){
			kind = s.kindOf(tmp);
		}
		if(kind != "none"){ //xxx in symbol table , is a method
			//change xxx.yyy to classname.yyy add this as argment 0
			name = s.typeOf(tmp) + name.substr(found, name.size()-found);
			v.writePush(kind, s.indexOf(tmp));
			args++;
		}
	}
	else{
		//dont find ".", is a method of self class
		name = className+"."+name;
		v.writePush("this", 0);
		args++;
	}
	//expressionlist?
	compileExpressionList();
	//)
	t.advance();

	v.writeCall(name, args);
}


void CompilationEngine::compileLet(){
	string name;
	int flag = 0;
	//let varName
	t.advance();
	name = t.identifier();
	t.advance();

	//[...]?
	if(t.tokenType() == "SYMBOL" && t.symbol() == "["){
		//push varName
		string kind = s.kindOf(name);
		if(kind == "none"){
			kind = s.kindOf(name);
			v.writePush(kind, s.indexOf(name));
			if(kind == "none"){
				cout<<"CompilationEngine::compileLet: Error: cann't find name in class."<<endl;
			}
		}
		else{
			v.writePush(kind, s.indexOf(name));
		}
		//[
		t.advance();
		//expression
		compileExpression();
		v.writeArithmetic("add");
		//]
		t.advance();

		flag++;
	}

	//= expression ;
	t.advance();
	compileExpression();
	t.advance();

	//[...]? / string? ->pop to different place
	if(flag == 0){
		string kind = s.kindOf(name);
		if(kind == "none"){
			kind = s.kindOf(name);
		}
		v.writePop(kind, s.indexOf(name));
	}
	else{
		v.writePop("temp", 0);
		v.writePop("pointer", 1);
		v.writePush("temp", 0);
		v.writePop("that", 0);
	}
}


void CompilationEngine::compileWhile(){
	stringstream ss;
	ss << label;

	string l;
	l = ss.str();

	label++;

	//while ( 
	t.advance();
	t.advance();
	//expression 
	v.writeLabel("WHILE_EXP"+l);
	compileExpression();
	v.writeArithmetic("not");
	v.writeIf("WHILE_END"+l); //if-goto
	//) { 
	t.advance();
	t.advance();
	//statements
	compileStatements();
	v.writeGoto("WHILE_EXP"+l);//goto
	//}
	t.advance();
	v.writeLabel("WHILE_END"+l);
}


void CompilationEngine::compileReturn(){
	//return
	t.advance();

	//expression?
	if(t.tokenType() != "SYMBOL" || t.symbol() != ";"){
		if(t.tokenType() == "KEYWORD" && t.keyWord() == "this"){
			v.writePush("pointer", 0);
			t.advance();
		}
		else
			compileExpression();
	}
	else
		v.writePush("constant", 0);

	v.writeReturn();

	//;
	t.advance();
}


void CompilationEngine::compileIf(){
	stringstream ss;
	ss << label;

	string l;
	l = ss.str();

	label++;

	//if ( 
	t.advance();
	t.advance();
	//expression 
	compileExpression();
	v.writeArithmetic("not");
	v.writeIf("IF_FALSE"+l); //if-goto
	//) { 
	t.advance();
	t.advance();
	//statements }
	compileStatements();
	v.writeGoto("IF_END"+l);//goto
	v.writeLabel("IF_FALSE"+l);
	t.advance();

	//else?
	if((t.tokenType() == "KEYWORD") && (t.keyWord() == "else")){
		//else { statements }
		t.advance();
		t.advance();
		compileStatements();
		t.advance();
	}
	v.writeLabel("IF_END"+l);
}


string CompilationEngine::whichOp(){
	if(t.tokenType() != "SYMBOL"){
		cout<<"CompilationEngine::whichOp: Error: tokenType is not symbol."<<endl;
		exit(1);
	}

	string op = t.symbol();
	if(op == "*")
		return "mul";
	if(op == "/")
		return "div";
	if(op == "+")
		return "add";
	if(op == "-")
		return "sub";
	if(op == "=")
		return "eq";
	if(op == "&gt;")
		return "gt";
	if(op == "&lt;")
		return "lt";
	if(op == "&amp;")
		return "and";
	if(op == "|")
		return "or";

	return "";
}


string CompilationEngine::whichUnaryOp(){
	if(t.tokenType() != "SYMBOL"){
		cout<<"CompilationEngine::whichUnaryOp: Error: tokenType is not symbol."<<endl;
		exit(1);
	}

	string op = t.symbol();

	if(op == "-")
		return "neg";
	if(op == "~")
		return "not";

	return "";
}


//term (op term)*
void CompilationEngine::compileExpression(){
	//term
	compileTerm();

	//op term?
	while(t.tokenType() == "SYMBOL" && t.isOp()){
		string op = whichOp();
		t.advance();
		compileTerm();
		v.writeArithmetic(op);
	}
}


void CompilationEngine::compileTerm(){
	if(t.tokenType() != "IDENTIFIER"){
		if(t.tokenType() == "SYMBOL"){
			// -/~ term
			if(t.isUnaryOp()){
				string op = whichUnaryOp();
				t.advance();
				compileTerm();
				v.writeArithmetic(op);
			}
			else{
				//( expression )
				if(t.symbol() == "("){
					t.advance();
					compileExpression();
					t.advance();
				}
			}
		}
		else{
			if(t.tokenType() == "STRING_CONST"){
				string str = t.stringVal();
				v.writePush("constant", str.size());
				v.writeCall("String.new", 1);
				for(auto s: str){
					v.writePush("constant", s);
					v.writeCall("String.appendChar", 2);
				}
			}
			if(t.tokenType() == "INT_CONST"){
				v.writePush("constant", t.intVal());
			}
			if(t.tokenType() == "KEYWORD"){
				//true false null this
				if(t.keyWord() == "true"){
					v.writePush("constant", 1);
					v.writeArithmetic("neg");
				}
				if(t.keyWord() == "false" || t.keyWord() == "null")
					v.writePush("constant", 0);
				if(t.keyWord() == "this")
					v.writePush("this", 0);
			}
			t.advance();
		}
	}
	else{
		//peek next token
		//varName [ expression ]
		if(t.lookAhead() == "["){
			//varName
			string name = t.identifier();
			string kind = s.kindOf(name);
			if(kind == "none"){
				kind = s.kindOf(name);
				v.writePush(kind, s.indexOf(name));
			}
			else{
				v.writePush(kind, s.indexOf(name));
			}
			t.advance();
			//[
			t.advance();
			//expression
			compileExpression();
			v.writeArithmetic("add");
			v.writePop("pointer", 1);
			v.writePush("that", 0);
			//]
			t.advance();

		}
		else{
			//subroutineCall
			if(t.lookAhead() == "(" || t.lookAhead() == ".")
				compileSubroutineCall();
			else{
				string name = t.identifier();
				string kind = s.kindOf(name);
				if(kind == "none"){
					kind = s.kindOf(name);
				}
				v.writePush(kind, s.indexOf(name));
				t.advance();
			}
		}
	}
}


//only appears in subroutineCall, enclosed by ()
void CompilationEngine::compileExpressionList(){
	//update args to record the elements in expressionlist.
	if(t.tokenType() != "SYMBOL" || t.symbol() != ")"){
		compileExpression();
		args++;

		while(t.tokenType() != "SYMBOL" || t.symbol() != ")"){
			// ,expression
			t.advance();
			compileExpression();
			args++;
		}
	}
}