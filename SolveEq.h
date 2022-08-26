#ifndef SOLVE_EQ	//Сделать так все .h
#define SOLVE_EQ

#include <cstddef>

const int INF_ROOTS = -1;

//!-----------------------------------------------------
//! Structure to store a solution of equation
//!-----------------------------------------------------
struct Solutions {
	int nRoots = 0;			//!<Number of roots
	double* roots = nullptr;	//!<Dynamic array of roots
};

Solutions* Init_Solutions(int nRoots);

void Del_Solutions(Solutions* r);

bool Is_Equal(double a, double b);

Solutions* Solve_Linear_Equation(double b, double c);

Solutions* Solve_Round_Eqution(double a, double b, double c);

#endif // SOLVE_EQ