#ifndef IN_AND_OUT
#define IN_AND_OUT

#include <stdio.h>

#include "SolveEq.h"

const int GREEN         = 10;
const int RED           = 12;
const int YELLOW        = 14;
const int DEFAULT_COLOR = 15;

int Clean_Buffer();

void Get_Rand_Coef(double* a, double* b, double* c);

void Get_One_Coef_From_Console(double* a, const char* print);

void Get_One_Double_From_File(FILE* fp, double* a);

void Get_One_Int_From_File(FILE* fp, int* a);

void Get_Coef(double* a, double* b, double* c);

void Output_Solutions(Solutions*  anses);

void Print_Program_Info();

#endif //IN_AND_OUT