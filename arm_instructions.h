#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"

#ifndef _ARM_INSTRUCTIONS_H
#define _ARM_INSTRUCTIONS_H

//Opcode instructions
#define opcode_add 0b0100
#define opcode_sub 0b0010
#define opcode_mov 0b1101
#define branch_bx 0b000100101111111111110001
#define opcode_cmp 0b1010

//condition fields
#define EQ 0b0000 //z set
#define NE 0b0001 //clear X
#define GE 0b1010 //N EQUALS V
#define LE 0b1101 //Z set OR (N not equal to V)
#define AL 0b110 //ignored

//CPSR FLAGS
#define z_bit 30
#define v_bit 28
#define n_bit 31


/* Instuction Prototypes */
void data_iw(emulator* emu, unsigned int iw);
void mul_iw(emulator* emu, unsigned int iw);
void bx_iw(emulator* emu, static_analysis* emu_stat, unsigned int iw);
void ldr_str_iw(emulator* emu, unsigned int iw);
void branch_iw(emulator* emu, unsigned int iw);
void branch_check_iw(emulator* emu, static_analysis* emu_stat, unsigned int iw);


#endif
