#include "task_46_01.h"

double max_b(double a, double b)
{
	return (a) > (b) ? (a) : (b);
}

double counting(double *A_1, double *A, int n)
{
	int i;
	double v_1 = 0, v_2 = 0, v_3 = 0, v_4 = 0;
	for (i = 0; i < n; i++)
	{
		v_1 += (A[i*n + i] - A_1[i*n + i])*(A[i*n + i] - A_1[i*n + i]);
		if ( v_2 < fabs(A[i*n + i] - A_1[i*n + i]) ) 
			v_2 = fabs(A[i*n + i] - A_1[i*n + i]);
	}
	v_1 = sqrt(v_1);
	for (i = 0; i < n; i++)
	{
		v_3 += (A[(i + 1)*n + i] - A_1[(i + 1)*n + i])*(A[(i + 1)*n + i] - A_1[(i + 1)*n + i]);
		if (v_4 < fabs(A[(i + 1)*n + i] - A_1[(i + 1)*n + i]))
			v_4 = fabs(A[(i + 1)*n + i] - A_1[(i + 1)*n + i]);
	}
	v_3 = sqrt(v_3);
	
	return max_b(v_4, max_b(v_3, max_b(v_2, v_1)));
}

void copy(double *A, double *A_1, int n)
{
	int i;
	for (i = 0; i < n*n; i++)
	{
		A[i] = A_1[i];
	}
}

int evc_46_01(int n, int max_iterations, double epsilon, double* A, double* E, double* tmp, double precision)
{
	double result, s_k = A[(n-1)*n+n-1];
	int k, i, j, iter, x = 0;
	double *L = tmp + n + n*n + n*n, *R = tmp + n + n*n + n*n + n*n, *A_1 = tmp + n + n*n + n*n + n*n + n*n;
	double rSum = 0, eMax = 0;
	
	for (i = 0; i < n*n; i++)
	{
		A_1[i] = 0;
	}

	for (i = 0; i < n; i++)
	{
		rSum = 0;
		for (j = 0; j < n; j++)
		{
			rSum += fabs(A[i*n + j]);
		}
		if (rSum > eMax)
		{
			eMax = rSum;
		}
	}

	eMax = eMax*epsilon;

	for (iter = 0; iter < max_iterations || max_iterations == 0; iter++)
	{
		if (fabs(A[n*n - 1 - x*(n + 1)]) < eMax)
		{
			E[x] = A[n*n - 1 - x*(n + 1)];
			x++;
		}

		if (n - x == 2)
		{
			E[x] = (A[0] + A[n + 1] + sqrt((A[0] + A[n + 1])*(A[0] + A[n + 1]) - 4 * (A[0] * A[n + 1] - A[1] * A[n]))) / 2;
			E[x + 1] = (A[0] + A[n + 1] - sqrt((A[0] + A[n + 1])*(A[0] + A[n + 1]) - 4 * (A[0] * A[n + 1] - A[1] * A[n]))) / 2;
			return 0;
		}

		s_k = A[n*n-1 - x*(n+1)];

		for (i = 0; i < n*(n - x); i += n + 1)
		{
			A[i] -= s_k;
		}

		for (i = 1; i < n - x; i++)
		{
			L[i*n + (i - 1)] = A[i*n + i - 1] / R[(i - 1) * n + i - 1];
			for (k = i; k < n - x; k++)
			{
				R[i*n + k] = A[i*n + k] - L[i*n + (i - 1)] * R[(i - 1)*n + k];
			}
		}

		for (i = 0; i < n - 1 - x; i++)
		{
			A[i] = R[i] + R[i + 1] * L[(i + 1)*n + k];
		}

		for (i = 0; i < n - x; i++)
		{
			A[i*n + (i - 1)] = R[i*n + i] * L[i*n + (i - 1)];
			for (k = i; k < n - 1 - x; k++)
			{
				A[i*n + k] = R[i*n + k] + R[i*n + k + 1] * L[(k + 1)*n + k];
			}
		}
		for (i = 0; i < n*(n - x); i += n + 1)
		{
			A[i] += s_k;
		}

	}
	
	
	return 1;
}