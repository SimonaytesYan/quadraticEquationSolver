#define _CRT_SECURE_NO_WARNINGS
const double E = 1e-6;
const int INF_ROOTS = -1;
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <malloc.h>

struct Roots {
	int nRoots = 0;
	double* roots = NULL;
};

Roots Init_Roots(int nRoots) {
	return Roots {nRoots, (nRoots > 0) ? (double*)malloc(sizeof(double) * nRoots) : NULL };
}

void Del_Roots(Roots* r) { 
	if (r->roots != NULL)
		free(r->roots);
}

bool Is_Same(double a, double b) {
	return (a - E < b + E && b - E < a + E);
}

bool Is_Zero(double x) {
	return (-E < x && x < E);
}

void clean_buffer() {
	while ((getchar()) != '\n');
}

void get_rand_coef(double* a, double* b, double* c)
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

void get_coef(double* a, double* b, double* c)
{
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);

	printf("Enter the coefficient for x squared\n");
	while (!scanf("%lg", a))
	{
		clean_buffer();
		printf("Wrong format. Try again\n");
	}

	clean_buffer();
	printf("Enter the coefficient for x\n");
	while (!scanf("%lg", b))
	{
		clean_buffer();
		printf("Wrong format. Try again\n");
	}

	clean_buffer();
	printf("Enter the free coefficient\n");
	while (!scanf("%lg", c))
	{
		clean_buffer();
		printf("Wrong format. Try again\n");
	}
}

double D(double a, double b, double c)
{
	return b * b - 4 * a * c;
}

Roots solve_1eq(double b, double c) 
{
	if (Is_Zero(b))
	{
		if (Is_Zero(c))
			return Init_Roots(INF_ROOTS);
		return Init_Roots(0);
	}
	Roots r = Init_Roots(1);
	r.roots[0] = -c / b;
	return r;
}

Roots solve_2eq(double a, double b, double c)
{
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));
	
	if (Is_Zero(a))
		return solve_1eq(b, c);

	double d = D(a, b, c);

	if (Is_Zero(d))
	{
		Roots r = Init_Roots(1);
		r.roots[0] = -b / (2 * a);
		return r;
	}

	if (d < 0)
		return Init_Roots(0);

	double sqrt_d = sqrt(d);
	Roots r = Init_Roots(2);
	r.roots[0] = (-b - sqrt_d) / (2 * a);
	r.roots[1] = (-b + sqrt_d) / (2 * a);
	return r;
}

void Output(Roots anses) {

	if (anses.nRoots == INF_ROOTS)
	{
		printf("InfInit_Rootsy number of roots\n");
		return;
	}
	if (anses.nRoots == 0)
	{
		printf("No roots\n");
		return;
	}
	if (anses.nRoots > 0) {
		for (int i = 0; i < anses.nRoots; i++) {
			printf("%lg ", anses.roots[i]);
		}
		printf("\n");
		return;
	}

	printf("Error\n");
}