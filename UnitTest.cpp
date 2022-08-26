#include <assert.h>
#include <windows.h>
#include <stdio.h>

#include "SolveEq.h"
#include "InAndOut.h"
#include "CLIHandler.h"
#include "UnitTest.h"

const char* DEFAULT_TESTS_PATH = "UnitTests\\UnitTests.txt";

/*!
* \file
* \brief
* File containing the definition of functions to test solving 
*/

//!-------------------------------------------------
//! Function to read test condition and correst answers to it
//! \param [in]  fp    Pointer to file which the information will be read
//! \param [out] A     Pointer to variable in which coefficient befor x^2 will be written
//! \param [out] B     Pointer to variable in which coefficient befor x will be written
//! \param [out] C     Pointer to variable in which free coefficient will be written
//! \param [out] r_ans Pointer to structure in which correct answer will be written
//! 
//! ------------------------------------------------
void Get_Test_From_File(FILE* fp, double* A, double* B, double* C, Polynomial** Correct_ans)
{
	assert(A != NULL);
	assert(B != NULL);
	assert(C != NULL);
	assert(fp != nullptr);
	assert(Correct_ans != nullptr);

	int nRoots = 0;

	Get_One_Double_From_File(fp, A);
	Get_One_Double_From_File(fp, B);
	Get_One_Double_From_File(fp, C);
	Get_One_Int_From_File(fp, &nRoots);

	*Correct_ans = New_Polynomial(nRoots);

	for (int j = 0; j < nRoots; j++) {
		Get_One_Double_From_File(fp, &((*Correct_ans)->coefficients[j]));
	}
}

//!-------------------------------------------------
//! Function to run test
//! \param [in] a     Test contidion. Coefficient befor x^2 will be written
//! \param [in] b     Test contidion. Coefficient befor x will be written
//! \param [in] c     Test contidion. Coefficient will be written
//! \param [in] r_ans Answer to test. Structure Polynomial
//! \param [out] ans  Pointer to pointer to structure in which program answer will be written
//! \return true if test passed and false otherwise
//! 
//! ------------------------------------------------
bool Test_Round_Eqution(double a, double b, double c, Polynomial* correct_ans, Polynomial** program_ans)
{
	assert(correct_ans != nullptr);
	assert(program_ans != nullptr);

	*program_ans = Solve_Round_Eqution(a, b, c);

	if ((*program_ans)->nCoef != correct_ans->nCoef)
		return false;

	for (int i = 0; i < correct_ans->nCoef; i++) {
		if (!Is_Equal((*program_ans)->coefficients[i], correct_ans->coefficients[i]))
			return false;
	}

	return true;
}

//!-------------------------------------------------
//! Function to open file from which Tests will be read
//! \param [in] Launch_Attrib LaunchAttributes structure which has information about launch conditions from cmd (including custom test file name)
//! 
//! ------------------------------------------------
FILE* Open_Test_File(LaunchAttributes Launch_Attrib) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FILE *fp = nullptr;

	if (Launch_Attrib.test_from_custom_file) {

		if (Launch_Attrib.test_file_name != nullptr) {
			fp = fopen(Launch_Attrib.test_file_name, "r");
		}

		if (fp == nullptr)
		{
			SetConsoleTextAttribute(hConsole, YELLOW);
			printf("WARNING: No custom tests were found\n"
				   "Default tests will be run\n");
			SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
			fp = fopen(DEFAULT_TESTS_PATH, "r");
		}
	}
	else
		fp = fopen(DEFAULT_TESTS_PATH, "r");

	if (fp == nullptr)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("No default tests were found\n");
		SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
	}
	return fp;
}

//!-------------------------------------------------
//! Function to print "FAILED" and some debug information if isPassed false are different and "PASSED" othervise
//! \param [in] isPassed	Variable indicating whether the test in question passed
//! \param [in] program_ans Programmic response to a run test 				   
//! \param [in] correct_ans Correct answer to a run test 
//! 
//! ------------------------------------------------
void Print_Test_Result(bool isPassed, Polynomial* program_ans, Polynomial* correct_ans)
{
	assert(program_ans != NULL);
	assert(correct_ans != NULL);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (isPassed) 
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("Passed!\n");
		SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
	}
	else 
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("FAILED!!!\n");
		SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

		printf("Correct number of roots = %d\n", correct_ans->nCoef);
		if (correct_ans->nCoef > 0) 
		{
			printf("Correct answer: ");
			for (int i1 = 0; i1 < correct_ans->nCoef; i1++)
				printf("%lg ", correct_ans->coefficients[i1]);

			printf("\n");
		}
	
		printf("Received number of roots = %d\n", program_ans->nCoef);
		if (program_ans->nCoef > 0) 
		{
			printf("Received answer: ");
			for (int i1 = 0; i1 < program_ans->nCoef; i1++)
				printf("%lg ", program_ans->coefficients[i1]);

			printf("\n");
		}
	}

}

//!-------------------------------------------------
//! Function to launch group test from file
//! \param [in] Launch_Attrib LaunchAttributes structure which has information about launch conditions from cmd
//! 
//! ------------------------------------------------
void Launch_Tests_For_Round_Equation_Solver(LaunchAttributes Launch_Attrib)
{
	FILE* fp = Open_Test_File(Launch_Attrib);

	if (fp == nullptr)
		return;

	int TestN = 0;
	Get_One_Int_From_File(fp, &TestN);

	for (int i = 0; i < TestN; i++)
	{
		printf("TEST %d: ", i);

		double A = 0;
		double B = 0;
		double C = 0;
		Polynomial* correct_ans = nullptr;
		Get_Test_From_File(fp, &A, &B, &C, &correct_ans);

		Polynomial* program_ans = nullptr;
		bool isPassed = Test_Round_Eqution(A, B, C, correct_ans, &program_ans);

		Print_Test_Result(isPassed, program_ans, correct_ans);

		Del_Polynomial(correct_ans);
		Del_Polynomial(program_ans);
	}
	fclose(fp);
}
