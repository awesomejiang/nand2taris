#include "jackcompiler.h"

int main(int argv, char** argc){
	JackCompiler J(argc[1]);
	J.run();

	return 0;
}