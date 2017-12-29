How To Compile:

For windows OS:
Compile with your ide. Remember to add whitespace.h as neccessary head file.

For unix OS(e.g. mac/Linux):
1. Compile directly with terminal. Specific command varys based on what compiler you choose. 
2. Take g++ as an example. Input "make" in your terminal to get a executable file named "main". Input "make clean" to clean compilation results.
*** If you want to compile it yourself for different settings, you can input "g++ main.cpp -o [filename]" in your terminal to create an executable file named [filename].



How To Run The Code:

Once you compile the code and get your executable file, you can input "./[yourfilename] [inputfilename] (no-comments)" to running the programme. You will see a new file end with a ".out" in the same directory of your input file.
*** [inputfilename] is neccessary and the filename have to end with ".in", or you will meet an error.
*** Input the parameter "no-comments" decides whether the programme deletes comments in input file or not.



Where Can The Code Work:

Since the programme only uses basic C++ libraries, the programme will work well if you have basic c++ compiling environment in your computer!
*** If you are interested in source code, see src/main.cpp, src/whitespace.h and src/document.txt