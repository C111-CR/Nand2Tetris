//for(int i=m;i<n;i++){
//	arr[i] = -1;
//}

//arr -> some memories
//m=RAM[0] n=RAM[1]


	@100
	D=A

	@arr
	M=D
	//arr start from No.100 register
	
	@R0
	D=M
	
	@i
	M=D
	
	@R1
	D=M
	
	@n
	M=D
	
(loop)
	@i
	D=M
	
	@n
	D=D-M
	//Now D is equal to (i-n)
	
	
	@End
	D;JEQ
	//if i>=n(D>0) -> stop
	
	
	@i
	D=M
	
	@arr
	A=D+M
	M=-1
	//set arr[i] = -1
	
	
	@i
	M=M+1
	//i++
	
	
	@loop
	0;JMP
	
(End)
	@End
	0;JMP
	
	
	