#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Secant Method
**********************************************/
void sp_program1_2(FILE* fp) {
	float x0, x1;
	int n = 0;

	fprintf(fp, "\n\tSecant Method(FLOAT)\n");
	fprintf(fp, "n	    xn1			|f(xn1)|\n");
	scanf("%f %f", &x0, &x1);

	while (1) {
		fprintf(fp, "%2d   %20.18e\n", n, x1, fabs(_sp_f(x1)));
		float x2 = x1 - _sp_f(x1) * ((x1 - x0) / (_sp_f(x1) - _sp_f(x0)));
		x0 = x1;
		x1 = x2;

		if (fabs(_sp_f(x1)) < DELTA || n >= Nmax || fabs(x1 - x0) < EPSILON) break;
		n++;
	}

	printf("%2d   %20.18e   %12.10e\n", n, x0, fabs(_sp_f(x0)));
}
