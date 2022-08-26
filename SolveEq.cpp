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
* File containing the definition of functions to solve round equations
*/

const double EPSILON = 1e-6;

//!-----------------------------------------------------
//! Polynomial structure constuctor 
//! \param [in] nRoots Ammount of roots in structure
//! \return Return pointer to the created structure (or null after bad allocation)
//! 
//!-----------------------------------------------------
Polynomial* New_Polynomial(int nCoef)
{
	Polynomial* now_sol = (Polynomial*)calloc(1, sizeof(Polynomial));
	if (now_sol == NULL)
		return NULL;

	now_sol->nCoef = nCoef;
	if (nCoef > 0) 
	{
		now_sol->coefficients = (double*)calloc(nCoef, sizeof(double));

		if (now_sol->coefficients == NULL) 
		{
			free(now_sol);
			return NULL;
		}
	}

	return now_sol;
}

//!-----------------------------------------------------
//! Structure Polynomial destructor
//! \param [in] r Pointer to the structure to be destructed
//! 
//!-----------------------------------------------------
void Del_Polynomial(Polynomial* r)
{
	free(r->coefficients);
	r->coefficients = nullptr;
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
//! \return		Structure Polynomial with solution data
//! 
//! ----------------------------------------------------
Polynomial* Solve_Linear_Equation(double b, double c)
{
	if (Is_Equal(b, 0))
	{
		if (Is_Equal(c, 0))
			return New_Polynomial(INF_ROOTS);
		return New_Polynomial(0);
	}

	Polynomial* r = New_Polynomial(1);
	r->coefficients[0] = -c / b;
	return r;
}


//!-----------------------------------------------------
//! Function to solve round equation
//! \param [in] a Coefficient before x^2
//! \param [in] b Coefficient before x
//! \param [in] c Free term
//! \return		Structure Polynomial with solution data
//! 
//! ----------------------------------------------------
void Swap_Double(double *a, double *b) 
{
	assert(a != NULL);
	assert(b != NULL);
	double c = *a;
	*a = *b;
	*b = c;
}

//!-----------------------------------------------------
//! Function to solve round equation
//! \param [in] a Coefficient before x^2
//! \param [in] b Coefficient before x
//! \param [in] c Free term
//! \return		Structure Polynomial with solution data
//! 
//! ----------------------------------------------------
Polynomial* Solve_Round_Eqution(double a, double b, double c)
{
	if (!isfinite(a) || !isfinite(b) || !isfinite(c))
		return nullptr;

	if (Is_Equal(a,0))
		return Solve_Linear_Equation(b, c);

	double d = Evaluate_Discriminant(a, b, c);

	if (Is_Equal(d,0))
	{
		Polynomial* r = New_Polynomial(1);
		r->coefficients[0] = -b / (2 * a);
		return r;
	}

	if (d < 0)
		return New_Polynomial(0);

	double sqrt_d = sqrt(d);
	Polynomial* r = New_Polynomial(2);
	r->coefficients[0] = (-b - sqrt_d) / (2 * a);
	r->coefficients[1] = (-b + sqrt_d) / (2 * a);

	if (r->coefficients[0] > r->coefficients[1])
		Swap_Double(&r->coefficients[0], &r->coefficients[1]);
	
	return r;
}
