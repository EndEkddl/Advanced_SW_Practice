#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

//2x^3 - 12x -y -1 =0
//3y^2 -6y -x -3 = 0

void fcn3_7(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/

	fvec[0] = 2.0 * x[0] * x[0] * x[0] - 12.0 * x[0] - x[1] - 1.0;
	fvec[1] = 3.0 * x[1] * x[1] - 6.0 * x[1] - x[0] - 3.0;

	/********************************/
}

void practice3_7(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-7.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-7.txt");
		return;
	}

	/********************************/
	
	for (double i = -4; i <= 4; i += 0.5) {
		for (double j = -5; j <= 5; j += 0.5) {
			x[0] = i; x[1] = j;
			hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);
			fprintf(fp_w, "solution \tx : %lf, y: %lf\n", x[0], x[1]);
			fprintf(fp_w, "confirm   \tf1: %lf, f2: %lf, \n", fvec[0], fvec[1]);
		}
	}

	/********************************/

	fclose(fp_w);
}