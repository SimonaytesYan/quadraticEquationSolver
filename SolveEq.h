#ifndef SOLVE_EQ	//Сделать так все .h
#define SOLVE_EQ

#include <cstddef>

const int INF_ROOTS = -1;

enum POLYNOMIAL_STRUCTURE_STATUS
{
	ALL_RIGHT		 = 0,
	DOES_NOT_EXIST   = -1,
	BAD_COEFF		 = -2
};

enum FUNCTION_EXIT_STATUS 
{
	BAD_EXIT_STATUS  = -1,
	GOOD_EXIT_STATUS = 0
};

//!-----------------------------------------------------
//! Structure to store a solution of equation
//!-----------------------------------------------------
struct Polynomial 
{
	int nCoef = 0;					//!<Number of roots
	double* coefficients = nullptr;	//!<Dynamic array of roots
	int structureStatus = -1;		/**
									 *<Its 0  if its OK 
									 *<Its -1 if structure has been deleted or hasnt been created
									 *<Its -2 if coefficients are incorrect
									 */
};

int New_Polynomial(int nCoef, Polynomial *const  structToCreate);

void Del_Polynomial(Polynomial *const r);

bool Is_Equal(double a, double b);

int Solve_Linear_Equation(double b, double c, Polynomial* const answer);

int Solve_Round_Eqution(double a, double b, double c, Polynomial* const answer);

#endif // SOLVE_EQ