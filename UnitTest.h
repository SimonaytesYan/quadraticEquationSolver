#ifndef UNIT_TEST
#define UNIT_TEST

#include <stdio.h>

#include "SolveEq.h"
#include "InAndOut.h"

void Get_Test_From_File(FILE* fp, double* A, double* B, double* C, Solutions** Correct_ans);

bool Test_Round_Eqution(double a, double b, double c, Solutions* correct_ans, Solutions** program_ans);

void Launch_Tests_For_Round_Equation_Solver(LaunchAttributes Launch_Attrib);

FILE* Open_Test_File(LaunchAttributes Launch_Attrib);

#endif //UNIT_TEST