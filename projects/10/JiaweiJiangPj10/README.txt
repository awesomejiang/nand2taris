Student Name: Jiawei Jiang
Project#: 10

/****************************************************************************/
									README
/****************************************************************************/
Compilation environment: ubuntu 14, gcc 4.8.4


Compile file:
You can input
1. g++ main.cpp analyzer.cpp compilationengine.cpp tplemozer -o [out] -std = c++11
or
2. make
in terminal to compile the files and abtain an executable file.


Running:
Input:
./[out] [filename].jack
Prog will generate a file under directory of [filename].jack, named [filename].xml

or
./[out] [directory]
Prog will generate corresponding .xml files for all .jack files under [directory].

Notes:
To read a directory and find all *.jack files, I include <dirent.h> in my main program. So my program may not running correctly in windows PCs.


/****************************************************************************/
								Documentation
/****************************************************************************/
This project mainly has 3 classes.

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

1.12 isYbaryOp
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

2.17 compileClose
	Input:	void
	Output:	void
	Close output file.


3. Analyzer

3.1 Constructor
	Input:	void
	Output:	void
	Create file stream.

3.2 run
	Input:	void
	Output:	void
	Create CompilationEngine instances and call CompilationEngine::compileClass() to compile files in file stream one by one.

