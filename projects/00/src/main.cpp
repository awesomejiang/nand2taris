#include <iostream>
#include "whitespace.h"

using namespace std;

int main(int argc, char** argv){
	string in_str = argv[1];

	if(argc == 3){
		string tmp = (string)argv[2];
		if(tmp.size()==11 && tmp.compare("no-comments")==0 ){
			stripWhiteSpace(in_str, 1);
			return 0;
		}
	}

	if(argc == 2){
		stripWhiteSpace(in_str, 0);
		return 0;
	}
	
	cout<<"Invalid parameters. Please try again!"<<endl;

}