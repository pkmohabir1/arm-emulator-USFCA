#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"
#include "emulate.h"
#include "arm_instructions.h"

/* Data Processing Function */
void data_iw(emulator* emu, unsigned int iw){
   	    
        // Destination reg is 4 bits starting at bit 12
        unsigned int rd = (iw >> 12) & 0b1111;
        
        // First source reg is 4 bits starting at bit 16
        unsigned int rn = (iw >> 16) & 0b1111;

        // opcode (of the data proccessing family) is 4 bits starting at bit 21
        unsigned int opcode = (iw >> 21) & 0b1111;
    
        // Immediate value (if 25 bit == 1) is 8 bits starting at bit 0
        unsigned int im = iw & 0b11111111;
        
        // op2 register (if 25 bit == 0) is 4 bits starting at bit 0
        unsigned int rm = iw & 0b1111;

		//s_bit
		unsigned int s_bit = (iw >> 20) & 0b1;

        // False if 25 bit ==  0, otherwise True if 25 == 1
        bool flag_op2 = false;

        if(((iw >> 25) & 0b1) == 1){
            flag_op2 = true; // Set flag_op2 to True, 25 bit == 1
        }
        
       // Data Processing Instructions  
        if(opcode == opcode_add){
            // Execute ADD Instruction
            if(!flag_op2){
                //add register value
                emu->regs[rd] = emu->regs[rn] + emu->regs[rm];	
            }else{
                //add immediate value
                emu->regs[rd] = emu->regs[rn] + im; 
             }

        }else if(opcode == opcode_sub){
            //Execute SUB Instruction
            if(!flag_op2){
                //subtract from register value
                emu->regs[rd] = emu->regs[rn] - emu->regs[rm];
            }else{
                //subtract from immediate value
                emu->regs[rd] = emu->regs[rn] - im;
            }

        }else if(opcode == opcode_mov){
            //Execute MOV Instruction
            if(!flag_op2){
                //mov register value
                emu->regs[rd] = emu->regs[rm];
            }else{
                //mov immediate value
                emu->regs[rd] = im;
            }

        } else if(opcode == opcode_cmp){
			int cmp_result;

            if(!flag_op2){
                cmp_result = (int)emu->regs[rn] -(int) emu->regs[rm];
            }else{
                cmp_result = emu->regs[rn] - im;
            }
	    
	 		if(s_bit == 1){
				set_cpsr(emu, cmp_result, iw);
			}
        }
       	emu->regs[REG_PC] += 4;

}

/* Multiply Instruction Function */
void mul_iw(emulator* emu, unsigned int iw){
    
    // Destination reg is 4 bits starting at bit 16
    unsigned int rd = (iw >> 16) & 0b1111;

    // rm register is 4 bits starting at bit 0
    unsigned int rm = iw & 0b1111;

    // rs register is 4 bits starting at bit 8
    unsigned int rs = (iw >> 8) & 0b1111;

    // Execute MUL Instruction
    emu->regs[rd] = emu->regs[rm] * emu->regs[rs];

    emu->regs[REG_PC] += 4;

}

/* Branch & Exchange Function */
void bx_iw(emulator* emu, static_analysis* emu_stat, unsigned int iw){

	emu_stat->branch_taken++;
	
	unsigned int rn = iw & 0b1111;

	emu->regs[REG_PC] = emu->regs[rn];
	
}

/* Branch Check Function */
void branch_check_iw(emulator* emu, static_analysis* emu_stat, unsigned int iw){

	unsigned int cond_code = (iw >> 28) & 0b1111;

	unsigned int z = (emu->cpsr >> 30) & 0b1;

	unsigned int n = (emu->cpsr >> 31) & 0b1;

	unsigned int v = (emu->cpsr >> 28) & 0b1;

    unsigned int c = (emu->cpsr >> 29) & 0b1;

	if((cond_code == 0b0000) && (z == 1)){ //EQ
    	emu_stat->branch_taken++;
		branch_iw(emu, iw);
	}else if ((cond_code == 0b0001) && (z == 0)){//NE
		emu_stat->branch_taken++;
		branch_iw(emu, iw);
	}else if((cond_code == 0b1010) && (n==v)){//GE
		emu_stat->branch_taken++;
		branch_iw(emu, iw);
	} else if((cond_code == 0b1101) && (n!=v)){//LE
		emu_stat->branch_taken++;
		branch_iw(emu, iw);
	} else if(cond_code == 0b1110){ //AL
		emu_stat->branch_taken++;
		branch_iw(emu, iw);
	} else if((cond_code == 0b0011) && (c == 0)){//BCC
		emu_stat->branch_taken++;
        branch_iw(emu, iw);
    } 
    else{
		emu_stat->branch_not_taken++;
		emu->regs[REG_PC] += 4;
	}
		
}

