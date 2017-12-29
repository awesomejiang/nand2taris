#ifndef COMPILATIONENGINE_H
#define COMPILATIONENGINE_H

#include <string>
#include <unordered_map>

#include "tokenizer.h"
#include "vmwriter.h"
#include "symboltable.h"

using namespace std;

class CompilationEngine{
	public:
		CompilationEngine(string);
		~CompilationEngine();

		void compileClass();
		void compileClassVarDec();
		void compileSubroutine();
		void compileParameterList();
		void compileVarDec();
		void compileStatements();
		void compileDo();
		void compileLet();
		void compileWhile();
		void compileReturn();
		void compileIf();
		void compileSubroutineCall();
		void compileExpression();
		void compileTerm();
		void compileExpressionList();

	private:
		Tokenizer t;
		VMWriter v;
		SymbolTable s;

		string className;
		string methodName;
		string subroutineName;
		string subroutineKind;
		string subroutineType;
		int args;
		int label = 0;

		string whichOp();
		string whichUnaryOp();

};


#endif