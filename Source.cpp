#define _CRT_SECURE_NO_WARNINGS
#include "SolveEq.h"
#include "ConsoleHandler.h"
#include "InAndOut.h"
#include <assert.h>
#include <stdio.h>

const char * DEFAULT_TESTS_PATH = "UnitTests.txt";

void Get_Test_From_File(FILE *fp, double* A, double* B, double* C, Roots* r_ans)
{
	assert(fp != NULL);
	assert(r_ans != NULL);
    int nRoots = 0;

	fscanf(fp, "%lg %lg %lg", A, B, C);
	printf("a = %lg\n"
		"b = %lg\n"
		"c = %lg\n", *A, *B, *C);
	fscanf(fp, "%d", &nRoots);
	printf("Nroots = %d\n", nRoots);

	*r_ans = Init_Roots(nRoots);
	printf("Roots created\n");

	for (int j = 0; j < nRoots; j++) {
		fscanf(fp, "%lg", &r_ans->roots[j]);
		printf("%lg ", r_ans->roots[j]);
	}
	printf("\n");
}

bool Test_2equ(double a, double b, double c, Roots *r_ans, Roots *ans)
{
	assert(r_ans != NULL);
	assert(ans != NULL);

	*ans = Solve_2eq(a, b, c);

	printf("Equ solved\n");
	printf("Right nRoots = %d\n", r_ans->nRoots);
	printf("Got nRoots = %d\n", ans->nRoots);
	if (ans->nRoots != r_ans->nRoots)
		return false;

	printf("Right nRoots\n");
	for (int i = 0; i < r_ans->nRoots; i++) {
		if (!Is_Same(ans->roots[i], r_ans->roots[i]))
			return false;
	}
	printf("End test\n");

	return true;
}

void Launch_Tests(ConsoleLine CL)
{
    FILE* fp = NULL;
	if (CL.test_from_file) {
		if (CL.test_file_name != NULL) {
			fp = fopen(CL.test_file_name, "r");
		}

		if (fp == NULL && CL.test_from_file)
		{
			printf("WARNING: No custom tests were found\n"
				"Default tests will be open\n");
			fp = fopen(DEFAULT_TESTS_PATH, "r");
		}
	}
	else 
		fp = fopen(DEFAULT_TESTS_PATH, "r");

	if (fp == NULL)
	{
        printf("No default tests were found\n");
        return;
	}
	assert(fp != NULL);

	int TestN = 0;
	fscanf(fp, "%d", &TestN);

	printf("TestN = %d\n", TestN);
	for (int i = 0; i < TestN; i++)
	{
        printf("TEST %d: \n", i);

		double A = 0;
		double B = 0;
		double C = 0;
		Roots r_ans = {};
        Get_Test_From_File(fp, &A, &B, &C, &r_ans);
		printf("Coef and Answer has been gotten\n");

		Roots g_ans = {};
        bool isPassed = Test_2equ(A, B, C, &r_ans, &g_ans);

        if (isPassed)
            printf("Passed!\n");
        else {
            printf("FAILED!!!\n");

            printf("Right answer: ");
			for (int i1 = 0; i1 < r_ans.nRoots; i1++) {
				printf("%lg ", r_ans.roots[i]);
			}
			printf("\n");

			printf("Received answer: ");
			for (int i1 = 0; i1 < g_ans.nRoots; i1++) {
				printf("%lg ", g_ans.roots[i]);
            }
			printf("\n");
        }

        Del_Roots(&g_ans);
        Del_Roots(&r_ans);
    }
}

int main(int argc, const char* argv[])
{
	printf("Quadratic Equation Solver\n"
				 "by SYM \n"
				 "2022 \n\n");

	ConsoleLine CL = Parse_Console(argc, argv);

	switch (CL.mode)
	{
	case INTERACTION_MODE:
	{
		double a = 0;
		double b = 0;
		double c = 0;

		Get_Coef(&a, &b, &c);

		Roots anses = Solve_2eq(a, b, c);
		Output(anses);
		Del_Roots(&anses);
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
