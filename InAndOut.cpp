#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InAndOut.h"


void Clean_Buffer()
{
	while ((getchar()) != '\n')
		; /* no action */
}

void Get_Coef(double* a, double* b, double* c)
{
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);

	printf("Enter the coefficient for x squared\n");
	while (!scanf("%lg", a))
	{
		Clean_Buffer();
		printf("Wrong format. Try again\n");
	}

	Clean_Buffer();
	printf("Enter the coefficient for x\n");
	while (!scanf("%lg", b))
	{
		Clean_Buffer();
		printf("Wrong format. Try again\n");
	}

	Clean_Buffer();
	printf("Enter the free coefficient\n");
	while (!scanf("%lg", c))
	{
		Clean_Buffer();
		printf("Wrong format. Try again\n");
	}
}


void Get_Rand_Coef(double* a, double* b, double* c)
{
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);

	*a = rand();
	double k = rand();
	if (k == 0)
		k = ((int)k % 10) + 1;
	*a = (*a) / k;

	*b = rand();
	k = rand();
	if (k == 0)
		k = ((int)k % 10) + 1;
	*b = (*b) / k;

	*c = rand();
	k = rand();
	if (k == 0)
		k = ((int)k % 10) + 1;
	*c = (*c) / k;

	printf("%lg %lg %lg\n", *a, *b, *c);
}
