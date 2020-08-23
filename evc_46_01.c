#include "task_46_01.h"

void bubbleSort(double* ArrayPtr, int length_array)
{
	double tmp;
	int i;
	int exit = 0;
	while (!exit)
	{
		exit = 1;
		for (i = 0; i < (length_array - 1); i++)
		{
			if (ArrayPtr[i] > ArrayPtr[i + 1])
			{
				tmp = ArrayPtr[i];
				ArrayPtr[i] = ArrayPtr[i + 1];
				ArrayPtr[i + 1] = tmp;
				exit = 0;
			}
		}
	}
}

double normalInfinit(double *A, int n)
{
	int i,j;
	double rowSum, normalInfinity = 0;
	for (i = 0; i < n; i++)
	{
		rowSum = 0;
		for (j = 0; j < n; j++) {
			rowSum += fabs(A[i*n + j]);
		}
		if (rowSum > normalInfinity )
		{
			normalInfinity = rowSum;
		}
	}
	return normalInfinity;
}

int evc_46_01(int n, int max_iterations, double epsilon, double* A, double* E, double* tmp, double precision)
{
	double s_k = A[(n - 1)*n + n - 1];
	int k, i, iter, step = 0;
	double *L = A, *R = A;
	double rowSum = 0, normalInfinity = normalInfinit(A,n);

	normalInfinity *= epsilon;

	for (iter = 0;iter < max_iterations || max_iterations == 0; iter++)
	{
		
		if (fabs(A[n*n - 2 - step*(n + 1)]) < normalInfinity)
		{
			E[step] = A[n*n - 1 - step*(n + 1)];
			step++;
		}

		if (n - step == 2)
		{
			E[step] = (A[0] + A[n + 1] + sqrt((A[0] + A[n + 1])*(A[0] + A[n + 1]) - 4 * (A[0] * A[n + 1] - A[1] * A[n]))) / 2;
			E[step + 1] = (A[0] + A[n + 1] - sqrt((A[0] + A[n + 1])*(A[0] + A[n + 1]) - 4 * (A[0] * A[n + 1] - A[1] * A[n]))) / 2;
			bubbleSort(E, n);
			return 0;
		}

		s_k = A[n*n - 1 - step*(n + 1)];

		for (i = 0; i < n*(n - step); i += n + 1) 
		{
			A[i] -= s_k;
		}


		for (i = 1; i < n - step; i++)
		{
			L[i*n + (i - 1)] = A[i*n + i - 1] / R[(i - 1) * n + i - 1];
			for (k = i; k < n - step; k++)
			{
				R[i*n + k] = A[i*n + k] - L[i*n + (i - 1)] * R[(i - 1)*n + k];
			}
		}
		
		for (k = 0; k < n - 1 - step; k++) 
		{
			A[k] = R[k] + R[k + 1] * L[(k + 1)*n + k];
		}
		
		for (i = 1; i < n - step; i++) 
		{
			A[i*n + (i - 1)] = R[i*n + i] * L[i*n + (i - 1)];
			for (k = i; k < n - 1 - step; k++) 
			{
				A[i*n + k] = R[i*n + k] + R[i*n + (k + 1)] * L[(k + 1)*n + k];
			}
		}
		
		for (i = 0; i < n*(n - step); i += n + 1) 
		{
			A[i] += s_k;
		}

		
	}
	return 1;
}