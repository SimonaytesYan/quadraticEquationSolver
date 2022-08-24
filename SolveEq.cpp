#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <malloc.h>
#include "SolveEq.h"
#include "InAndOut.h"

const double EPSILON = 1e-6;

Roots* Init_Roots(int nRoots)
{
	Roots* r = (Roots*)malloc(sizeof(Roots));
	r->nRoots = nRoots;
	if (nRoots > 0) {
		//printf("Malloc start\n");
		r->roots = (double*)malloc(nRoots*sizeof(double));
		//printf("Malloc end\n");
	}
	//printf("End Init\n");
	return r;
}

void Del_Roots(Roots* r)
{
	assert(r != NULL);
	if (r->roots != NULL)
		free(r->roots);
	free(r);
}

bool Is_Same(double a, double b)
{
	return (a - EPSILON < b + EPSILON && b - EPSILON < a + EPSILON);
}

double Evaluate_Discriminant(double a, double b, double c)
{
	return b * b - 4 * a * c;
}

Roots* Solve_1eq(double b, double c)
{
	if (Is_Same(b, 0.))
	{
		if (Is_Same(c, 0.))
			return Init_Roots(INF_ROOTS);
		return Init_Roots(0);
	}

	Roots* r = Init_Roots(1);
	r->roots[0] = -c / b;
	return r;
}
//!-----------------------------------------------------
//! solve_2qe
//! @param [in] a a-coefficient for equation
//! @param [in] b b-coefficient for equation
//! @param [in] c c-coefficient for equation
//! @return Roots of equation
//! ----------------------------------------------------
Roots* Solve_2eq(double a, double b, double c)
{
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));

	if (Is_Same(a,0.))
		return Solve_1eq(b, c);

	double d = Evaluate_Discriminant(a, b, c);

	if (Is_Same(d,0.))
	{
		Roots* r = Init_Roots(1);
		r->roots[0] = -b / (2 * a);
		return r;
	}

	if (d < 0)
		return Init_Roots(0);

	double sqrt_d = sqrt(d);
	Roots* r = Init_Roots(2);
	r->roots[0] = (-b - sqrt_d) / (2 * a);
	r->roots[1] = (-b + sqrt_d) / (2 * a);
	if (r->roots[0] > r->roots[1])
	{
		double swap = r->roots[0];
		r->roots[0] = r->roots[1];
		r->roots[1] = swap;
	}
	return r;
}

void Output(Roots anses)
{
	if (anses.nRoots == INF_ROOTS)
	{
		printf("Infinity number of roots\n");
		return;
	}
	if (anses.nRoots == 0)
	{
		printf("No roots\n");
		return;
	}
	if (anses.nRoots > 0)
	{
		for (int i = 0; i < anses.nRoots; i++)
		{
			printf("%lg ", anses.roots[i]);
		}
		printf("\n");
		return;
	}

	assert(0 && "Error\n");
}