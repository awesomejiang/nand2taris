//init
@256
D=A
@SP
M=D
//call Sys.init 0
@Sys.Sys.init&return.0
D=A
@SP
M=M+1
A=M-1
M=D
@LCL
D=M
@SP
M=M+1
A=M-1
M=D
@ARG
D=M
@SP
M=M+1
A=M-1
M=D
@THIS
D=M
@SP
M=M+1
A=M-1
M=D
@THAT
D=M
@SP
M=M+1
A=M-1
M=D
@SP
D=M
@5
D=D-A
@0
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
(Sys.Sys.init&return.0)


//function Sys.init 0
(Sys.init)
@0
D=A
(Sys.Sys.init.LOOP.0)
@Sys.Sys.init.END.0
D;JLE
@SP
M=M+1
A=M-1
M=0
D=D-1
@Sys.Sys.init.LOOP.0
0;JMP
(Sys.Sys.init.END.0)

//push constant 4000
@4000
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop pointer 0
@0
D=A
@THIS
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//push constant 5000
@5000
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop pointer 1
@1
D=A
@THIS
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//call Sys.main 0
@Sys.Sys.main&return.5
D=A
@SP
M=M+1
A=M-1
M=D
@LCL
D=M
@SP
M=M+1
A=M-1
M=D
@ARG
D=M
@SP
M=M+1
A=M-1
M=D
@THIS
D=M
@SP
M=M+1
A=M-1
M=D
@THAT
D=M
@SP
M=M+1
A=M-1
M=D
@SP
D=M
@5
D=D-A
@0
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.main
0;JMP
(Sys.Sys.main&return.5)

//pop temp 1
@1
D=A
@frame
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//label LOOP
(Sys.Sys.main$LOOP.7)

//goto LOOP
@Sys.Sys.main$LOOP
0;JMP

//function Sys.main 5
(Sys.main)
@5
D=A
(Sys.Sys.main.LOOP.7)
@Sys.Sys.main.END.7
D;JLE
@SP
M=M+1
A=M-1
M=0
D=D-1
@Sys.Sys.main.LOOP.7
0;JMP
(Sys.Sys.main.END.7)

//push constant 4001
@4001
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop pointer 0
@0
D=A
@THIS
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//push constant 5001
@5001
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop pointer 1
@1
D=A
@THIS
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//push constant 200
@200
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop local 1
@1
D=A
@LCL
D=M+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//push constant 40
@40
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop local 2
@2
D=A
@LCL
D=M+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//push constant 6
@6
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop local 3
@3
D=A
@LCL
D=M+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//push constant 123
@123
D=A
@SP
A=M
M=D
@SP
M=M+1

//call Sys.add12 1
@Sys.Sys.add12&return.19
D=A
@SP
M=M+1
A=M-1
M=D
@LCL
D=M
@SP
M=M+1
A=M-1
M=D
@ARG
D=M
@SP
M=M+1
A=M-1
M=D
@THIS
D=M
@SP
M=M+1
A=M-1
M=D
@THAT
D=M
@SP
M=M+1
A=M-1
M=D
@SP
D=M
@5
D=D-A
@1
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.add12
0;JMP
(Sys.Sys.add12&return.19)

//pop temp 0
@0
D=A
@frame
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//push local 0
@0
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

//push local 1
@1
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

//push local 2
@2
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

//push local 3
@3
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

//push local 4
@4
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

//add
@SP
AM=M-1
D=M
A=A-1
M=M+D

//add
@SP
AM=M-1
D=M
A=A-1
M=M+D

//add
@SP
AM=M-1
D=M
A=A-1
M=M+D

//add
@SP
AM=M-1
D=M
A=A-1
M=M+D

//return
@LCL
D=M
@frame
M=D
@5
AD=D-A
D=M
@ret
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
D=A
@SP
M=D+1
@frame
MD=M-1
A=D
D=M
@THAT
M=D
@frame
MD=M-1
A=D
D=M
@THIS
M=D
@frame
MD=M-1
A=D
D=M
@ARG
M=D
@frame
MD=M-1
A=D
D=M
@LCL
M=D
@ret
A=M
0;JMP

//function Sys.add12 0
(Sys.add12)
@0
D=A
(Sys.Sys.add12.LOOP.30)
@Sys.Sys.add12.END.30
D;JLE
@SP
M=M+1
A=M-1
M=0
D=D-1
@Sys.Sys.add12.LOOP.30
0;JMP
(Sys.Sys.add12.END.30)

//push constant 4002
@4002
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop pointer 0
@0
D=A
@THIS
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//push constant 5002
@5002
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop pointer 1
@1
D=A
@THIS
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

//push argument 0
@0
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

//push constant 12
@12
D=A
@SP
A=M
M=D
@SP
M=M+1

//add
@SP
AM=M-1
D=M
A=A-1
M=M+D

//return
@LCL
D=M
@frame
M=D
@5
AD=D-A
D=M
@ret
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
D=A
@SP
M=D+1
@frame
MD=M-1
A=D
D=M
@THAT
M=D
@frame
MD=M-1
A=D
D=M
@THIS
M=D
@frame
MD=M-1
A=D
D=M
@ARG
M=D
@frame
MD=M-1
A=D
D=M
@LCL
M=D
@ret
A=M
0;JMP

