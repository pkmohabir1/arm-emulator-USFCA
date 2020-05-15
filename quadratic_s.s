.global quadratic_s

@ parameters:
	@ r0 = x
	@ r1 = a
	@ r2 = b
	@ r3 = c




quadratic_s:
	mov r4,r0	@ set r4 to r0 to keep x

	mul r4,r0,r0	@ r4 = x*x
	mul r4, r1,r4	@ r4 = (x*x)*a
	mul r2,r0,r2	@ r2 = b*x
	
	add r4,r2,r4	@ r4 = (a*(x*x))+(b*x)
	add r4,r3,r4	@ r4 = (a*(x*x))+(b*x)+c
	mov r0,r4	@ r0 = r4
	bx lr		@ return r0
