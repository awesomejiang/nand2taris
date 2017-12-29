#include <fstream>
#include <string>
#include <iostream>

#include "vmwriter.h"

using namespace std;

VMWriter::VMWriter(string infile){
	outfile.open((infile+".vm").c_str());
}


VMWriter::~VMWriter(){}


void VMWriter::writePush(string segment, int index){
	if(segment == "arg")
		segment = "argument";
	if(segment == "var")
		segment = "local";
	if(segment == "this")
		segment = "pointer";
	if(segment == "field")
		segment = "this";

	outfile<<"push "+segment+" "<<index<<endl;
}


void VMWriter::writePop(string segment, int index){
	if(segment == "arg")
		segment = "argument";
	if(segment == "var")
		segment = "local";
	if(segment == "this")
		segment = "pointer";
	if(segment == "field")
		segment = "this";

	outfile<<"pop "+segment+" "<<index<<endl;
}


void VMWriter::writeArithmetic(string command){
	if(command == "mul"){
		outfile<<"call Math.multiply 2"<<endl;
	}
	else{
		if(command == "div"){
			outfile<<"call Math.divide 2"<<endl;
		}
		else{
			outfile<<command<<endl;
		}
	}
}


void VMWriter::writeLabel(string label){

	outfile<<"label "+label<<endl;
}


void VMWriter::writeGoto(string label){

	outfile<<"goto "+label<<endl;
}


void VMWriter::writeIf(string label){

	outfile<<"if-goto "+label<<endl;
}


void VMWriter::writeCall(string name, int nargs){

	outfile<<"call "+name+" "<<nargs<<endl;
}


void VMWriter::writeFunction(string name, int nvars){

	outfile<<"function "+name+" "<<nvars<<endl;
}


void VMWriter::writeReturn(){

	outfile<<"return"<<endl;
}


void VMWriter::close(){

	outfile.close();
}