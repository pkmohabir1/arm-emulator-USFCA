#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"
#include "armemu.h"
#include "static_analysis.h"

#ifndef _EMULATE_H
#define _EMULATE_H

/* Emulated Prototypes */
void emulate_quadratic(emulator* emu, static_analysis* emu_stat, int x, int a, int b, int c);
void emulate_sum_arr(emulator* emu, static_analysis*  emu_stat, unsigned int arr, int n);
void emulate_strlen(emulator* emu, static_analysis* emu_stat, unsigned char* string);
void emulate_find_max(emulator* emu, static_analysis* emu_stat, unsigned int arr, int n);
void emulate_fib_iter(emulator* emu, static_analysis* emu_stat, int n);
void emulate_fib_rec(emulator* emu, static_analysis* emu_stat, unsigned int n);
void emulate_program(emulator* emu, static_analysis* emu_stat);
void print_analysis(emulator* emu, static_analysis* emu_stat);

/* Set CSPR Flags Prototype*/
void set_cpsr(emulator* emu, int cmp_result, unsigned int iw);

/* Clear Resisters Prototype */
void clear_regs(emulator* emu);

/* Clear Static Analysis Struct */
void clear_stat_analysis(static_analysis* emu_stat);

/* Print Static Analysis Prototype */
void print_analysis(emulator* emu, static_analysis* emu_stat);

#endif 
