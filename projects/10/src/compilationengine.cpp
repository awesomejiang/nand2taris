#include <string>
#include <fstream>
#include <iostream>

#include "tokenizer.h"
#include "compilationengine.h"

using namespace std;

CompilationEngine::CompilationEngine(string infile) : t(infile){

	outfile.open((infile+".xml").c_str());
}


CompilationEngine::~CompilationEngine(){}


void CompilationEngine::print(){
	if(t.tokenType() == "KEYWORD")
		outfile<<"<keyword> "<<t.keyWord()<<" </keyword>"<<endl;
	if(t.tokenType() == "IDENTIFIER")
		outfile<<"<identifier> "<<t.identifier()<<" </identifier>"<<endl;
	if(t.tokenType() == "SYMBOL")
		outfile<<"<symbol> "<<t.symbol()<<" </symbol>"<<endl;
	if(t.tokenType() == "STRING_CONST")
		outfile<<"<stringConstant> "
		<<t.stringVal()<<" </stringConstant>"<<endl;
	if(t.tokenType() == "INT_CONST")
		outfile<<"<integerConstant> "
		<<t.intVal()<<" </integerConstant>"<<endl;

	//move token to next
	t.advance();
}


//class A{}
void CompilationEngine::compileClass(){
	outfile<<"<class>"<<endl;

	//print class A {
	t.advance();
	print();
	print();
	print();

	//calssvardecs and subroutines
	while(t.tokenType() == "KEYWORD")
		if(t.keyWord() == "field" || t.keyWord() == "static")
			while(t.keyWord() == "field" || t.keyWord() == "static")
				compileClassVarDec();
		else
			while(t.tokenType() == "KEYWORD")
				compileSubroutine();

	//print }
	outfile<<"<symbol> "<<t.symbol()<<" </symbol>"<<endl;

	outfile<<"</class>"<<endl;
}

//filed int a, int b;
void CompilationEngine::compileClassVarDec(){
	outfile<<"<classVarDec>"<<endl;

	//print until ;
	while(t.tokenType() != "SYMBOL" || t.symbol() != ";")
		print();

	//print ;
	print();
	
	outfile<<"</classVarDec>"<<endl;
}


//method int foo(...){...}
void CompilationEngine::compileSubroutine(){
	outfile<<"<subroutineDec>"<<endl;

	//print method int foo(
	print();
	print();
	print();
	print();

	//parameterList
	compileParameterList();

	//print )
	print();

	outfile<<"<subroutineBody>"<<endl;

	//{
	print();

	//VarDecs and statements
	while(t.tokenType() == "KEYWORD")
		if(t.keyWord() == "var" || t.keyWord() == "local")
			while(t.keyWord() == "var" || t.keyWord() == "local")
				compileVarDec();
		else
			compileStatements();

	//print }
	print();

	outfile<<"</subroutineBody>"<<endl;
	outfile<<"</subroutineDec>"<<endl;

}


//int a, Array b
void CompilationEngine::compileParameterList(){
	outfile<<"<parameterList>"<<endl;

	//print until )
	while(t.tokenType() != "SYMBOL" || t.symbol() != ")")
		print();

	outfile<<"</parameterList>"<<endl;
}


//var int a, int b;
void CompilationEngine::compileVarDec(){
	outfile<<"<varDec>"<<endl;

	//print until ;
	while(t.tokenType() != "SYMBOL" || t.symbol() != ";")
		print();

	//print ;
	print();
	
	outfile<<"</varDec>"<<endl;
}


void CompilationEngine::compileStatements(){
	outfile<<"<statements>"<<endl;

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

	outfile<<"</statements>"<<endl;
}

//do foo();
void CompilationEngine::compileDo(){
	outfile<<"<doStatement>"<<endl;

	//print do
	print();

	//subroutineCall
	compileSubroutineCall();

	//print ;
	print();

	outfile<<"</doStatement>"<<endl;
}


void CompilationEngine::compileSubroutineCall(){
	//print until (
	while(t.tokenType() != "SYMBOL" || t.symbol() != "(")
		print();

	//print (
	print();

	//expressionlist?
	compileExpressionList();

	//print )
	print();
}


void CompilationEngine::compileLet(){
	outfile<<"<letStatement>"<<endl;

	//print let varName
	print();
	print();

	//[...]?
	if(t.tokenType() == "SYMBOL" && t.symbol() == "["){
		print();
		compileExpression();
		print();
	}

	//print = expression ;
	print();
	compileExpression();
	print();

	outfile<<"</letStatement>"<<endl;
}


void CompilationEngine::compileWhile(){
	outfile<<"<whileStatement>"<<endl;

	//print while ( expression ) { statements }
	print();
	print();
	compileExpression();
	print();
	print();
	compileStatements();
	print();

	outfile<<"</whileStatement>"<<endl;
}


void CompilationEngine::compileReturn(){
	outfile<<"<returnStatement>"<<endl;

	//print return
	print();

	//expression?
	if(t.tokenType() != "SYMBOL" || t.symbol() != ";")
		compileExpression();

	//print ;
	print();

	outfile<<"</returnStatement>"<<endl;
}


void CompilationEngine::compileIf(){
	outfile<<"<ifStatement>"<<endl;

	//print if ( expression ) { statements }
	print();
	print();
	compileExpression();
	print();
	print();
	compileStatements();
	print();

	//else?
	if(t.tokenType() == "KEYWORD" && t.keyWord() == "else"){
		//print else { statements }
		print();
		print();
		compileStatements();
		print();
	}

	outfile<<"</ifStatement>"<<endl;
}


//term (op term)*
void CompilationEngine::compileExpression(){
	outfile<<"<expression>"<<endl;

	//term
	compileTerm();

	//op term?
	while(t.tokenType() == "SYMBOL" && t.isOp()){
		print();
		compileTerm();
	}

	outfile<<"</expression>"<<endl;
}


void CompilationEngine::compileTerm(){
	outfile<<"<term>"<<endl;

	if(t.tokenType() != "IDENTIFIER"){
		if(t.tokenType() == "SYMBOL"){
			//-/~ term
			if(t.isUnaryOp()){
				print();
				compileTerm();
			}
			else{
				//( expression )
				if(t.symbol() == "("){
					print();
					compileExpression();
					print();
				}
			}
		}
		else
			print();
	}
	else{
		//peek next token
		//varName [ expression ]
		if(t.lookAhead() == "["){
			print();
			print();
			compileExpression();
			print();
		}
		else{
			//subroutineCall
			if(t.lookAhead() == "(" || t.lookAhead() == ".")
				compileSubroutineCall();
			else
				print();
		}
	}

	outfile<<"</term>"<<endl;
}


//only appears in subroutineCall, enclosed by ()
void CompilationEngine::compileExpressionList(){
	outfile<<"<expressionList>"<<endl;

	if(t.tokenType() != "SYMBOL" || t.symbol() != ")"){
		compileExpression();
		while(t.tokenType() != "SYMBOL" || t.symbol() != ")"){
			//print , expression
			print();
			compileExpression();
		}
	}

	outfile<<"</expressionList>"<<endl;
}


//close output file
void CompilationEngine::compileClose(){

	outfile.close();
}