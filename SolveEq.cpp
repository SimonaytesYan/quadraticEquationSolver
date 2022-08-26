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
//! \param [out] structToCreate Pointer to structure to be created
//! \return Return Exit status (GOOD_EXIT_STATUS if executed corrently and BAD_EXIT_STATUS otherwise)
//! 
//!-----------------------------------------------------
int New_Polynomial(int nCoef, Polynomial *const  structToCreate)
{	
	assert(structToCreate);

	structToCreate->nCoef			= nCoef;
	structToCreate->structureStatus = ALL_RIGHT;
	if (nCoef > 0) 
	{
		structToCreate->coefficients = (double*)calloc(nCoef, sizeof(double));

		if (structToCreate->coefficients == NULL) 
		{
			structToCreate->structureStatus = DOES_NOT_EXIST;
			return BAD_EXIT_STATUS;
		}
	}

	return GOOD_EXIT_STATUS;
}

//!-----------------------------------------------------
//! Structure Polynomial destructor
//! \param [in] r Pointer to the structure to be destructed
//! 
//!-----------------------------------------------------
void Del_Polynomial(Polynomial *const r)
{
	free(r->coefficients);
	r->coefficients = nullptr;
	r->structureStatus = DOES_NOT_EXIST;
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
//! \param [in]  b      Coefficient before x
//! \param [in]  c	    Free term
//! \param [out] answer	Polinomial structure in wich the answers will be written 
//! \return				Exit status (GOOD_EXIT_STATUS if executed corrently and BAD_EXIT_STATUS otherwise)
//! 
//! ----------------------------------------------------
int  Solve_Linear_Equation(double b, double c, Polynomial* const answer)
{  
	assert(answer != NULL);
	if (!isfinite(b) || !isfinite(c))
		return BAD_EXIT_STATUS;

	if (Is_Equal(b, 0))
	{
		if (Is_Equal(c, 0))
			return New_Polynomial(INF_ROOTS, answer);

		return New_Polynomial(0, answer);;
	}

	int ExitStatus = New_Polynomial(1, answer);
	if (ExitStatus != GOOD_EXIT_STATUS)
		return ExitStatus;

	answer->coefficients[0] = -c / b;
	return GOOD_EXIT_STATUS;
}

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
//! \param [in] a		Coefficient before x^2
//! \param [in] b		Coefficient before x
//! \param [in] c		Free term
//! \param [out] answer	Polinomial structure in wich the answers will be written 
//! \return				Exit status (GOOD_EXIT_STATUS if executed corrently and BAD_EXIT_STATUS otherwise)
//! 
//! ----------------------------------------------------
int Solve_Round_Eqution(double a, double b, double c, Polynomial* const answer)
{
	if (!isfinite(a) || !isfinite(b) || !isfinite(c))
		return BAD_EXIT_STATUS;

	if (Is_Equal(a,0))
		return Solve_Linear_Equation(b, c, answer);

	double d = Evaluate_Discriminant(a, b, c);

	if (Is_Equal(d,0))
	{
		int ExitStatus = New_Polynomial(1, answer);
		if (ExitStatus == BAD_EXIT_STATUS)
			return ExitStatus;

		answer->coefficients[0] = -b / (2 * a);

		return GOOD_EXIT_STATUS;
	}

	if (d < 0)
		return New_Polynomial(0, answer);

	double sqrt_d = sqrt(d);

	int ExitStatus = New_Polynomial(2, answer);
	if (ExitStatus == BAD_EXIT_STATUS)
		return ExitStatus;

	answer->coefficients[0] = (-b - sqrt_d) / (2 * a);
	answer->coefficients[1] = (-b + sqrt_d) / (2 * a);

	if (answer->coefficients[0] > answer->coefficients[1])
		Swap_Double(&answer->coefficients[0], &answer->coefficients[1]);
	
	return GOOD_EXIT_STATUS;
}
