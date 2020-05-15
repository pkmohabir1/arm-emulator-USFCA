#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test_cases.h"
#include "armemu.h"
#include "static_analysis.h"
#include "debug.h"
#include "emulate.h"

/*
 * quadratic_c calculates the solution to the quadratic equation for the given parameters.
 */
int quadratic_c(int x, int a, int b, int c){

	int result = (a*(x*x)) + (b*x) + c;
	return result;
}

/*
 * sum_array_c calculates the sum of the integers in the array.
 */
int sum_array_c(int *array, int n){

	int i;
	int sum = 0;

	for(i = 0; i<n; i++){
		sum = sum + array[i];
	}
	return sum;
}

/*
 * fib_iter_c iteratively determines the value of the nth number in the Fibonacci sequence.
 */
int fib_iter_c(int n){

	int prev_prev_num = 0;
	int prev_num = 0;
	int cur_num = 1;

	if (n == 0){
		return 0;
	}

	for(int i = 1; i<n; i++){
		prev_prev_num = prev_num;
		prev_num = cur_num;
		cur_num = prev_prev_num + prev_num;
	}

	return cur_num;
}

/*
 * fib_rec_c recursively determines the value of the nth number in the Fibonacci sequence
 */
int fib_rec_c(int n){

	if(n == 0){
		return 0;
	} else if(n == 1) {
		return 1;
	} else {
		return fib_rec_c(n - 1) + fib_rec_c(n - 2);
	}
	return 0;
}

/*
 * Find_max_c finds the largest number in an array of integers
 */
int find_max_c(int *array, int n){

	int i;
	int max = array[0];

	for (i = 1; i<n; i++){

		if(array[i] > max){
			max = array[i];
		}
	}
	return max;
}

/*
 * strlen_c counts the nukber of characters in a C String
 */
int strlen_c(char *s){

	int i = 0;

	while(s[i] != '\0'){
		i++;
	}
	return i;
}

/*
 * Tests for Quadratic Functions
 */
void test_quad(emulator* emu, static_analysis* emu_stat){

	printf("\n******** Quadratic Tests ********\n");

	printf("\n");
	printf("quadratic_c(1,36,6,9) = %d\n",quadratic_c(1,36,6,9));
	printf("quad(1,36,6,9) =  %d\n", quadratic_s(1,36,6,9));
	printf("emulate_quadratic_s(emu,emu_stat,1,36,6,9) = ");
	emulate_quadratic(emu, emu_stat,1,36,6,9);

	printf("\n");
	printf("quadratic_c(1,2,3,4) = %d\n",quadratic_c(1,2,3,4));
	printf("quad(1,2,3,4) = %d\n", quadratic_s(1,2,3,4));
	printf("emulate_quadratic_s(emu,emu_stat,1,2,3,4) = ");
	emulate_quadratic(emu, emu_stat,1,2,3,4);

	printf("\n");
	printf("quadratic_c(-1,-2,-3,-4) = %d\n", quadratic_c(-1,-2,-3,-4));
	printf("quad(-1,-2,-3,-4) = %d\n", quadratic_s(-1,-2,-3,-4));
	printf("emulate_quadratic_s(emu,emu_stat,-1,-2,-3,-4) = ");
	emulate_quadratic(emu, emu_stat,-1,-2,-3,-4);

	printf("\n");
	printf("quadratic_c(-4,2,-3,6) = %d\n", quadratic_c(-4,2,-3,6));
	printf("quad(-4,2,-3,6) = %d\n", quadratic_s(-4,2,-3,6));
	printf("emulate_quadratic_s(emu,emu_stat,-4,2,-3,6) = ");
	emulate_quadratic(emu, emu_stat,-4,2,-3,6);

	printf("\n");
	printf("quadratic_c(7,10,0,-40) = %d\n", quadratic_c(7,10,0,-40));
	printf("quad(7,10,0,-40) = %d\n", quadratic_s(7,10,0,-40));
	printf("emulate_quadratic_s(emu,emu_stat,7,10,0,-40) = ");
	emulate_quadratic(emu, emu_stat,7,10,0,-40);

}

/*
 * Tests for Sum Array Functions
 */
