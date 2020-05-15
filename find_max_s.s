.global find_max_s

@ parameters:
	@ r0: array
	@ r1: length of array

find_max_s: 	
	mov ip, #1	@ ip tracks where we are in the array
	ldr r2,[r0]	@ load first element in array as max

	add r0, r0, #4	@ increment address in memory

loop: 
	cmp ip, r1	@ comparing index in array
	bge end		@ if compare is greater than branch to end

	ldr r3,[r0]	@ load element in array
	
	cmp r3,r2	@ comparing element in array with max

	add ip,ip,#1	@ increment ip
	add r0,r0,#4	@ increment address in memory

	ble loop	@ if comapre is less than or equal to branch to loop

	mov r2,r3	@ set r2 with r3
	
	b loop		@ branch back to loop
end:
	mov r0,r2	@ set r0 with r2
	bx lr		@ return r0
