#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "InAndOut.h"

#define _CRT_SECURE_NO_WARNINGS

/*!
* \file
* \brief
* File containing the definition of functions to Input and Output
*/

void Print_Program_Info() 
{
	printf("Round Equation Solver\n"
		"by SYM \n"
		"2022 \n\n");
}

//!-----------------------------------------------------
//! Function to output in cmd Polynomial structure
//! \param [in] answers Polynomial structure to output
//! 
//! ----------------------------------------------------
void Output_Polynomial(Polynomial*  answers)
{
	assert(answers != NULL);

	if (answers->nCoef == INF_ROOTS)
		printf("Infinity number of roots\n");

	else if (answers->nCoef == 0)
		printf("No roots\n");

	else if (answers->nCoef == 1)
		printf("x = %lg\n", answers->coefficients[0]);

	else if (answers->nCoef > 1)
	{
		for (int i = 0; i < answers->nCoef; i++)
			printf("x%d = %lg ", i + 1, answers->coefficients[i]);

		printf("\n");
	}
	else 
		printf("Wrong number of roots");
}

//!-----------------------------------------------------
//! Function clean cmd buffer
//! \return amount cleared symbols
//! 
//!-----------------------------------------------------
int Clean_Buffer()
{
	int cnt = 0;
	while ((getchar()) != '\n') 
		cnt++;
	return cnt;
}

//!-----------------------------------------------------
//! Function read one double variable from file with checking correct format
//! \param [out] a Pointer to variable in which file input will be written
//! \param [in] fp Pointer to file from which value of variable will be read
//! 
//!-----------------------------------------------------
void Get_One_Double_From_File(FILE* fp, double* a) 
{
	assert(fp != nullptr);
	assert(fscanf(fp, "%lg", a));
}

//!-----------------------------------------------------
//! Function read one int variable from file with checking correct format
//! \param [out] a Pointer to variable in which file input will be written
//! \param [in] fp Pointer to file from which value of variable will be read
//! 
//!-----------------------------------------------------
void Get_One_Int_From_File(FILE* fp, int* a) 
{
	assert(fp != nullptr);
	assert(fscanf(fp, "%d", a));
}

//!-----------------------------------------------------
//! Function to print message (in cmd) and then read one double variable (from cmd) with checking for correct format
//! \param [out] a	  Pointer to variable in which cmd input will be written
//! \param [in] print Text that will be output to the cmd befor reading value of variable
//! 
//!-----------------------------------------------------
void Get_One_Coef_From_Console(double *a, const char *print) 
{
	assert(a != NULL);
	assert(print != NULL);

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
//! \param [out] a Pointer to variable in which coefficient before x^2 will be written
//! \param [out] b Pointer to variable in which coefficient before x will be written
//! \param [out] c Pointer to variable in which free term will be written
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
//! \param [out] a Pointer to variable in which coefficient before x^2 will be written
//! \param [out] b Pointer to variable in which coefficient before x will be written
//! \param [out] c Pointer to variable in which free term will be written
//! 
//!-----------------------------------------------------
void Get_Rand_Coef(double* a, double* b, double* c)
{
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);

	*a = rand()/(double)(rand() + 1) * (rand() % 3 - 1);

	*b = rand()/(double)(rand() + 1) * (rand() % 3 - 1);

	*c = rand()/(double)(rand() + 1) * (rand() % 3 - 1);

	printf("%lg %lg %lg\n", *a, *b, *c);
}
