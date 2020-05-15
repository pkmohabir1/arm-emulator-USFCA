.global strlen_s

@ parameters:
	@ r0: string array

strlen_s:
	mov ip, #0	@ ip tracks iterations & str len 

loop:
	
	ldrb r2,[r0]	@ grabbing element in array

	cmp r2,#0 	@ comparing loaded element with 0
	beq end		@ if compare equals branch to end

	add ip,ip,#1	@ increment ip
	add r0,r0,#1	@ increment to next element's memory address 

	b loop		@ branch to loop
	
end:
	mov r0,ip	@ set return value with ip
	bx lr		@ return r0
