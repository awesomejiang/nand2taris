Student Name: Jiawei Jiang
Project#: 10

/****************************************************************************/
									README
/****************************************************************************/
Compilation environment: ubuntu 14, gcc 4.8.4


Compile file:
You can input
1. g++ main.cpp jackcompiler.cpp compilationengine.cpp tokenizer.cpp vmwriter.cpp symboltable.cpp main.cpp -o [out] -std = c++11
or
2. make
in terminal to compile the files and abtain an executable file.


Running:
Input:
./[out] [filename].jack
Prog will generate a file under directory of [filename].jack, named [filename].vm

or
./[out] [directory]
Prog will generate corresponding .vm files for all .jack files under [directory].

Notes:
1.If you call OS functions, you have to put "OS.vm"s to the directionary of .jack files.
2.To read a directory and find all *.jack files, I include <dirent.h> in my main program. So my program may not running correctly in windows PCs.



/****************************************************************************/
								Documentation
/****************************************************************************/
This project mainly has 5 classes.

1.Tokenizer

1.1 Constructor
	Input:	string
	Output:	void
	Reading input files and transform it to stream.

1.2 hasMoreTokens
	Input:	void
	Output:	void
	Check if there is more tokens in stream.

1.3 advance
	Input:	void
	Output:	void
	Move token pointer to next one if hasMoreTokens() is true.

1.4 tokenType
	Input:	void
	Output:	void
	The type of current token.

1.5 keyWord
	Input:	void
	Output:	string
1.6 symbol
	Input:	void
	Output:	string
1.7 identifier
	Input:	void
	Output:	string
1.8 intVal
	Input:	void
	Output:	int
1.9 stringVal
	Input:	void
	Output:	string
	Return the value of corresponding token.

1.10 lookAhead
	Input:	void
	Output:	void
	Return the value of next token. Only be called in CompilationEngine.

1.11 isOp
	Input:	void
	Output:	bool
	Check if symbol token is an operator. Only be called in CompilationEngine.

1.12 isUraryOp
	Input:	void
	Output:	bool
	Check if symbol token is an unary operator. Only be called in CompilationEngine.
(1.10~1.12 is helper functions of CompilationEngine class)


2.CompilationEngine

2.1 Constructor
	Input:	void
	Output:	void
	create a Tokenizer instance for parsing and create/open a output file.

2.2~2.16 compileClass
		 compileClassVarDec
		 compileSubroutine
		 compileParameterList
		 compileVarDec
		 compileStatements
		 compileDo
		 compileLet
		 compileWhile
		 compileReturn
		 compileIf
		 compileSubroutineCall
		 compileExpression
		 compileTerm
		 compileExpressionList
	Input:	void
	Output:	void
	Parse corresponding part of tokenizered stream and write result into output file.


3.SymbolTable

3.1 Constructor
	Input:	void
	Output:	void
	Create an empty symbol table for writing symbols.

3.2 startSubroutine
	Input:	void
	Output:	void
	Called when start a new subroutine, clean symbol table of subroutine scope.

3.3 define
	Input: string, string, string
	Output: void
	Add a new entry(name, tpye, kind) into symbol table.

3.4 varCVount
	Input:	string
	Output: int
	Return table size of corresponding symbol table of input kind.

3.5 kindOf
	Input:	string
	Output: string
	Return kind of input symbol. Return value could be field, static, argument, local or none.

3.6 typeOf
	Input:	string
	Output: string
	Return type of input symbol.

3.7indexOf
	Input:	string
	Output: int
	Return index of input symbol.


4. VMWriter

4.1 Constructor
	Input:	string
	Output: void
	Create a output file and prepare to write code into it.

4.2~4.10
	writePush
	Input:	string, int
	Output: void

	writePop
	Input:	string, int
	Output: void
	
	writeArithmetic
	Input:	string
	Output: void
	
	writeLabel
	Input:	string
	Output: void
	
	writeGoto
	Input:	string
	Output: void
	
	writeIf
	Input:	string
	Output: void
	
	writeCall
	Input:	string, int
	Output: void
	
	writeFunction
	Input:	string, int
	Output: void
	
	writeReturn
	Input:	void
	Output: void
	Write corresponding code into outputfile.

4.11 compileClose
	Input:	void
	Output:	void
	Close output file.


5. JackCompiler

5.1 Constructor
	Input:	files
	Output:	void
	Create file stream.

5.2 run
	Input:	void
	Output:	void
	Create CompilationEngine instances and call CompilationEngine::compileClass() to compile files in file stream one by one.