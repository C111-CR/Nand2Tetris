// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.


//	a=RAM[0] b=RAM[1]
//	sum = 0
//	while(a-- != 0){
//		sum += b;
//	}
//	RAM[2] = sum


	@R0
	D=M
	@a
	M=D
	
	@R1
	D=M
	@b
	M=D
	
	@sum
	M=0
	
(LOOP)
	@a
	D=M
	@LOAD
	D;JEQ
	
	@b
	D=M
	@sum
	M=M+D
	
	@a
	M=M-1
	
	@LOOP
	0;JMP
	
(LOAD)
	@sum
	D=M
	@R2
	M=D
	
(END)
	@END
	0;JMP

