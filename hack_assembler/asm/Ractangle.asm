// Program function: draw a rectangle n*16 from (0,0)
//	n = RAM[0]


	@SCREEN
	D=A
	@address
	M=D
	
	@R0
	D=M
	@n
	M=D
	
	
(loop)
	@n
	D=M
	@End
	D;JEQ
	
	@address
	A=M
	M=-1
	
	@32
	D=A
	@address
	M=M+D
	
	@n
	M=M-1
	
	@loop
	0;JMP
	
	
(End)
	@End
	0;JMP
	