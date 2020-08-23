#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#pragma warning(disable:4996)


int sim_46_01(int n, double* A, double* tmp, double precision);
int evc_46_01(int n, int max_iterations, double epsilon, double* A, double* E, double* tmp, double precision);
void matrix();
size_t sim_memsize_46_01(int n);
int debug, error;