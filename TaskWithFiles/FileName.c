#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


int main() 
{
	FILE* file;
	char buffer[8];
	double* list = calloc(3, sizeof(double));

	file = fopen("Coeff.txt", "r");

	int i = 0;
	while (!feof(file))
	{
		fgets(buffer, sizeof(buffer), file);
		double c = atof(buffer);
		list[i] = c;

		printf("%2.3f ", list[i]);
		i++;
	}
	fclose(file);
}