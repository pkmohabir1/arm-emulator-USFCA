.global sum_arr_s

@ parameters:
	@ r0: array of 32 bit integers
	@ r1: length of array


sum_arr_s: 
	mov r4, #0	@ use ip (aka r12) to loop over the array
	mov r2, #0	@ sum of array
loop:
	cmp r4, r1	@ compare ip with length of array
	beq end		@ if compare equals each other branch to end
	ldr r3, [r0]	@ loads the first integer in array
	
	add r2, r2, r3	@ r2 = r2+r3
	
	add r4, r4, #1	@ increment ip
	add r0, r0, #4	@ shift r0 to next element in array

	b loop		@ branch to loop

end:
	mov r0,r2	@ set return value to r2
	bx lr		@ return r0
