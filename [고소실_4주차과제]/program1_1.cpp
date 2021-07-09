#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp)
{
	double x0 = DBL_MAX;
	double x1;
	int n;
	fprintf(fp, "\n\tNewton_Rapson Method\n");
	fprintf(fp, " n              xn1                  |f(xn1)|\n");
	scanf("%lf", &x1);

	for (n = 0; ; n++) {
		fprintf(fp, "%2d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));

		if (fabs(_f(x1)) < DELTA || n >= Nmax || fabs(x1 - x0) < EPSILON)
			break;

		x0 = x1;
		x1 = x1 - _f(x1) / _fp(x1);

	}
	printf("%2d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));
}