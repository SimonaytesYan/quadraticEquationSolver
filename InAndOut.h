#ifndef IN_AND_OUT
#define IN_AND_OUT

#include <stdio.h>

#include "SolveEq.h"

enum CONSOLE_COLORS {
    GREEN         = 10,
    RED           = 12,
    YELLOW        = 14,
    DEFAULT_COLOR = 15
};


int Clean_Buffer();

void Get_Rand_Coef(double* a, double* b, double* c);

void Get_One_Coef_From_Console(double* a, const char* print);

void Get_One_Double_From_File(FILE* fp, double* a);

void Get_One_Int_From_File(FILE* fp, int* a);

void Get_Coef(double* a, double* b, double* c);

void Output_Polynomial(Polynomial*  anses);

void Print_Program_Info();

#endif //IN_AND_OUT