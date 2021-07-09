#include "my_solver.h"
double integral(double start, double end, int n, double* xx, double* yy) {
	
	double area = 0;

	double h = (double)1 / (double)(n - 1);
	int s, e;

	for (s = 0; s < n; s++) {
		if (s * h >= start && start < (double)(s + 1) * h) break;
	}
	for (e = 0; e < n; e++) {
		if (e * h >= end && end < (e + 1) * h) break;
	}

	for (int i = s; i <= e; i++) {
		if (i == s || i == e) area += yy[i];
		else area += 2 * yy[i];
	}

	area = area / 2 * h;

	return area;

}
void program2_1()
{
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/

	int n;

	double h;
	double area = 0;

	fscanf(fp_r, "%d %lf", &n, &h);
	double* xx = (double*)malloc(sizeof(double) * n);
	double* yy = (double*)malloc(sizeof(double) * n);

	for (int i = 0; i < n; i++) {
		fscanf(fp_r, "%lf %lf", &xx[i], &yy[i]);

		if (i == 0 || i == n-1) area += yy[i]; // 양 끝은 한 번만 더함
		else area += 2 * yy[i];
	}


	h = (double)1 / (n - 1);
	area = area * h / 2;


	for (int i = 0; i < n; i++) {
		xx[i] = i * h; //0~1
		yy[i] /= area; //합이 1이 되도록 정규화
	}

	printf("*** Integrating the pdf from 0.0 to 1.0 = %lf\n", integral(0.0, 1.0, n, xx, yy));
	printf("*** Integrating the pdf from 0.0 to 0.25 = %lf\n", integral(0.0, 0.25, n, xx, yy));
	printf("*** Integrating the pdf from 0.25 to 0.5 = %lf\n", integral(0.25, 0.5, n, xx, yy));
	printf("*** Integrating the pdf from 0.5 to 0.75 = %lf\n", integral(0.5, 0.75, n, xx, yy));
	printf("*** Integrating the pdf from 0.75 to 1.0 = %lf\n", integral(0.75, 1.0, n, xx, yy));
	

	fprintf(fp_w, "%d %.6lf\n", n, h);
	for (int i = 0; i < n; i++) {
		fprintf(fp_w, "%.6lf %.6lf\n", xx[i], yy[i]);
	}
	
	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
