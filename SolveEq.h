#ifndef SOLVE_EQ	//Сделать так все .h
#define SOLVE_EQ

#include <cstddef>

const int INF_ROOTS = -1;

//!-----------------------------------------------------
//! Structure to store a solution of equation
//!-----------------------------------------------------
struct Solutions {
	int nRoots = 0;			//!<Number of roots
	union {			
		double* roots = nullptr;	//!<Dynamic array of roots
		double root;
	};
};

Solutions* Init_Solutions(int nRoots);

void Del_Solutions(Solutions* r);

bool Is_Same(double a, double b);

double Evaluate_Discriminant(double a, double b, double c);

Solutions* Solve_1eq(double b, double c);

Solutions* Solve_2eq(double a, double b, double c);

#endif // SOLVE_EQ