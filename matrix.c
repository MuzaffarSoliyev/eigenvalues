#include "task_46_01.h"

void matrix()
{
	int i,j;
	FILE *f;
	f = fopen("out.txt", "w");
	double A[30][30];
	for (i = 0; i < 30; i++)
		for (j = 0; j < 30; j++)
			A[i][j] = 0;

	for (i = 0; i < 30; i++)
	{

		A[i][i] = 30 / (i+1);
		for (j = 0; j < 30; j++)
		{
			if (i > j)
			{
				A[i][j] = 1.0 / ((i+1) + 2 * (j+1));
				A[j][i] = A[i][j];
			}
		}
	}
	fprintf(f, "%d\n", 30);
	for (i = 0; i < 30; i++)
	{
		for (j = 0; j < 30; j++)
		{
			fprintf(f,"%lf ", A[i][j]);
		}
		fprintf(f,"\n");
	}
}