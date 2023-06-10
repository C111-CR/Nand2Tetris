// Program: Sum from 1 to n 
// compute: RAM[1] = 1+2+3+...+RAM[0]

// set i,n,sum
// usage:	n=RAM[0] i=0 sum=0
//			loop:	i>n jmp to Stop
//					i = i+1
//					sum = sum + i
//					jmp to loop
					
//			Stop:	RAM[1] = sum

	@R0
	D=M
	
	@n
	M=D		// n = RAM[0]
	
	@i
	M=0		// i = 0
	
	@sum
	M=0		// sum = 0
	
(loop)
	@i
	M=M+1
	D=M
	
	@n
	D=D-M	// D = i-n
	
	@Stop
	D;JGT	// if D>0(i>n) then jmp to Stop
	
	
	@i
	D=M
	
	@sum
	M=M+D
	
	@loop
	0;JMP
	
(Stop)
	@sum
	D=M
	
	@R1
	M=D
	
(End)
	@End
	0;JMP