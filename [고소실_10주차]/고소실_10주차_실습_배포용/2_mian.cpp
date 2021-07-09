#include <stdio.h>
#include <random>
#include <time.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#define DEGREE 10

#define N_X 1048576

/*
	컴퓨터에서 연산은 일반적으로 곱셈과 나눗셈이 덧셈과 뺄셈보다 훨씬 시간이 많이 걸린다.

	따라서 다항식 계산 시 곱셈의 횟수를 줄이는 것이 효율적이다.

	Eval_poly_naive 함수에서는 항을 하나씩 계산하여 더하는 것으로 곱셈의 횟수가 많기 때문에 시간적인 측면에서 비효율적이다.

	반면, Eval_poly_Horner 함수는 곱셈의 횟수를 줄여 식의 계산을 하기 때문에 시간적인 측면에서 유리하다.
*/

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

void init_polynomial(void);
void Eval_Poly_Naive(double y[], double x[], int n_x, double a[], int deg);
void Eval_Poly_Horner(double y[], double x[], int n_x, double a[], int deg);
void Check_Difference(double y_n[], double y_h[], int n_x);

double* a, * x, * y_n, * y_h;

void main(void)
{
	init_polynomial();

	CHECK_TIME_START;
	Eval_Poly_Naive(y_n, x, N_X, a, DEGREE);
	CHECK_TIME_END(compute_time);
	printf("***Polynomial Naive  compute time : %f ms\n", compute_time);

	CHECK_TIME_START;
	Eval_Poly_Horner(y_h, x, N_X, a, DEGREE);
	CHECK_TIME_END(compute_time);
	printf("***Polynomial Horner compute time : %f ms\n", compute_time);

	Check_Difference(y_n, y_h, N_X);
}
void init_polynomial(void) {
	a = (double*)malloc(sizeof(double) * (DEGREE + 1));
	x = (double*)malloc(sizeof(double) * N_X);
	y_n = (double*)malloc(sizeof(double) * N_X);
	y_h = (double*)malloc(sizeof(double) * N_X);

	srand((unsigned)time(NULL));
	double* ptr = a;
	for (int i = 0; i < DEGREE; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
	ptr = x;
	for (int i = 0; i < N_X; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
}

void Eval_Poly_Naive(double y[], double x[], int n_x, double a[], int deg)
{

	for (int i = 0; i < n_x; i++) {
		y[i] = 0;
		for (int j = 0; j <= deg; j++) {
			y[i] += a[j] * pow(x[i], j);
		}
	}
}


void Eval_Poly_Horner(double y[], double x[], int n_x, double a[], int deg)
{
	for (int i = 0; i < n_x; i++) {
		y[i] = a[deg];
		for (int j = deg - 1; j >= 0; j--) {
			y[i] *= x[i];
			y[i] += a[j];
		}
	}
}


void Check_Difference(double y_n[], double y_h[], int n_x) {
	int i;

	for (i = 0; i < n_x; i++) {
		if ((float)y_n[i] != (float)y_h[i]) {
			printf("Value y_n[%d] (%.15lf) is not equal with y_h[%d] (%.15lf)\n\n", i, y_n[i], i, y_h[i]);
			return;
		}
	}

	printf("All values are equal\n\n");
}
