# Arm Assembly Emulator Project
Writer: Porfirio Mohabir (pkmohabir1) <br />
Writer: Natalia Jones (nljones4) <br />
CS 315 Computer Architecture 

# Project overview
Program will emualate for ARM assembly language in C. Project was done on Raspberry pi

# Project Compenents

 - All 16 registers and the CPSR
 - Data Proeccessing Instructions
 - Branch Instructions
 - The Stack, sufficient for temporary storage of link register and any preserved registers
 - Dynamic Analysis of Emulated instructions, to be printed when the emulated program completed
 ```bash
 1. # of data processing instructions
 2. # of branch instructions
 3. % of branches taken vs. not taken
 4. # of instructions in total
 ```
# Assebemly Files

```bash
- Quadratic_s.s (Quadratic function)
- sum_array_s.s (Sum of array function)
- strlen_s.s    (String length funtion)
- find_max_s.s  (Find Max Function)
- fib_iter_s.s  (Fibonaci Iterative Function)
- fib_rec_s.s.  (Fibonaci Recursive Function)
```
# C Header Files

```bash
- arm_instructions.h
- emulate.h
- static_analysis.h
- test_cases.h
- armemu.h
```
# Execute
C driver will call both the natively assembled version programs and the emulated version of each program.

```base
$ make
$ ./main
```