void test_sum_arr(emulator* emu, static_analysis* emu_stat){

	printf("\n******** Sum Array Tests ********\n");

	printf("\n");

	int pos_array[] = {50,22,3,14,35};

	printf("sum_array_c([50,22,3,14,35],5) = %d\n", sum_array_c(pos_array,5));
	printf("sum([50,22,3,14,35],5) = %d\n", sum_arr_s(pos_array,5));
	printf("emulate_sum_arr(emu,emu_stat,[50,22,3,14,35],5) = ");
	emulate_sum_arr(emu, emu_stat, (unsigned int) pos_array,5);

	printf("\n");

	int neg_array[] = {-1,-2,-2,-3,-4};

	printf("sum_array([-1,-2,-2,-3,-4],5) = %d\n", sum_array_c(neg_array, 5));
	printf("sum([-1,-2,-2,-3,-4], 5) = %d\n", sum_arr_s(neg_array, 5));
	printf("emulate_sum_arr(emu,emu_stat,[-1,-2,-2,-3,-4], 5) = ");
	emulate_sum_arr(emu, emu_stat, (unsigned int) neg_array,5);

	printf("\n");

	int zero_array[] = {0,-8,30,-24,4};

	printf("sum_array_c([0,-8,30,-24,4], 5) = %d\n", sum_array_c(zero_array,5));
	printf("sum([0,-8,30,-24,4],5) = %d\n", sum_arr_s(zero_array,5));
	printf("emulate_sum_arr(emu,emu_stat,[0,-8,30,-24,4],5) = ");
	emulate_sum_arr(emu, emu_stat, (unsigned int) zero_array,5);

	printf("\n");

	int thousand_arr[1000];
	for(int i = 0; i < 1000;i++){
		thousand_arr[i] = i+1;
	}

	printf("sum_array_c([1,2,...,1000],1000) = %d\n", sum_array_c(thousand_arr,1000));
	printf("sum([1,2,...,1000],1000) = %d\n", sum_arr_s(thousand_arr,1000));
	printf("emulate_sum_arr(emu,emu_stat,[1,2,...,1000],1000) = ");
	emulate_sum_arr(emu, emu_stat, (unsigned int) thousand_arr,1000);

}

/*
 * Tests for Find Max Functions
 */
void test_find_max(emulator* emu, static_analysis* emu_stat){

	printf("\n******** Find Max Tests ********\n");
	printf("\n");
	int pos_max [] = {0,4,10,3,3};

	printf("find_max_c([0,4,10,3,3],5) = %d\n", find_max_c(pos_max, 5));
	printf("max([0,4,10,3,3],5) = %d\n", find_max_s(pos_max, 5));
	printf("emulate_find_max(emu,emu_stat,[0,4,10,3,3],5) = ");
	emulate_find_max(emu, emu_stat, (unsigned int) pos_max,5);

	printf("\n");

	int neg_max [] = {-4,-5,-2,-1,-6};

	printf("find_max_c([-4,-5,-2,-1,-6],5) = %d\n", find_max_c(neg_max, 5));
	printf("max([-4,-5,-2,-1,-6],5) = %d\n", find_max_s(neg_max, 5));
	printf("emulate_find_max(emu,emu_stat,[-4,-5,-2,-1,-6],5) = ");
	emulate_find_max(emu, emu_stat, (unsigned int) neg_max,5);

	printf("\n");

	int arr1 [] = {54,3,-2,-3,340,7};

	printf("find_max_c([54,3,-2,-3,340,7], 6) = %d\n",find_max_c(arr1,6));
	printf("max([54,3,-2,-3,340,7],6) = %d\n",find_max_s(arr1,6));
	printf("emulate_find_max(emu,emu_stat,[54,3,-2,-3,340,7],6) = ");
	emulate_find_max(emu, emu_stat, (unsigned int) arr1,6);

	printf("\n");

	int thousand_arr[1000];
	for(int i = 0; i < 1000; i++){
		thousand_arr[i] = i+1;
	}

	printf("find_max_c([1,2,...,1000],1000) = %d\n",find_max_c(thousand_arr,1000));
	printf("max([1,2,...,1000], 1000) = %d\n", find_max_s(thousand_arr, 1000));
	printf("emulate_find_max(emu,emu_stat,[1,2,...,1000], 1000) = ");
	emulate_find_max(emu, emu_stat, (unsigned int) thousand_arr,1000);

}

/*
 * Tests for Fibonacci Iterative Functions
 */
