/*!
* \file
* \brief
* File containing the definition of functions to Input and Output
*/
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

//!-----------------------------------------------------
//! Function to read coefficients of equation from console input
//! \param [out] a Pointer to variable in which coefficient befor x^2 will be written
//! \param [out] b Pointer to variable in which coefficient befor x will be written
//! \param [out] c Pointer to variable in which free coefficient will be written
//! 
//!-----------------------------------------------------
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


//!-----------------------------------------------------
//! Function to get random coefficients of equation
//! \param [out] a Pointer to variable in which coefficient befor x^2 will be written
//! \param [out] b Pointer to variable in which coefficient befor x will be written
//! \param [out] c Pointer to variable in which free coefficient will be written
//! 
//!-----------------------------------------------------
void Get_Rand_Coef(double* a, double* b, double* c)
{
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);

	*a = rand()/(rand() + 1);

	*b = rand()/(rand() + 1);

	*c = rand()/(rand() + 1);

	printf("%lg %lg %lg\n", *a, *b, *c);
}
