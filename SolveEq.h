#ifndef SOLVE_EQ	//Сделать так все .h
#define SOLVE_EQ

#include <cstddef>

const int INF_ROOTS = -1;

//!-----------------------------------------------------
//! Structure to store a solution of equation
//!-----------------------------------------------------
struct Polynomial {
	int nCoef = 0;			//!<Number of roots
	double* coefficients = nullptr;	//!<Dynamic array of roots
};

Polynomial* New_Polynomial(int nRoots);

void Del_Polynomial(Polynomial* r);

bool Is_Equal(double a, double b);

Polynomial* Solve_Linear_Equation(double b, double c);

Polynomial* Solve_Round_Eqution(double a, double b, double c);

#endif // SOLVE_EQ