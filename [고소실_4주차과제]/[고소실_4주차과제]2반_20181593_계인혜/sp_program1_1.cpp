#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/

void sp_program1_1(FILE* fp) {

	float x0 = DBL_MAX;
	float x1;
	int n;

	fprintf(fp, "\n\tNewton_Rapson Method(FLOAT)\n");
	fprintf(fp, "n	    xn1			|f(xn1)|\n");
	scanf("%f", &x1);

	for (n = 0;; n++) {
		fprintf(fp, "%2d   %20.18e   %12.10e\n", n, x1, fabs(_sp_f(x1)));

		if (fabs(_sp_f(x1)) < DELTA || n >= Nmax || fabs((x1 - x0)) < EPSILON) break;

		x0 = x1;
		x1 = x1 - _sp_f(x1) / _sp_fp(x1);

	}
	printf("%2d   %20.18e   %12.10e\n", n, x1, fabs(_sp_f(x1)));

}
