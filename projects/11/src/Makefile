BINS=	main	tokenizer	compilationengine	jackcompiler	vmwriter	symboltable

all:tokenizer	compilationengine	jackcompiler	vmwriter	symboltable	main

tokenizer: whitespace.h tokenizer.h tokenizer.cpp
	g++ -c tokenizer.cpp -std=c++11

vmwriter: vmwriter.h vmwriter.cpp
	g++ -c vmwriter.cpp -std=c++11

symboltable: symboltable.h symboltable.cpp
	g++ -c symboltable.cpp -std=c++11

compilationengine: compilationengine.h compilationengine.cpp
	g++ -c compilationengine.cpp -std=c++11

jackcompiler: jackcompiler.h jackcompiler.cpp
	g++ -c jackcompiler.cpp -std=c++11

main: main.cpp symboltable.o vmwriter.o jackcompiler.o compilationengine.o tokenizer.o
	g++ -c main.cpp -std=c++11
	g++ symboltable.o vmwriter.o tokenizer.o compilationengine.o jackcompiler.o main.o -o main -std=c++11


clean:
	rm -f $(BINS) *.o *.vm *.log