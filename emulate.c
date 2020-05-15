#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "armemu.h"
#include "debug.h"
#include "static_analysis.h"
#include "arm_instructions.h"
#include "emulate.h"

/* Function Prototypes */
int quadratic_s(int, int, int, int);
int sum_arr_s(int*, int n);
int strlen_s(char* arr);
int find_max_s(int*,int);
int fib_iter_s(int);
int fib_rec_s(int);

/* Clear Static Analysis Struct */ 
void clear_stat_analysis(static_analysis* emu_stat){

    emu_stat->instruction_count = 0;
    emu_stat->data_proc_count = 0;
    emu_stat->memory_count = 0;
    emu_stat->branch_taken = 0;
    emu_stat->branch_not_taken = 0;
	emu_stat->cache_hit = 0;
    emu_stat->cache_miss = 0;
}

/* Clear Registers Function*/ 
void clear_regs(emulator* emu){

    for(int i = 0; i<NUM_REGS; i++){
        emu->regs[i] = 0;
    }
    for(int j = 0; j<STACK_SZ; j++){
        emu->stack[j];
    }
    emu->cpsr = 0;

}

/* Emulate Fibonacci Iterative Function */
void emulate_fib_iter(emulator* emu, static_analysis* emu_stat, int n){

	clear_regs(emu);

	clear_stat_analysis(emu_stat);

    emu->regs[0] =  n;

    emu->regs[REG_PC] = (unsigned int) fib_iter_s;
    
    emulate_program(emu, emu_stat);
	
	print_analysis(emu, emu_stat);

}

/* Emulate Fibonacci Recursive Function */
void emulate_fib_rec(emulator* emu, static_analysis* emu_stat, unsigned int n){

	clear_regs(emu);

 	clear_stat_analysis(emu_stat);

  	emu->regs[0] = n;

    emu->regs[REG_PC] = (unsigned int) fib_rec_s;

    emu->regs[REG_SP] = (unsigned int)(&emu->stack[STACK_SZ]);
    
    emulate_program(emu, emu_stat);

	print_analysis(emu, emu_stat);

}

/* Emulate Find Max Function */
void emulate_find_max(emulator* emu, static_analysis* emu_stat, unsigned int arr, int n){

	clear_regs(emu);
	
	clear_stat_analysis(emu_stat);

    emu->regs[0] = arr;

    emu->regs[1] = n;

    emu->regs[REG_PC] = (unsigned int) find_max_s;
    
    emulate_program(emu, emu_stat);

	print_analysis(emu, emu_stat);

}

/* Emulate Sum Array Function */
void emulate_sum_arr(emulator* emu, static_analysis* emu_stat, unsigned int arr, int n){

	clear_regs(emu);

	clear_stat_analysis(emu_stat);

    emu->regs[0] = arr;

    emu->regs[1] = n;

    emu->regs[REG_PC] = (unsigned int) sum_arr_s;
    
    emulate_program(emu, emu_stat);

	print_analysis(emu, emu_stat);

}

/* Emulate String Length Function */
void emulate_strlen(emulator* emu, static_analysis* emu_stat, unsigned char* string){

    clear_regs(emu);

	clear_stat_analysis(emu_stat);
    
    emu->regs[0] = (unsigned int) string;

    emu->regs[REG_PC] = (unsigned int) strlen_s;

    emulate_program(emu, emu_stat);

	print_analysis(emu, emu_stat);

}

/* Emulate Quadratic Function */
void emulate_quadratic(emulator* emu, static_analysis* emu_stat, int x, int a, int b, int c){

    clear_regs(emu);

    clear_stat_analysis(emu_stat);
    
    emu->regs[0] = x;

    emu->regs[1] = a;

    emu->regs[2] = b;

    emu->regs[3] = c;

    emu->regs[REG_PC] = (unsigned int) quadratic_s;
    
    emulate_program(emu, emu_stat);

	print_analysis(emu, emu_stat); 

}

/* General Emulator */
void emulate_program(emulator* emu, static_analysis* emu_stat){

    unsigned int iw;

   do{ 
		emu_stat->instruction_count++;

        iw = *(unsigned int*) emu->regs[REG_PC];
        
        if( ((iw >> 25) & 0b111) == 0b101){
            branch_check_iw(emu, emu_stat, iw);
        }else if( ((iw >> 26) & 0b11) == 0b01){
			emu_stat->memory_count++;
            //Execute ldr or str Instruction
            ldr_str_iw(emu, iw);
        }else if( (((iw >> 22)& 0b111111) == 0b000000) && (((iw >> 4) & 0b1111) == 0b1001) ){
            //Execute Muliply
		    mul_iw(emu, iw);
    	}else if(((iw >> 4) & 0b111111111111111111111111) == branch_bx){
            //Execute Branch
		    bx_iw(emu, emu_stat, iw);
	    }else{
            emu_stat->data_proc_count++;
            //Execute Data Pro.
       	    data_iw(emu, iw);
        }

    }while(emu->regs[REG_PC] != 0);

}

/* Print Static Analysis Function */
void print_analysis(emulator* emu, static_analysis* emu_stat){

	printf("%d\n",emu->regs[0]);

	printf("\n***** Static Analysis *****\n");
	
	printf("Data Processing Count: %d\n", emu_stat->data_proc_count);

	int total_branches = emu_stat->branch_taken + emu_stat->branch_not_taken;

	printf("Total Branches: %d\n", total_branches);

	float percent_bt = (emu_stat->branch_taken * 100)/total_branches;

	float percent_bnt = (emu_stat->branch_not_taken * 100)/total_branches;

	printf("%.2f%% taken vs. %.2f%% not taken\n", percent_bt, percent_bnt);

    printf("Total Instruction Count: %d\n", emu_stat->instruction_count);

	printf("Total Memory Count: %d\n", emu_stat->memory_count);

	printf("*************************************\n");

}
