.global fib_iter_s

@parameters : 
	@ r0 = n
fib_iter_s:
	cmp r0,#0	@ n == 0
	beq endif	@ return if 0

	mov r1, #0	@ prev_prev_num
	mov r2, #0	@ prev_num
	mov r3, #1	@ curr_num
	mov r4, #1	@ int i
	
loop:
	cmp r4,r0	@ i==n return
	beq end		@ return curr_num

	mov r1, r2	@ pre_prev_num = prev_num
	mov r2, r3	@ prev_num = curr_num

	add r3, r1,r2	@ curr_num = prev_prev_num + prev_num
	add r4,r4, #1	@ i++ 
	
	bne loop	@ loop
	mov r0,r4	@ if we don't take the branch fall through r0=curr_num
end:
	mov r0,r3	@ set return value to r3
	bx lr		@ return r0
endif:
	bx lr		@ return r0
