#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <assert.h>
#define BLOCK_SIZE 16
#define N 67108864
__int64 start, freq, end;
#define CHECK_TIME_START() { QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start); }
#define CHECK_TIME_END(a) { QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f)); }
int n;
double compute_time;

int Fibonacci(int n) {
	// DO NOT MODIFY THIS FUNCTION!!!
	float sqrt_5, x_0, x_1;
	float tmp_0, tmp_1;

	sqrt_5 = sqrtf(5.0f);
	x_0 = (1.0f + sqrt_5) / 2.0f;
	x_1 = (1.0f - sqrt_5) / 2.0f;

	tmp_0 = tmp_1 = 1.0f;
	for (int i = 0; i < n; i++) {
		tmp_0 *= x_0;
		tmp_1 *= x_1;
	}
	return (int)((tmp_0 - tmp_1) / sqrt_5 + 0.5);
}
int* x, * y_c, * y_g;
void main(void) {

	int n, i;
	FILE* fp;

	// Read the input array from the input file if one already exists.
	fp = fopen("x.binary", "rb");
	if (!fp) {
		fprintf(stderr, "Error: cannot open the input file...\n");
		exit(-1);
	}
	fread(&n, sizeof(int), 1, fp);
	fprintf(stdout, "\n*** The problem size is %d.\n", n);

	x = (int*)malloc(sizeof(int) * n);
	if (!x) {
		fprintf(stderr, "Error: cannot allocate memory for the input array...\n");
		exit(-1);
	}
	fread(x, sizeof(int), n, fp);
	fclose(fp);

	y_c = (int*)malloc(sizeof(int) * n);
	y_g = (int*)malloc(sizeof(int) * n);

	//CPU
	CHECK_TIME_START();
	for (i = 0; i < n; i++) {
		y_c[i] = Fibonacci(x[i]);
	}
	CHECK_TIME_END(compute_time);



	fprintf(stdout, "\n***_CPU_ Time taken for computing %d Fibonacci numbers is %.6fms\n\n", n, compute_time);
	
	//fprintf(stdout, "\n***_GPU_ Time taken for computing %d Fibonacci numbers is %.6fms\n\n", n, device_time);

	i = (int)(n * (rand() / (RAND_MAX + 1.0f)));
	fprintf(stdout, "*** Fibonacci number of %d is (CPU :%d  , GPU :%d).\n\n", x[i], y_c[i], y_g[i]);

	
}