#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/

void sp_program1_1(FILE* fp) {
	
	float x1;
	int n;

	fprintf(fp, "n	    xn1			|f(xn1)|\n");
	scanf("%f", &x1);

	for (n=0;; n++) {
		fprintf(fp, "%2d   %20.18e   %12.10e\n", n, x1, fabs(_sp_f(x1)));
	
		float x2 = x1 - _sp_f(x1) / _sp_fp(x1);
	
		x1 = x2;

		if (fabs(_sp_f(x2)) < DELTA || n >= Nmax || fabs(x2 - x1) < EPSILON) break;

	}
	printf("%2d   %20.18e   %12.10e\n", n, x1, fabs(_sp_f(x1)));
	
}
