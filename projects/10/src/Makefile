BINS=	main	tokenizer	compilationengine	analyzer

all:tokenizer	compilationengine	analyzer	main

tokenizer: whitespace.h tokenizer.h tokenizer.cpp
	g++ -c tokenizer.cpp -std=c++11

compilationengine: compilationengine.h compilationengine.cpp
	g++ -c compilationengine.cpp -std=c++11

analyzer: analyzer.h analyzer.cpp
	g++ -c analyzer.cpp -std=c++11

main: main.cpp analyzer.o compilationengine.o tokenizer.o
	g++ -c main.cpp -std=c++11
	g++ tokenizer.o compilationengine.o analyzer.o main.o -o main -std=c++11


clean:
	rm -f $(BINS) *.o *.xml *.log