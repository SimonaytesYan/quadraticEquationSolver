#include "Header.h"

int main() 
{
	double a = 0, b = 0, c = 0;
	
	//while (true)
	//{
		//get_rand_coef(&a, &b, &c);
	get_coef(&a, &b, &c);

	Roots anses = solve_2eq(a, b, c);
	Output(anses);
	//}
	return 0;
}