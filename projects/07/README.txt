Student Name: Jiawei Jiang
Project#: 7


Compilation environment: ubuntu 14, gcc 8.4


Compile file:
You can input
1. g++ main.cpp parser.cpp codewriter.cpp -o [out] -std = c++11
or
2. make
in terminal to compile the files and abtain an executable file.


Running:
Input:
./[out] [filename].vm
or
./[out] [directory]
Prog will generate a file named [filename].asm/[directory].asm


Notes:
To read a directory and find all *.vm files, I include <dirent.h> in my main program. So my program may not running correctly in windows PCs.
However, I test it in both linux and mac system, it works well and passes all test case.