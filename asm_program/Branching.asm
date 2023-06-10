// Program: Signum.asm
// compute : if R0>0 
//			    R1 = 1;
//			 else 
//				R1 = 0;

	@R0
	D=M
	
	@Positive
	D;JGT
	
	@R1
	M=0
	
	@End
	0;JMP
	
	(Positive)
	@R1
	M=1
	
	(End)
	@End
	0;JMP