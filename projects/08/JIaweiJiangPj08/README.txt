Student Name: Jiawei Jiang
Project#: 8


Compilation environment: ubuntu 14, gcc 4.8.4


Compile file:
You can input
1. g++ main.cpp parser.cpp codewriter.cpp -o [out] -std = c++11
or
2. make
in terminal to compile the files and abtain an executable file.


Running:
Input:
./[out] [filename].vm
Prog will generate a file named under directory of [filename].vm, named [filename].asm

or
./[out] [directory]
Prog will generate a file named under [directory] [directory].asm
(ATTENTION: No '/' should be include at last when inputting)


Notes:
1.To read a directory and find all *.vm files, I include <dirent.h> in my main program. So my program may not running correctly in windows PCs.
2.It is said in textbook that every file/directory should have a "Sys.init" function, so my prog will print a wrong when testing "Simplefunction". However, it can work because I parse the files first to check if there is Sys.init function in target file.
3.I assume that all files do not have namesake functions, so I do not add filename to varibles names.
4.I asuume no varibles appears before any functions. It's obvious if there is Sys.init in file.