#include <cstddef>

const int INF_ROOTS = -1;

//!-----------------------------------------------------
//! Structure to store a solution of equation
//!-----------------------------------------------------
struct Solutions {
	int nRoots = 0;			//!<Number of roots
	double* roots = NULL;	//!<Dynamic array of roots
};

void Output_Solutions(Solutions  anses);

Solutions* Init_Solutions(int nRoots);

void Del_Solutions(Solutions* r);

bool Is_Same(double a, double b);

double Evaluate_Discriminant(double a, double b, double c);

Solutions* Solve_1eq(double b, double c);

Solutions* Solve_2eq(double a, double b, double c);