BINS=	main	parser	codewriter

all:parser codewriter	main

codewriter:codewriter.h
	g++ -c codewriter.cpp -std=c++11

parser: whitespace.h parser.h
	g++ -c parser.cpp -std=c++11

main:
	g++ main.cpp parser.o codewriter.o -o main -std=c++11


clean:
	rm -f $(BINS) *.o *.asm