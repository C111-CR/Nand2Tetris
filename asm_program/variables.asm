// Program: Flip
// filp the value of RAM[0] and RAM[1]
// usage: 	tmp = R0;
//		  	R0 = R1;
//		  	R1 = tmp;

// system gives a register named tmp
// like R0,R1,R2...
// then put D's value to the tmp register

	@R0
	D=M
	
	@tmp
	M=D		// tmp = R0
	
	@R1
	D=M		
	
	@R0
	M=D		// R0 = R1
	
	@tmp
	D=M
	
	@R1
	M=D		// R1 = tmp
	
(End)
	@End
	0;JMP
	