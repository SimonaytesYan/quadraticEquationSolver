#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <malloc.h>
#include "SolveEq.h"
#include "InAndOut.h"

/*!
* \file
* \brief
* File containing the definition of functions to solve quadratic equations
*/

const double EPSILON = 1e-6;

//!-----------------------------------------------------
//! Solutions structure constuctor 
//! \param [in] nRoots Ammount of roots in structure
//! \return Return pointer to the created structure (or null after bad allocation)
//! 
//!-----------------------------------------------------
Solutions* Init_Solutions(int nRoots)
{
	Solutions* now_sol = (Solutions*)calloc(1, sizeof(Solutions));
	if (now_sol == NULL)
		return NULL;
	now_sol->nRoots = nRoots;
	if (nRoots > 0) 
	{
		now_sol->roots = (double*)calloc(nRoots, sizeof(double));

		if (now_sol->roots == NULL) 
		{
			free(now_sol);
			return NULL;
		}
	}
	return now_sol;
}

//!-----------------------------------------------------
//! Structure Solutions destructor
//! \param [in] r Pointer to the structure to be destructed
//! 
//!-----------------------------------------------------
void Del_Solutions(Solutions* r)
{
	free(r->roots);
	r->roots = nullptr;
	free(r);
	r = nullptr;
}

//!-----------------------------------------------------
//! Function for checking two doubles for equality
//! \param [in] a First double
//! \param [in] b Second double
//! \return Return true if a and b are the same and false otherwise
//! 
//! ----------------------------------------------------
bool Is_Equal(double a, double b)
{
	return (a - b) < EPSILON && (a - b) > -EPSILON;
}

//!-----------------------------------------------------
//! Function to evaluate the discriminant
//! \param [in] a Coefficient before x^2
//! \param [in] b Coefficient before x
//! \param [in] c Free term
//! 
//! ----------------------------------------------------
static double Evaluate_Discriminant(double a, double b, double c)
{
	return b * b - 4 * a * c;
}


//!-----------------------------------------------------
//! Function to solve linear equation
//! \param [in] b Coefficient before x
//! \param [in] c Free term
//! \return		Structure Solutions with solution data
//! 
//! ----------------------------------------------------
Solutions* Solve_Linear_Equation(double b, double c)
{
	if (Is_Equal(b, 0))
	{
		if (Is_Equal(c, 0))
			return Init_Solutions(INF_ROOTS);
		return Init_Solutions(0);
	}

	Solutions* r = Init_Solutions(1);
	r->roots[0] = -c / b;
	return r;
}

void swap(double *a, double *b) {	//!!void*
	double c = *a;
	*a = *b;
	*b = c;
}

//!-----------------------------------------------------
//! Function to solve quadratic equation
//! \param [in] a Coefficient before x^2
//! \param [in] b Coefficient before x
//! \param [in] c Free term
//! \return		Structure Solutions with solution data
//! 
//! ----------------------------------------------------
Solutions* Solve_Quadraric_Eqution(double a, double b, double c)
{
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));

	if (Is_Equal(a,0))
		return Solve_Linear_Equation(b, c);

	double d = Evaluate_Discriminant(a, b, c);

	if (Is_Equal(d,0))
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
