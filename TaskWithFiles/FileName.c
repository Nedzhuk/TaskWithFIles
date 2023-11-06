#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* Roots(double discr, double* list) 
{
	double* roots = calloc(2, sizeof(double));

	double x1 = (-list[1] + sqrt(discr)) / (2 * list[0]);
	double x2 = (-list[1] - sqrt(discr)) / (2 * list[0]);
	roots[0] = x1;
	roots[1] = x2;
	return roots;
}

double Root(double* list)
{
	double x = (-list[1]) / (2 * list[0]);
	return x;
}

int Discriminant(double* list) 
{
	double d = (list[1] * list[1]) - (4 * list[0] * list[2]);
	return d;
}

int main() 
{
	FILE *fileCoefficient, *fileResult, *fileReference;
	char buffer[128];
	double* list = calloc(3, sizeof(double));

	fileResult = fopen("ResultRoots.txt", "w");
	fprintf(fileResult, "");
	fclose(fileResult);

	fileReference = fopen("Reference.txt", "w");
	fprintf(fileReference, "");
	fclose(fileReference);

	fileCoefficient = fopen("Coeff.txt", "r");
	int count = 0;
	fseek(fileCoefficient, 0, SEEK_END);
	count = ftell(fileCoefficient);
	fseek(fileCoefficient, 0, SEEK_SET);

	if (count > 0) 
	{
		int i = 0;
		while (!feof(fileCoefficient))
		{
			fgets(buffer, sizeof(buffer), fileCoefficient);
			
			double c = atof(buffer);
			
			if ((buffer[0] >= '0' && buffer[0] <= '9') || (buffer[0] == '-' && (buffer[1] >= '0' && buffer[1] <= '9')))
			{
				if (c == 0 && i == 0) 
				{
					printf("1 coefficient cannot be qual 0");
					return 1;
				}
				list[i] = c;
				printf("%2.3f ", list[i]);
				i++;
			}
			else 
			{
				printf("\nThe coefficient cannot be a symbol");
				return 3;
			}
		}
	}
	else 
	{
		printf("File was empty");
		return 2;
	}

	fclose(fileCoefficient);
	double discr = Discriminant(list);
	printf("\nDiscriminant = %2.3f", discr);
	
	fileResult = fopen("ResultRoots.txt", "w+t");
	if (discr == 0) 
	{
		double root = Root(list);
		printf("\nRoot = %2.3f", root);

		fprintf(fileResult, "Root = %2.3f", root);
	}
	else if (discr > 0)
	{
		double* roots = Roots(discr, list);
		printf("\nRoot 1 = %2.3f\nRoot 2 = %2.3f", roots[0], roots[1]);

		fprintf(fileResult, "Root 1 = %2.3f\nRoot 2 = %2.3f", roots[0], roots[1]);
	}
	else 
	{
		printf("\nNo roots");
		fprintf(fileResult, "No root");
	}
	fclose(fileResult);

	fileReference = fopen("Reference.txt", "w+t");
	fprintf(fileReference, "Discriminant = %2.3f\n", discr);
	if (discr == 0)
		fprintf(fileReference, "Count roots = 1\n");
	if(discr >0)
		fprintf(fileReference, "Count roots = 2\n");
	if (discr < 0)
		fprintf(fileReference, "Count roots = 0\n");

	fclose(fileReference);

	return 0;
}