void test_fib_iter(emulator* emu, static_analysis* emu_stat){

	printf("\n******** Fibonacci Iterative Tests ********\n");

	printf("0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765\n");

	printf("\n");
	printf("fib_iter_c(0) = %d\n", fib_iter_c(0));
	printf("fib(0) = %d\n", fib_iter_s(0));
	printf("emulate_fib_iter(emu,emu_stat,0) = ");
	emulate_fib_iter(emu, emu_stat, 0);

	printf("\n");
	printf("fib_iter_c(1) = %d\n", fib_iter_c(1));
	printf("fib(1) = %d\n", fib_iter_s(1));
	printf("emulate_fib_iter(emu,emu_stat,1) = ");
	emulate_fib_iter(emu, emu_stat, 1);

	printf("\n");
	printf("fib_iter_c(10) = %d\n", fib_iter_c(10));
	printf("fib(10) = %d\n", fib_iter_s(10));
	printf("emulate_fib_iter(emu,emu_stat,10) = ");
	emulate_fib_iter(emu, emu_stat, 10);

	printf("\n");
	printf("fib_iter_c(20) = %d\n", fib_iter_c(20));
	printf("fib(20) = %d\n", fib_iter_s(20));
	printf("emulate_fib_iter(emu,emu_stat,20) = ");
	emulate_fib_iter(emu, emu_stat, 20);

}

/*
 * Tests for Fibonacci Recursive Functions
 */
void test_fib_rec(emulator* emu, static_analysis* emu_stat){

	printf("\n******** Fibonacci Recursive Tests ********\n");

	printf("0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181\n");

	printf("fib_rec_c(0) = %d\n", fib_rec_c(0));
	printf("rec(0) = %d\n", fib_rec_s(0));
	printf("emulate_fib_rec (emu,emu_stat,0) = ");
	emulate_fib_rec(emu, emu_stat, 0);

	printf("\n");
	printf("fib_rec_c(1) = %d\n", fib_rec_c(1));
	printf("rec(1) = %d\n", fib_rec_s(1));
	printf("emulate_fib_rec (emu,emu_stat,1) = ");
	emulate_fib_rec(emu, emu_stat, 1);

	printf("\n");
	printf("fib_rec_c(10) = %d\n", fib_rec_c(10));
	printf("rec(10) = %d\n", fib_rec_s(10));
	printf("emulate_fib_rec (emu,emu_stat,10) = ");
	emulate_fib_rec(emu, emu_stat, 10);

	printf("\n");
	printf("fib_iter_c(20) = %d\n", fib_iter_c(20));
	printf("fib(20) = %d\n", fib_rec_s(20));
	printf("emulate_fib_rec (emu,emu_stat,20) = ");
	emulate_fib_rec(emu, emu_stat, 20);

}

/*
 * Tests for String Length Functions
 */
void test_strlen(emulator* emu, static_analysis* emu_stat){

	printf("\n******** StrLen Tests ********\n");

	printf("strlen_c(\"hi\") = %d\n",strlen_c("hi"));
	printf("len(\"hi\") = %d\n", strlen_s("hi"));
	printf("emulate_strlen(emu,emu_stat,\"hi\") = ");
	emulate_strlen(emu,emu_stat,"hi");

	printf("\nstrlen_c(\"Hello World\") = %d\n",strlen_c("Hello World"));
	printf("len(\"Hello World\") = %d\n", strlen_s("Hello world"));
	printf("emulate_strlen(emu,emu_stat,\"Hello World\") = ");
	emulate_strlen(emu,emu_stat,"Hello World");

	printf("\nstrlen_c(\"CS 315 rules!\") = %d\n",strlen_c("CS 315 rules!"));
	printf("len(\"CS 315 rules!\") = %d\n", strlen_s("CS 315 rules!"));
	printf("emulate_strlen(emu,emu_stat,\"CS 315 rules!\") = ");
	emulate_strlen(emu,emu_stat,"CS 315 rules!");

	printf("\nstrlen_c(\"This is a long long long long string.\") = %d\n",strlen_c("This is a long long long string."));
	printf("len(\"This is a long long long string.\") = %d\n", strlen_s("This is a long long long string."));
	printf("emulate_strlen(emu,emu_stat,\"This is a long long long string.\") = ");
	emulate_strlen(emu,emu_stat,"This is a long long long string.");

}
