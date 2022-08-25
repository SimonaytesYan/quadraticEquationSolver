#ifndef UNIT_TEST
#define UNIT_TEST

#include "SolveEq.h"
#include "InAndOut.h"
#include <stdio.h>

void Get_Test_From_File(FILE* fp, double* A, double* B, double* C, Solutions** Correct_ans);

bool Test_Quadraric_Eqution(double a, double b, double c, Solutions* correct_ans, Solutions** program_ans);

void Launch_Tests(LaunchAttributes Launch_Attrib);

#endif //UNIT_TEST