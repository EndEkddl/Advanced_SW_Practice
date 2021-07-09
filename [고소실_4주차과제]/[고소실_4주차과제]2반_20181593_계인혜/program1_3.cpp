#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
	Bisection Method
**********************************************/

void program1_3(FILE* fp) {

	double x0 = DBL_MAX;
	double a0, b0, x1, temp;
	int n;

	fprintf(fp, "\n\tBisection Method\n");
	fprintf(fp, "n		xn1		|f(xn1)|\n");
	scanf("%lf %lf", &a0, &b0);
	x1 = (a0 + b0) / 2.0;

	for (n = 0; ; n++) {
	
		temp = _f(x1);
		fprintf(fp, "%2d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));

		if (fabs(temp) < DELTA || n >= Nmax || fabs(x1 - x0) < EPSILON) {
			break;
		}

		if (_f(a0) * temp > 0) a0 = x1;
		else if (_f(a0) * temp <= 0) b0 = x1;

		temp = (a0 + b0) / 2.0;
		x0 = x1; x1 = temp;
	
	}

	printf("%2d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));

	return;
}