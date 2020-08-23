#include "task_46_01.h"

size_t stringLength(const char *str)
{
	size_t length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return length;

}

int stringComp(const char *str1, const char *str2)
{

	size_t i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i] || abs((int)(stringLength(str1) - stringLength(str2))) != 0) {
			return -1;
		}
		i++;
	}
	return 1;
}

int NstringComp(const char *str1, const char *str2, int n)
{
	int i;
	if (stringLength(str2) != n)
	{
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
		{
			return 0;
		}
	}
	return 1;
}

int main(int argc, char* argv[])
{
	int n, i, j, res, max_iterations = 0;
	clock_t beginTime, endTime;
	int flagP = 0, flagT = 0, flagH = 0;
	int k = 1;
	double *A, *E, *tmp;
	char *filenameIn = "46_01_in.txt";
	char *filenameOut = "46_01_out.txt";
	FILE *in, *out;
	debug = error = 0;
	double precision = 1e-14, epsilon = 1e-10, time;

	for (i = 0; i < argc; i++)
	{
		if (argv[i][0] != '-')
		{
			continue;
		}
		else if (stringComp(argv[i], "-d") == 1)
		{
			debug = 1;
			continue;
		}
		else if (stringComp(argv[i], "-e") == 1)
		{
			error = 1;
			continue;
		}
		else if (stringComp(argv[i], "-p") == 1)
		{
			flagP = 1;
			continue;
		}
		else if (stringComp(argv[i], "-h") == 1 || stringComp(argv[i], "-?") == 1)
		{
			printf("Usage: evc[input_file_name][output_file_name][options] \nWhere options include : \n-d    print debug messages[default OFF] \n -e    print errors[default OFF] \n -p    print matrix[default OFF] \n -t    print execution time[default OFF] \n  -prec=<num>       precision[default - 1e-14]\n  -eps=<num>        'epsilon'[default - 1e-10]\n  -max_iter=<num>   limit number of iterations [default - 0, i.e. not limit]\n  -h, -? print this and exit \nDefault input_file_name value is lss_00_00_in.txt, default output_file_name value is lss_00_00_out.txt.");
		}
		else if (stringComp(argv[i], "-t") == 1)
		{
			flagT = 1;
			continue;
		}
		else if (NstringComp(argv[i], "-prec=", 6) == 1)
		{
			precision = atof(argv[i] + 6);
			continue;
		}
		else if (NstringComp(argv[i], "-eps=", 5) == 1)
		{
			precision = atof(argv[i] + 5);
			continue;
		}
		else if (NstringComp(argv[i], "-max_iter=", 10) == 1)
		{
			precision = atof(argv[i] + 10);
			continue;
		}
		else
		{
			if (error)
			{
				fprintf(stderr, "Parametr zadan ne pravilno\n");
			}
			return -6;
		}
	}
	
	if (argc > 1 && argv[1][0] != '-')
	{
		filenameIn = argv[1];
	}

	if (argc > 2 && argv[2][0] != '-')
	{
		filenameOut = argv[2];
	}
	
	if (debug)
	{
		printf("Otkritiye fayla ... \n");
	}
	
	in = fopen(filenameIn, "r");
	
	if (in == NULL)
	{
		if (error)
		{
			fprintf(stderr, "Oshibka pri otkritii vhodnogo fayla\n");
		}
		return -1;
	}
	
	out = fopen(filenameOut, "w");
	
	if (out == NULL)
	{
		if (error)
		{
			fprintf(stderr, "Oshibka pri otkritii vhodnogo fayla\n");
		}
		return -4;
	}

	if (debug)
	{
		printf("Schitivaniye razmera matrici... \n");
	}

	if (fscanf(in, "%d", &n) != 1 || n <= 0)
	{
		fclose(in);
		if (error)
		{
			printf(stderr, "Oshibka pri razmernosti matrici libo razmer matrichi menishe nulya\n");
		}
		return -1;
	}
	
	if (debug)
	{
		printf("Videleniye pamyati ... \n");
	}

	A = (double*)malloc(n*n * sizeof(double));
	E = (double*)malloc(n * sizeof(double));
	tmp = (double*)malloc((sim_memsize_46_01(n))* sizeof(double));

	if (A == NULL || E==NULL || tmp == NULL)
	{
		fclose(in);
		if (error)
		{
			fprintf(stderr, "Oshibka pri vidilenii pamyati\n");
		}
		return -2;
	}
	if (debug)
	{
		printf("Schitivaniye elementov matrici ... \n");
	}

	for (j = 0; j < n*n; j++)
	{
		if (fscanf(in, "%lf", &A[j]) != 1)
		{
			fclose(in);
			if (error)
			{
				fprintf(stderr, "Oshibka pri schitivanii\n");
			}
			return -3;
		}
	}

	fclose(in);

	if (flagP)
	{
		print(A, n);
	}
	if (debug)
	{
		printf("Privodeneye k pochti terudolnomu vidu ... \n");
	}
	beginTime = clock();
	matrix();
	res = sim_46_01(n,A,tmp,precision);
	endTime = clock();
	time = (double)(endTime - beginTime) / CLOCKS_PER_SEC;

	if (res == 0)
	{
		if (debug)
		{
			printf("Nahojdeniye sobstvennih znacheniy ... \n");
		}
		beginTime = clock();
		res = evc_46_01(n, max_iterations, epsilon, A, E, tmp, precision);
		endTime = clock();
	}

	if (res == 0)
	{
		if (debug)
		{
			printf("Zapic rezultatov v fayl ... \n");
		}
		fprintf(out, "%d\n", n);
		for (i = 0; i < n; i++)
		{
			fprintf(out, "%1.9lf\n", E[i]);
		}
	}
	else if (res == 1)
	{
		if (error)
		{
			fprintf(stderr, "Metod ne shoditsya za ukazannoye chislo iteraciy\n");
		}
		fprintf(out, "0");
		return -5;
	}
	
	fclose(out);
	free(A);
	free(E);
	free(tmp);

	if (flagT)
	{
		time += (double)(endTime - beginTime) / CLOCKS_PER_SEC;
		printf("%lf\n", time);
	}
	
	return 0;
}
