#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

void get_rand_coef(float *a, float *b, float *c) 
{
	*a = rand();
	float k = rand();
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

	printf("%f %f %f\n", *a, *b, *c);
}

void get_coef(float* a, float* b, float* c) 
{
	printf("Enter the coefficient for x squared\n");
	while (!scanf("%f", a))
	{
		while ((getchar()) != '\n');
		printf("Wrong format. Try again\n");
	}

	while ((getchar()) != '\n');
	printf("Enter the coefficient for x\n");
	while (!scanf("%f", b))
	{
		while ((getchar()) != '\n');
		printf("Wrong format. Try again\n");
	}

	while ((getchar()) != '\n');
	printf("Enter the free coefficient\n");
	while (!scanf("%f", c))
	{
		while ((getchar()) != '\n');
		printf("Wrong format. Try again\n");
	}
}

float D(float a, float b, float c) 
{
	return b * b - 4 * a * c;
}

float* roots(float a, float b, float c) 
{
	float* Roots;
	if (a == 0) 
	{
		if (b == 0) 
		{
			Roots = (float*)malloc(sizeof(float));
			if (c == 0) 
			{
				(*Roots) = -1;
				return Roots;
			}
			else 
			{
				(*Roots) = 0;
				return Roots;
			}
		}
		else 
		{
			Roots = (float*)malloc(sizeof(float) * 2);
			*Roots = 1;
			*(Roots + 1) = -c / b;
			return Roots;
		}
	}

	float d = D(a, b, c);

	if (d < 0) 
	{
		Roots = (float*)malloc(sizeof(float));
		*Roots = 0;
		return Roots;
	}

	if (d == 0) 
	{
		Roots = (float*)malloc(sizeof(float)*2);
		*Roots = 1;
		*(Roots + 1) = -b / (2 * a);
		return Roots;
	}

	Roots = (float*)malloc(sizeof(float) * 3);
	*Roots = 2;
	*(Roots + 1) = (-b + sqrt(d)) / (2 * a);
	*(Roots + 2) = (-b - sqrt(d)) / (2 * a);
	return Roots;
}

void Output(float *anses) {

	if (*anses == -1)
	{
		printf("Infinity number of roots\n");
	}
	if (*anses == 0)
	{
		printf("No roots\n");
	}

	if (*anses > 0) {
		for (int i = 1; i <= *anses; i++) {
			printf("%f ", *(anses + i));
		}
		printf("\n");
	}
}

int main() 
{
	float a, b, c;
	
	//while (true)
	//{
		//get_rand_coef(&a, &b, &c);
	get_coef(&a, &b, &c);

	float* anses;
	anses = roots(a, b, c);
	Output(anses);
	free(anses);
	//}
	return 0;
}