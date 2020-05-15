#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** 
 * Arm Prototypes
 */
extern int quadratic_s(int x,int a,int b, int c);
extern int fib_iter_s(int n);
extern int sum_arr_s(int *array, int n);
extern int find_max_s(int *array, int n);
extern int strlen_s(char *s);
extern int fib_rec_s(int n);

/*
 * C Prototypes
 */
int quadratic_c(int x, int a, int b, int c);
int sum_array_c(int *array, int n);
int find_max_c(int *array, int n);
int fib_iter_c(int n);
int strlen_c(char *s);
int fib_rec_c(int n);

/*
* Test Case Prototypes
*/
void test_quad();
void test_sum_arr();
void test_find_max();
void test_fib_iter();
void test_fib_rec();
void test_strlen();

