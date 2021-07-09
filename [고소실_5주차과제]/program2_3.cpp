#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>


double secantMethod(double* fx, double* fy, int N, double h, double u) {
	double x0 = 0.0, x1 = 1.0;
	double a0 = 0.0, b0 = 1.0;
	double tmp;
	int n, s, a;
	double t1, t2;

	x1 = (a0 + b0) / 2.0;

	for (n = 0; ; n++) {
		for (a = 0; a < N; a++) {
			if (a * h <= a0 && a0 < (a + 1) * h) break;
		}
		for (s = 0; s < N; s++) {
			if (s * h <= x1 && x1 < (s + 1) * h) break;
		}

		if (fabs(fy[s] - u) < DELTA || n > Nmax || fabs(x1 - x0) < EPSILON) break;

		t1 = fy[a] - u;
		t2 = fy[s] - u;

		if (t1 * t2 < 0.0) b0 = x1;
		else a0 = x1;

		tmp = (a0 + b0) / 2.0;
		x0 = x1;
		x1 = tmp;
	}

	for (n = 0; ; n++){
		for (a = 0; a < N; a++) {
			if (a * h <= x0 && x0 < (a + 1) * h) break;
		}
		for (s = 0; s < N; s++) {
			if (s * h <= x1 && x1 < (s + 1) * h) break;
		}

		if (fabs(fy[s] - u) < DELTA || n > Nmax || fabs(x1 - x0) < EPSILON) break;
		
		tmp = x1 - fy[s] * ((s - a) / (fy[s] - fy[a]));
		x0 = x1;
		x1 = tmp;
	}

	return x1;
}

// HOMEWORK
void program2_3()
{
	FILE* fp_r, * fp_w;
	int n;
	int cnt[401];

	fp_w = fopen("histogram.txt", "w");
	fp_r = fopen("random_event_table_2_2_a.txt", "r");

	fscanf(fp_r, "%d", &n);
	double* x = (double*)malloc(sizeof(double) * n);
	memset(cnt, 0, sizeof(cnt));

	for (int i = 0; i < n; i++) {
		fscanf(fp_r, "%lf", &x[i]);
		cnt[(int)(x[i] / 0.0025)]++;
	}


	fprintf(fp_w, "=================Histogram of 2_2_a=================\n\n");
	for (int i = 0; i < 400; i++) {
		fprintf(fp_w, "%.4lf ~ %.4lf : %4d\t", i * 0.0025, (i + 1) * 0.0025, cnt[i]);
		for (int j = 0; j < cnt[i]; j++) {
			fprintf(fp_w, "*");
		}
		fprintf(fp_w, "\n");
	}
	free(x);
	if (fp_r != NULL)fclose(fp_r);

	fprintf(fp_w, "\n\n");
	fp_r = fopen("random_event_table_2_2_b.txt", "r");
	fscanf(fp_r, "%d", &n);
	x = (double*)malloc(sizeof(double) * n);
	memset(cnt, 0, sizeof(cnt));

	for (int i = 0; i < n; i++) {
		fscanf(fp_r, "%lf", &x[i]);
		cnt[(int)(x[i] / 0.0025)]++;
	}
	fprintf(fp_w, "=================Histogram of 2_2_b=================\n\n");
	for (int i = 0; i < 400; i++) {
		fprintf(fp_w, "%.4lf ~ %.4lf : %4d\t", i * 0.0025, (i + 1) * 0.0025, cnt[i]);
		for (int j = 0; j < cnt[i]; j++) {
			fprintf(fp_w, "*");
		}
		fprintf(fp_w, "\n");
	}

	free(x);
	if (fp_r != NULL)fclose(fp_r);
	if (fp_w != NULL)fclose(fp_w);
}

// HOMEWORK
void program2_2_a()
{
	__int64 start, freq, end;
	float resultTime = 0;

	// something to do...
	FILE* fp_r, * fp_w;
	int n, userN;
	double u, h;
	double x = 0, tmp = 0;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table_2_2_a.txt", "w");

	if (fp_r == NULL) {
		printf("Input File Open Error!\n");
		exit(0);
	}
	scanf("%d", &userN);

	fscanf(fp_r, "%d %lf", &n, &h);
	
	double* ax = (double*)malloc(sizeof(double) * n);
	double* ay = (double*)malloc(sizeof(double) * n);
	double* fx = (double*)malloc(sizeof(double) * n);
	double* fy = (double*)malloc(sizeof(double) * n);

	for (int i = 0; i < n; i++) {
		fscanf(fp_r, "%lf %lf", &ax[i], &ay[i]);
		fx[i] = ax[i];
		fy[i] = trapezoidal(ax,ay,n,h,0,fx[i]);
	}
	CHECK_TIME_START;

	fprintf(fp_w, "%d\n", userN);
	srand((unsigned int)time(NULL));
	for (int i = userN; i > 0; i--) {
		u = (double)rand() / RAND_MAX;
		x = bisectionMethod(fx, fy, n, h, u);
		fprintf(fp_w, "%.15lf\n", x);
	}

	CHECK_TIME_END(resultTime);

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_2_b()
{
	__int64 start, freq, end;
	float resultTime = 0;

	FILE* fp_r, *fp_w;
	int n, userN;
	double u, h;
	double x = 0, tmp = 0;
	
	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table_2_2_b.txt", "w");

	if (fp_r == NULL) {
		printf("Input File Open Error!\n");
		exit(0);
	}
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
	CHECK_TIME_START;

	fprintf(fp_w, "%d\n", userN);
	srand((unsigned int)time(NULL));

	for (int i = userN; i > 0; i--) {
		u = (double)rand() / RAND_MAX;
		x = secantMethod(fx, fy, n, h, u);
		double y = (rand() / 100) / (double)100000;
		x -= y;
		fprintf(fp_w, "%.15lf\n", x);
	}
	CHECK_TIME_END(resultTime);

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);


	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);
}