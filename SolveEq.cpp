/*!
* \file
* \brief
* File containing the definition of functions to solve quadratic equations
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <malloc.h>
#include "SolveEq.h"
#include "InAndOut.h"

const double EPSILON = 1e-6;

//!-----------------------------------------------------
//! Function to initialize Solutions structure
//! \param [in] nRoots Number of roots in structure
//! \return Return pointer to created structure
//! 
//!-----------------------------------------------------
Solutions* Init_Solutions(int nRoots)
{
	Solutions* r = (Solutions*)malloc(sizeof(Solutions));
	r->nRoots = nRoots;
	if (nRoots > 0) {
		r->roots = (double*)calloc(nRoots, sizeof(double));
	}
	return r;
}

//!-----------------------------------------------------
//! function to free memery from Solutions structure
//! \param [in] r Pointer to the structure to be deleted
//! 
//!-----------------------------------------------------
void Del_Solutions(Solutions* r)
{
	if (r != nullptr)
	{
		if (r->roots != nullptr) 
		{
			free(r->roots);
			r->roots = nullptr;
		}
		free(r);
		r = nullptr;
	}
}

//!-----------------------------------------------------
//! Function to checking two double for similarity
//! \param [in] a First double
//! \param [in] b Second double
//! \return Return true if a and b are the same and false otherwise
//! 
//! ----------------------------------------------------
bool Is_Same(double a, double b)
{
	return (a - b) < EPSILON && (a - b) > -EPSILON;
}

//!-----------------------------------------------------
//! Function to find the discriminant
//! \param [in] a Coefficient befor x^2
//! \param [in] b Coefficient befor x
//! \param [in] c Free coefficient
//! 
//! ----------------------------------------------------
double Evaluate_Discriminant(double a, double b, double c)
{
	return b * b - 4 * a * c;
}


//!-----------------------------------------------------
//! Function to solve linear equation
//! \param [in] b Coefficient befor x
//! \param [in] c Free coefficient
//! \return Roots of equation
//! 
//! ----------------------------------------------------
Solutions* Solve_1eq(double b, double c)
{
	if (Is_Same(b, 0.))
	{
		if (Is_Same(c, 0.))
			return Init_Solutions(INF_ROOTS);
		return Init_Solutions(0);
	}

	Solutions* r = Init_Solutions(1);
	r->roots[0] = -c / b;
	return r;
}

void swap(double *a, double *b) {
	double c = *a;
	*a = *b;
	*b = c;
}

//!-----------------------------------------------------
//! Function to solve quadratic equation
//! \param [in] a Coefficient befor x^2
//! \param [in] b Coefficient befor x
//! \param [in] c Free coefficient
//! \return Roots of equation
//! 
//! ----------------------------------------------------
Solutions* Solve_2eq(double a, double b, double c)
{
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));

	if (Is_Same(a,0.))
		return Solve_1eq(b, c);

	double d = Evaluate_Discriminant(a, b, c);

	if (Is_Same(d,0.))
	{
		Solutions* r = Init_Solutions(1);
		r->roots[0] = -b / (2 * a);
		return r;
	}

	if (d < 0)
		return Init_Solutions(0);

	double sqrt_d = sqrt(d);
	Solutions* r = Init_Solutions(2);
	r->roots[0] = (-b - sqrt_d) / (2 * a);
	r->roots[1] = (-b + sqrt_d) / (2 * a);
	if (r->roots[0] > r->roots[1])
		swap(&r->roots[0], &r->roots[1]);
	return r;
}

//!-----------------------------------------------------
//! Function to output in console line Roots structure
//! \param [in] anses Roots structure to output
//! 
//! ----------------------------------------------------
void Output_Solutions(Solutions  anses)
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
	printf("Wrong number of roots");
}