/* Branch Instruction Function */
void branch_iw(emulator* emu, unsigned int iw){

    unsigned int link_bit = (iw >> 24) & 0b1;

    unsigned int cond_code = (iw >> 28) & 0b1111;
    
    unsigned int offset = iw  & 0xFFFFFF;
    
    unsigned int signed_bit = (iw >> 23) & 0b1;

    unsigned int dest;
 
    if(signed_bit == 1){
        dest = offset | 0xFF000000;
    }else{
        dest = offset | 0x00000000;
    }

    if(link_bit ==1){
        emu->regs[REG_LR] = emu->regs[REG_PC]+4;
    }

    dest  = dest << 2;
    
    dest += 8;

    emu->regs[REG_PC] += dest;

}

/* Set CPSR Flags Function */
void set_cpsr(emulator* emu, int cmp_result, unsigned int iw){

    int result = cmp_result;

    unsigned int s_bit = (s_bit >> 20) & 0b1;
    
    unsigned int flag_bit;

    if(result < -2147483648 || result > 2147483648){
	    emu->cpsr |= (1<<v_bit);
    }else{
	    emu->cpsr &= ~(1<<v_bit);
    }
    
    if(result < 0){
        emu->cpsr |= (1<<n_bit);
    } else if(result == 0){
        emu->cpsr |= (1<<z_bit);
        emu->cpsr &= ~(1<<n_bit);
    }else{
        emu->cpsr &= ~(1 << z_bit);
        emu->cpsr &= ~(1 << n_bit);
    }

}

/* LDR & STR Instruction Function */
void ldr_str_iw(emulator* emu, unsigned int iw){

    unsigned int i_bit = (iw >> 25) & 0b1;
   
    unsigned int p_bit = (iw >> 24) & 0b1;

    unsigned int u_bit = (iw >> 23) & 0b1;

    unsigned int b_bit = (iw >> 22) & 0b1;

    unsigned int w_bit = (iw >> 21) & 0b1;

    unsigned int l_bit = (iw >> 20) & 0b1;
    
    unsigned int rn = (iw >> 16) & 0b1111;
    
    unsigned int rn_base_value;

    unsigned int im = iw & 0xFFF;

    unsigned int rm = iw & 0b1111;

    unsigned int rd = (iw >> 12) & 0b1111;

   	if(p_bit == 1){
        if(u_bit == 0){
            if(i_bit == 0){
                rn_base_value =(emu->regs[rn] - im);
            }else{
                rn_base_value =(emu->regs[rn] -  emu->regs[rm]);
            }
        }else{
            if(i_bit == 0){
                rn_base_value = (emu->regs[rn] +  im);
            }else{
                rn_base_value = (emu->regs[rn] +  emu->regs[rm]);
            }
        }
    }

    if(b_bit == 1){
        if(l_bit == 1){

             emu->regs[rd] = *(unsigned char*)rn_base_value;
        }else{
           *(unsigned int *) rn_base_value = emu->regs[rd];
        }
    }else{
        if(l_bit == 1){
			//LDR
            emu->regs[rd] = *(unsigned int*)rn_base_value;
        }else{
           // STR
          *(unsigned int*)rn_base_value = emu->regs[rd];
         }
    }

     if(p_bit == 0){
        if(u_bit == 0){
            if(i_bit == 0){
                rn_base_value =(emu->regs[rn] - im);
            }else{
               rn_base_value =(emu->regs[rn] - emu->regs[rm]);
            }
        }else{
            if(i_bit == 0){
                rn_base_value = (emu->regs[rn] + im);
            }else{
                rn_base_value =(emu->regs[rn] + emu->regs[rm]);
            }
        }
    }  
	emu->regs[REG_PC] += 4;

}

