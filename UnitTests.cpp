#include "Header.h"

double TestN = 13;

double A[] = { 0,0,0,0,1,1,1,1,3,-1,4,2,1 };
double B[] = { 0,0,1,1,0,0,1,1,7,7,4,1,2 };
double C[] = { 0,1,0,1,0,1,0,1,-6,8,1,1,1 };

double NRoot[] = { INF_ROOTS, 0, 1, 1, 1, 0, 2, 0, 2, 2, 1, 0, 1};
double Anses[][2] = { {0,0}, {0,0}, {0,0}, {-1,0}, {0,0}, {0,0}, {1,-1}, {0,0}, {2 / 3., -3}, {-1,8}, {-0.5, 0}, {0,0}, {-1,-1} };

bool Test(double a, double b, double c, double nRoots, double r_ans[2]) {
	Roots ans = solve_2eq(a, b, c);
	
	if (ans.nRoots != nRoots)
		return false;

	for (int i = 0; i < nRoots; i++) {
		if (ans.roots[i] != r_ans[i])
			return false;
	}

	return true;
}

int main() {

	printf("LOL");
	/*for (int i = 0; i < TestN; i++) {
		printf("TEST %d: ", i);
		bool isPassed = Test(A[i], B[i], C[i], NRoot[i], Anses[i]);
		if (isPassed)
			printf("Passed!\n");
		else
			printf("DONT PASSED!!!\n");
	}*/
	return 0;
}
