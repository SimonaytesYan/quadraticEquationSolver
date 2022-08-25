#include "SolveEq.h"
#include "InAndOut.h"
#include "ConsoleHandler.h"
#include "UnitTest.h"
#include <assert.h>
#include <windows.h>
#include <stdio.h>

const char* DEFAULT_TESTS_PATH = "UnitTests.txt";
//!-------------------------------------------------
//! Function to read test condition and correst answers to it
//! \param [in]  fp    Pointer to file which the information will be read
//! \param [out] A     Pointer to variable in which coefficient befor x^2 will be written
//! \param [out] B     Pointer to variable in which coefficient befor x will be written
//! \param [out] C     Pointer to variable in which free coefficient will be written
//! \param [out] r_ans Pointer to structure in which correct answer will be written
//! 
//! ------------------------------------------------
void Get_Test_From_File(FILE* fp, double* A, double* B, double* C, Solutions** Correct_ans)
{
	assert(fp != nullptr);
	assert(Correct_ans != nullptr);
	int nRoots = 0;

	Get_One_Double_From_File(fp, A);
	Get_One_Double_From_File(fp, B);
	Get_One_Double_From_File(fp, C);
	Get_One_Int_From_File(fp, &nRoots);

	*Correct_ans = Init_Solutions(nRoots);

	for (int j = 0; j < nRoots; j++) {
		Get_One_Double_From_File(fp, &((*Correct_ans)->roots[j]));
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
bool Test_Quadraric_Eqution(double a, double b, double c, Solutions* correct_ans, Solutions** program_ans)
{
	assert(correct_ans != nullptr);
	assert(program_ans != nullptr);

	*program_ans = Solve_Quadraric_Eqution(a, b, c);

	if ((*program_ans)->nRoots != correct_ans->nRoots)
		return false;

	for (int i = 0; i < correct_ans->nRoots; i++) {
		if (!Is_Equal((*program_ans)->roots[i], correct_ans->roots[i]))
			return false;
	}

	return true;
}

//!-------------------------------------------------
//! Function to launch group test from file
//! \param [in] CL ConsoleLine structure which has information about launch conditions from the console
//! 
//! ------------------------------------------------
void Launch_Tests(LaunchAttributes Launch_Attrib)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FILE* fp = nullptr;					//Отдельная функция
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
		return;
	}

	int TestN = 0;
	Get_One_Int_From_File(fp, &TestN);

	for (int i = 0; i < TestN; i++)
	{
		printf("TEST %d: ", i);

		double A = 0;
		double B = 0;
		double C = 0;
		Solutions* correct_ans = nullptr;
		Get_Test_From_File(fp, &A, &B, &C, &correct_ans);

		Solutions* program_ans = nullptr;
		bool isPassed = Test_Quadraric_Eqution(A, B, C, correct_ans, &program_ans);

		if (isPassed) {
			SetConsoleTextAttribute(hConsole, GREEN);
			printf("Passed!\n");
			SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
		}
		else {
			SetConsoleTextAttribute(hConsole, RED);
			printf("FAILED!!!\n");
			SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

			printf("Correct number of roots = %d\n", correct_ans->nRoots);
			printf("Right answer: ");
			for (int i1 = 0; i1 < correct_ans->nRoots; i1++) {
				printf("%lg ", correct_ans->roots[i]);
			}
			printf("\n");

			printf("Received number of roots = %d\n", program_ans->nRoots);
			printf("Received answer: ");
			for (int i1 = 0; i1 < program_ans->nRoots; i1++) {
				printf("%lg ", program_ans->roots[i]);
			}
			printf("\n");
		}

		Del_Solutions(correct_ans);
		Del_Solutions(program_ans);
	}
	fclose(fp);
}
