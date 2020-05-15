#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "armemu.h"
#include "debug.h"
#include "static_analysis.h"
#include "test_cases.h"

/* Main  */
int main(int argc, char **argv){

	emulator emu;

	memset(emu.regs, 0, sizeof(unsigned int)); 

	static_analysis emu_stat;

	test_quad(&emu, &emu_stat);

	test_sum_arr(&emu, &emu_stat);

	test_find_max(&emu, &emu_stat);

	test_fib_iter(&emu, &emu_stat);

	test_fib_rec(&emu, &emu_stat);

	test_strlen(&emu, &emu_stat);

    return 0;   

}
