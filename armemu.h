#ifndef _ARMEMU_H
#define _ARMEMU_H

// Special register names
#define REG_SP 13
#define REG_LR 14
#define REG_PC 15
#define NUM_REGS 16
#define STACK_SZ 1024

typedef struct {
    unsigned int regs[NUM_REGS];
    unsigned int stack[STACK_SZ];
    unsigned int cpsr;
} emulator;

#endif 
