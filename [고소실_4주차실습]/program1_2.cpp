#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/
void program1_2(FILE* fp) {
	double x0, x1;
	int n = 0;

	fprintf(fp, "n	    xn1			|f(xn1)|\n");
	scanf("%lf %lf", &x0, &x1);

	while (1) {
		fprintf(fp, "%2d   %20.18e\n", n, x1, fabs(_f(x1)), fabs(x1-x0));
		double x2 = x1 - _f(x1) * ((x1 - x0)/ (_f(x1) - _f(x0)));
		x0 = x1;
		x1 = x2;

		if (fabs(_f(x1)) < DELTA || n >= Nmax || fabs(x1 - x0) < EPSILON) break;
		
		n++;
	}
	printf("%2d   %20.18e   %12.10e		\n", n, x0, fabs(_f(x0)));
	
}
