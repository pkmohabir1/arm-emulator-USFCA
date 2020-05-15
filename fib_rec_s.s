.global fib_rec_s

@ parameter:
	@r0 = n

fib_rec_s:
	sub sp,sp,#16		@ allocating space on stack
	
	cmp r0, #0  		@ if equals zero base case
	beq zero			@ branch if eqauls to zero

	cmp r0, #1			@ if equals one base case
	beq one				@ branch if equals to one

	b fib_rec			@ branch to fib_rec
	
fib_rec:
	str lr, [sp]		@ store lr at stack pointer
	str r0, [sp, #4]	@ store r0 at (sp+4)
	
	/*n-1*/
	sub r0,r0,#1		@ subtract 1 from r0
	bl fib_rec_s		@ branch link to rec
	mov r2, r0			@ set r2 with r0
	
	str r2, [sp,#8]		@ store r2 at memory address of (sp + 8)
	ldr r0, [sp,#4]		@ load memory at sp+4 at r0
	
	/*n-2*/
	sub r0,r0,#2		@ subtract 2 from r0
	bl fib_rec_s		@ branch link rec
	mov r1,r0			@ set r1 with r0
	str r1, [sp,#12]	@ store r1 at memory address sp+12
	ldr r1, [sp,#12]	@ load memory address sp+12 to r1
	ldr r2,[sp,#8]		@ load memory address sp+8 to r2
	ldr r0, [sp, #4]	@ load memory address sp+4 to r0
	ldr lr, [sp]		@ load memory addess sp to lr
	
	add r3,r1,r2		@ add r1+r2 to r3
	b end				@ branch to end

one: 
	mov r3, #1 			@ set r3 with 1
	b end				@ branch to end
zero:
	mov r3, #0			@ set r3 with 0
	b end				@ branch to end

end:
	mov r0,r3			@ set r0 with r3
	add sp, sp, #16 	@ add 16 to sp
	bx lr				@ return
