#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdio.h>
#include "InAndOut.h"

/*!
* \file
* \brief
* File containing the definition of functions to Input and Output
*/


//!-----------------------------------------------------
//! Function to output in console line Roots structure
//! \param [in] anses Roots structure to output
//! 
//! ----------------------------------------------------
void Output_Solutions(Solutions*  anses)
{
	if (anses == nullptr)
		return;
	if (anses->nRoots == INF_ROOTS)
	{
		printf("Infinity number of roots\n");
	}
	else if (anses->nRoots == 0)
	{
		printf("No roots\n");
	}
	else if (anses->nRoots == 1) {
		printf("x = %lg\n", anses->roots[0]);
	}
	else if (anses->nRoots > 1)
	{
		for (int i = 0; i < anses->nRoots; i++)
		{
			printf("x%d = %lg ", i + 1, anses->roots[i]);
		}
		printf("\n");
	}
	else 
		printf("Wrong number of roots");
}

int Clean_Buffer()
{
	int cnt = 0;
	while ((getchar()) != '\n') 
	{
		cnt++;
	}
	return cnt;
}

void Get_One_Coef_From_Console(double *a, char *print) {
	do {
		printf("%s\n", print);
		while (!scanf("%lg", a))
		{
			Clean_Buffer();
			printf("Wrong format. Try again\n");
		}
	} while (Clean_Buffer());
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

	Get_One_Coef_From_Console(a, "Enter the coefficient for x^2");

	Get_One_Coef_From_Console(b, "Enter the coefficient for x");
	
	Get_One_Coef_From_Console(c, "Enter the free coefficient");
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
