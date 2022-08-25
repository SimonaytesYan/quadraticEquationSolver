#define _CRT_SECURE_NO_WARNINGS
#include "SolveEq.h"
#include "ConsoleHandler.h"
#include "InAndOut.h"
#include <assert.h>
#include <windows.h>
#include <stdio.h>

const int GREEN = 10;
/*!
* \file
* \brief 
* Main file from which the execution of the program begins with functions to testing
*/

/*! \mainpage Quadratic Equation Solver 
 *	by SYM 
 *  2022
 *
 * \section intro_sec Console flags
 * 
 * \subsection step1 -s
 * Use -s to run program in interaction mode
 * 
 * \subsection step2 -t
 * Use -t to run Unit tests
 * 
 * \subsection step3 -f
 * Use -f to specify a custom file from which the unit test will be read.
 * File path incroduced after -f flag
 */

const char * DEFAULT_TESTS_PATH = "UnitTests.txt";

//!-------------------------------------------------
//! Function to read test condition and correst answers to it
//! \param [in]  fp    Pointer to file which the information will be read
//! \param [out] A     Pointer to variable in which coefficient befor x^2 will be written
//! \param [out] B     Pointer to variable in which coefficient befor x will be written
//! \param [out] C     Pointer to variable in which free coefficient will be written
//! \param [out] r_ans Pointer to structure in which correct answer will be written
//! 
//! ------------------------------------------------
void Get_Test_From_File(FILE *fp, double* A, double* B, double* C, Solutions** r_ans)
{
	assert(fp != nullptr);
	assert(r_ans != nullptr);
    int nRoots = 0;

	fscanf(fp, "%lg %lg %lg", A, B, C);	//!
	fscanf(fp, "%d", &nRoots);

	*r_ans = Init_Solutions(nRoots);

	for (int j = 0; j < nRoots; j++) {
		fscanf(fp, "%lg", &((*r_ans)->roots[j]));
	}
}

//!-------------------------------------------------
//! Function to run test
//! \param [in] a     Test contidion. Coefficient befor x^2 will be written
//! \param [in] b     Test contidion. Coefficient befor x will be written
//! \param [in] c     Test contidion. Coefficient will be written
//! \param [in] r_ans Answer to test. Structure Solutions
//! \param [out] ans  Pointer to pointer to structure in which program answer will be written
//! \return true if test passed and false otherwise
//! 
//! ------------------------------------------------
bool Test_2equ(double a, double b, double c, Solutions *correct_ans, Solutions **program_ans)
{
	assert(correct_ans != nullptr);
	assert(program_ans != nullptr);

	*program_ans = Solve_2eq(a, b, c);

	if ((*program_ans)->nRoots != correct_ans->nRoots)
		return false;

	for (int i = 0; i < correct_ans->nRoots; i++) {
		if (!Is_Same((*program_ans)->roots[i], correct_ans->roots[i]))
			return false;
	}

	return true;
}

//!-------------------------------------------------
//! Function to launch group test from file
//! \param [in] CL ConsoleLine structure which has information about launch conditions from the console
//! 
//! ------------------------------------------------
void Launch_Tests(LaunchAttributes CL) //!!
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Обернуть функцию покраски консоли в IFDEF для windows и linux

    FILE* fp = nullptr;
	if (CL.test_from_file) {

		if (CL.test_file_name != nullptr) {
			fp = fopen(CL.test_file_name, "r");
		}

		if (fp == nullptr)
		{
			printf("WARNING: No custom tests were found\n"
				"Default tests will be run\n");
			fp = fopen(DEFAULT_TESTS_PATH, "r");
		}
	}
	else 
		fp = fopen(DEFAULT_TESTS_PATH, "r");

	if (fp == nullptr)
	{
        printf("No default tests were found\n");
        return;
	}

	int TestN = 0;
	fscanf(fp, "%d", &TestN); ////////!

	for (int i = 0; i < TestN; i++)
	{
        printf("TEST %d: ", i);

		double A = 0;
		double B = 0;
		double C = 0;
		Solutions* r_ans = nullptr;  ////!
        Get_Test_From_File(fp, &A, &B, &C, &r_ans);

		Solutions* g_ans = nullptr; /////!
        bool isPassed = Test_2equ(A, B, C, r_ans, &g_ans);


        if (isPassed) {
			SetConsoleTextAttribute(hConsole, 10);			
            printf("Passed!\n");										//! IMPLEMENT PRINT WITH COLOUR SUPPORT
			SetConsoleTextAttribute(hConsole, 15);
		}
        else {
			SetConsoleTextAttribute(hConsole, 12);
            printf("FAILED!!!\n");
			SetConsoleTextAttribute(hConsole, 15);

			printf("Correct number of roots = %d", r_ans->nRoots);
            printf("Right answer: ");
			for (int i1 = 0; i1 < r_ans->nRoots; i1++) {
				printf("%lg ", r_ans->roots[i]);
			}
			printf("\n");

			printf("Received number of roots = %d", g_ans->nRoots);
			printf("Received answer: ");
			for (int i1 = 0; i1 < g_ans->nRoots; i1++) {
				printf("%lg ", g_ans->roots[i]);
            }
			printf("\n");
        }

        Del_Solutions(g_ans);
        Del_Solutions(r_ans);
    }
}

int main(int argc, const char* argv[])
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	printf("Quadratic Equation Solver\n"
				 "by SYM \n"
				 "2022 \n\n");

	LaunchAttributes CL = Parse_Console(argc, argv);

	switch (CL.mode)
	{
	case INTERACTION_MODE:
	{
		double a = 0;
		double b = 0;
		double c = 0;

		Get_Coef(&a, &b, &c);

		Solutions* anses = Solve_2eq(a, b, c);
		Output_Solutions(*anses);
		Del_Solutions(anses);
		break;
	}
	case UNIT_TEST_MODE:
	{
        Launch_Tests(CL);
	}
	break;
	default:
		printf("Wrong operation mode\n");
	}
}
