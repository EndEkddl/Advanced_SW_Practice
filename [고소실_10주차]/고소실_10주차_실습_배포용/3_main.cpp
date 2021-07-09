#include <stdio.h>
#include <random>
#include <time.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
/*
	���� �ڷḦ �����ϸ�, ����� ���ڳ����� ���� �� �ε� �Ҽ��� ���꿡�� ��Ȯ���� ��������.

	�̸� �����ϱ� ���� ������ �������� �ٲپ� ����Ͽ���. �̶�, ������Ģ�� ���� �츮�� ���Ϸ��� ���� ���� ���� ����� ������ �ȴ�.

	���� x�� ���� ������� �������� �ٲپ� ��� �� ��� ���� ������ �����Ͽ���.
*/

#define N 50
double Taylor_series(double x, int n);
float Taylor_series_ex(double x, int n);
__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

void main(void)
{
	CHECK_TIME_START;
	printf("*** f<-8.3> = %.6e \n", Taylor_series(-8.3, N));
	CHECK_TIME_END(compute_time);
	printf("Taylor_series : %f ms\n", compute_time);

	CHECK_TIME_START;
	printf("*** f<-8.3> = %.6e \n", Taylor_series_ex(-8.3, N));
	CHECK_TIME_END(compute_time);
	printf("Taylor_series_ex : %f ms\n", compute_time);
	printf("*** f<-8.3> = %.6e \n", pow(2.71828182846, -8.3));
}




double Taylor_series(double x, int n)
{
	double ans = 1;

	if (x < 0) x *= -1;
	for (int i = n; i >= 1; i--) {
		ans = ans * (x / (double)i) + 1;
	}

	return ans;
}


float Taylor_series_ex(double x, int n)
{
	float ans = 1.0;
	bool check = false;

	if (x < 0) {
		x *= -1;
		check = true;
	}

	for (int i = n; i >= 1; i--) {
		ans = ans * (x / (float)i) + 1;
	}

	if (check) return 1 / ans;
	return ans;


}
