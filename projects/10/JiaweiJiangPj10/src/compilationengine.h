#ifndef COMPILATIONENGINE_H
#define COMPILATIONENGINE_H

#include <string>
#include <fstream>

#include "tokenizer.h"

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

		void compileClose();
	private:
		Tokenizer t;
		ofstream outfile;
		void print();

};


#endif