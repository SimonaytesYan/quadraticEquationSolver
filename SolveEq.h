#include <cstddef>

const int INF_ROOTS = -1;

struct Roots {
	int nRoots = 0;
	double* roots = NULL;
};

void Output(Roots anses);

Roots Init_Roots(int nRoots);

void Del_Roots(Roots* r);

bool Is_Same(double a, double b);

double Evaluate_Discriminant(double a, double b, double c);

Roots Solve_1eq(double b, double c);

Roots Solve_2eq(double a, double b, double c);