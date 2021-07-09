#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

double linearEquation(double* fx, double* fy, int idx, double x1) {
	// 선형보간 : (xm, pxm), (xm+1, pxm+1)을 지나는 직선의 방정식
	return (((fy[idx + 1] - fy[idx]) / (fx[idx + 1] - fx[idx])) * (x1 - fx[idx])) + fy[idx];
}
double bisectionMethod(double* fx, double* fy, int n, double h, double u) {
	double x0 = 0.0, x1 = 1.0;
	double a0 = 0.0, b0 = 1.0;
	int i, a, s;// a : 직전의 샘플링 지점

	x1 = (a0 + b0) / 2;

	for (i = 0; ; i++) {
		for (a = 0; a < n; a++) {
			if (a * h <= a0 && a0 < (a + 1) * h) break;
		}
		for (s = 0; s < n; s++) {
			if (s * h <= x1 && x1 < (s + 1) * h) break;
		}
		double tmp = linearEquation(fx, fy, s, x1);
		if (fabs(tmp - u) < DELTA || i >= Nmax || fabs(x1 - x0) < EPSILON) {
			break;
		}
		double t1, t2;
		t1 = linearEquation(fx, fy, a, a0) - u;
		t2 = linearEquation(fx, fy, s, x1) - u;

		if (t1 * t2 < 0) b0 = x1;
		else a0 = x1;

		tmp = (a0 + b0) / 2;
		x0 = x1;
		x1 = tmp;
	}

	return x1;

}
double trapezoidal(double* ax, double* ay, int n, double h, double start, double end) {
	double area = 0;
	int e;

	for (e = 0; e < n; e++) {
		if (e * h <= end && end < (e + 1) * h) break;
	}

	for (int i = 0; i <= e; i++) {
		if (i == 0 || i == e) area += ay[i];
		else area += 2 * ay[i];
	}

	area = area / 2 * h;

	return area;
}
void program2_2()
{
	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/
	int n, userN;
	double h, u;
	double x = 0, tmp = 0;

	scanf("%d", &userN);

	fscanf(fp_r, "%d %lf", &n, &h);
	double* ax = (double*)malloc(sizeof(double) * n);
	double* ay = (double*)malloc(sizeof(double) * n);
	double* fx = (double*)malloc(sizeof(double) * n);
	double* fy = (double*)malloc(sizeof(double) * n);

	for (int i = 0; i < n; i++) {
		fscanf(fp_r, "%lf %lf", &ax[i], &ay[i]);
		fx[i] = ax[i];
		fy[i] = trapezoidal(ax, ay, n, h, 0, fx[i]);
	}
	for (int i = userN; i > 0; i--) {
		u = (double)rand() / RAND_MAX;
		x = bisectionMethod(fx, fy, n, h, u);
		printf("%.15lf\n", x);
		fprintf(fp_w, "%.15lf\n", x);
	}


	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
