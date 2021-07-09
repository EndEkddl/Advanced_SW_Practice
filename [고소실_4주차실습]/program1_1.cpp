#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp) {
	
	double x1; 
	int n = 0;

	fprintf(fp, "n	    xn1			|f(xn1)|\n");
	scanf("%lf", &x1);

	for (n = 0;; n++) {
		fprintf(fp, "%2d   %20.18e   %12.10e\n", n, x1, fabs(_f(x1)));
		double x2 = x1 - _f(x1) / _fp(x1);
	
		if (fabs(_f(x2)) < DELTA || n >= Nmax || fabs(x2 - x1) < EPSILON) break;
		x1 = x2;

		
	}
	printf("%2d   %20.18e   %12.10e\n", n, x1, fabs(_f(x1)));

}
