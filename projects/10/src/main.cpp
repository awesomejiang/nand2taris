#include <iostream>
#include "analyzer.h"

using namespace std;

int main(int argv, char** argc){
	Analyzer A(argc[1]);
	A.run();

	return 0;
}