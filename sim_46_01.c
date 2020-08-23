#include "task_46_01.h"

void multiplicationMatrix(double *A, double *B, int n, double *AB, double precision)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			AB[i*n + j] = 0;
			for (k = 0; k < n; k++)
			{
				AB[i*n + j] += A[i*n + k] * B[k*n + j];
			}
			if (fabs(AB[i*n + j]) < precision)
			{
				AB[i*n + j] = 0;
			}
		}
	}
}

void print(double *A, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%lf ", A[i*n + j]);
		}
		printf("\n");
	}
	printf("\n");
}


int sim_46_01(int n, double* A, double* tmp, double precision)
{
	int k, j, i, l;
	double *x_k = tmp, *buf = tmp + n + n*n, *U = tmp + n;
	double s_k, a_k_1, x_k_norm;


	for (i = 0; i < n; i++)
	{
		x_k[i] = 0;
	}


	for (k = 0; k < n - 1; k++){

		s_k = 0;
		for (i = 0; i < n*n; i++)
		{
			U[i] = 0;
		}
		//printf("U\n");
		//print(U, n);
		for (i = 0; i < n; i++)
		{
			x_k[i] = 0;
		}

		for (j = k + 1; j < n; j++)
		{
			s_k += A[j*n + k] * A[j*n + k];
			x_k[j] = A[j*n + k];
		}

		print(A,n);

		if (fabs(s_k) < precision)
		{
			k++;
			continue;
		}

		a_k_1 = sqrt(s_k);

		x_k[k + 1] = x_k[k + 1] - a_k_1;

		s_k = 0;

		for (j = k + 1; j < n; j++)
		{
			s_k += x_k[j] * x_k[j];
		}
		s_k = sqrt(s_k);


		if (fabs(s_k)<precision)
		{
			continue;
		}

		for (j = 0; j < n; j++)
		{
			x_k[j] = x_k[j] / s_k;

		}

		for (i = k + 1; i < n; i++)
		{
			for (j = k + 1; j < n; j++)
			{
				U[i*n + j] = -2 * x_k[i] * x_k[j];
			}

		}



		for (i = 0; i < n; i++)
		{
			U[i*n + i] += 1;
		}


		//print(U, n);

		multiplicationMatrix(U, A, n, buf, precision);
		//print(buf, n);
		multiplicationMatrix(buf, U, n, A, precision);
		//printf("UAU\n");
		//print(A,n);
		//printf("\n");
	}
	FILE *file;
	file = fopen("res.txt", "w");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			fprintf(file, "%lf ", A[i*n + j]);
		}
		fprintf(file,"\n");
	}
	return 0;
}

size_t sim_memsize_46_01(int n)
{
	return (n*n + n)*sizeof(double);
}