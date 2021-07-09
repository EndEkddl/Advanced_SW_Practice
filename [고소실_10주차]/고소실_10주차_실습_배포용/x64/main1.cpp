#include <stdio.h>
#include <string.h>
#include <random>
#include <time.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

/*
	조교님께서 제공해주신 1번 함수는 행렬의 곱셈시 비효율접근을 하는 것이었다.
	이를 전치행렬을 이용하여 좀 더 효율적인 접근 방식을 사용하도록 한 것이 2번 함수이다.

	즉, 1번 : *ooooooo*oooooo은 이런식으로 '*' 표시가 되어 있는 부분에 차례로 접근한다. 
	그러나 이는 인접한 메모리가 아니기 때문에 접근 시 시간이 훨씬 오래걸린다.
	반면 2번 : **oooooooooooo은 이런식으로 인접한 메모리에 차례로 접근하기 때문에 시간 절약의 효과를 얻을 수 있다.

	3번 같은 경우는 강의 시간에 배운 loop unrolling 기법을 사용하여 시간을 감소시키는 것인데, 8개로 풀었을 때 가장 효과적이었다.

	4번은 loop를 32개로 풀어보았지만 시간 절약 효과가 3번보다 덜했다.
*/


__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;


#define MATDIM 1024
double* pMatA, * pMatB, * pMatC;
void MultiplySquareMatrices_1(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize);
void MultiplySquareMatrices_2(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize);
void MultiplySquareMatrices_3(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize);
void MultiplySquareMatrices_4(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize);

void init_MatMat(void);

void main(void)
{
	init_MatMat();

	CHECK_TIME_START;
	MultiplySquareMatrices_1(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_1 : %f ms\n", compute_time);

	CHECK_TIME_START;
	MultiplySquareMatrices_2(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_2 = %f ms\n", compute_time);

	CHECK_TIME_START;
	MultiplySquareMatrices_3(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_3 = %f ms\n", compute_time);

	CHECK_TIME_START;
	MultiplySquareMatrices_4(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_4 = %f ms\n", compute_time);
}

void MultiplySquareMatrices_1(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize)
{
	int i, j, k;
	for (i = 0; i < MatSize; i++) {
		for (j = 0; j < MatSize; j++) {
			pDestMatrix[i * MatSize + j] = 0;
			for (k = 0; k < MatSize; k++)
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k] * pRightMatrix[k * MatSize + j];
		}
	}

}

void MultiplySquareMatrices_2(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize)
{
	int i, j, k;
	double* temp = (double*)malloc(sizeof(double) * MATDIM * MATDIM);
	memset(temp, 0x00, sizeof(temp));

	for (i = 0; i < MatSize; i++) {
		for (j = 0; j < MATDIM; j++) {
			temp[i * MATDIM + j] = pRightMatrix[i + j * MATDIM];
		}
	}

	for (i = 0; i < MatSize; i++) {
		for (j = 0; j < MatSize; j++) {
			pDestMatrix[i * MatSize + j] = 0;
			for (k = 0; k < MatSize; k++) {
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MATDIM + k] + temp[j * MATDIM + k];
			}
		}
	}

	free(temp);
}

void MultiplySquareMatrices_3(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize)
{
	int i, j, k;
	double* temp = (double*)malloc(sizeof(double) * MATDIM * MATDIM);
	memset(temp, 0x00, sizeof(temp));

	for (i = 0; i < MatSize; i++) {
		for (j = 0; j < MATDIM; j++) {
			temp[i * MATDIM + j] = pRightMatrix[i + j * MATDIM];
		}
	}

	for (i = 0; i < MatSize; i++) {
		for (j = 0; j < MatSize; j++) {
			pDestMatrix[i * MatSize + j] = 0;
			for (k = 0; k < MatSize / 8; k++) {
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MATDIM + k * 8] + temp[j * MATDIM + k * 8];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MATDIM + k * 8 + 1] + temp[j * MATDIM + k * 8 + 1];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MATDIM + k * 8 + 2] + temp[j * MATDIM + k * 8 + 2];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MATDIM + k * 8 + 3] + temp[j * MATDIM + k * 8 + 3];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MATDIM + k * 8 + 4] + temp[j * MATDIM + k * 8 + 4];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MATDIM + k * 8 + 5] + temp[j * MATDIM + k * 8 + 5];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MATDIM + k * 8 + 6] + temp[j * MATDIM + k * 8 + 6];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MATDIM + k * 8 + 7] + temp[j * MATDIM + k * 8 + 7];
			}
			for (k = 0; k < MatSize % 8; k++) {
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * (MatSize / 8) * 8 + k] * temp[j * (MatSize / 8) * 8 + k];
			}

		}
	}

	free(temp);
}

void MultiplySquareMatrices_4(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize)
{
	int i, j, k;
	double* temp = (double*)malloc(sizeof(double) * MATDIM * MATDIM);
	memset(temp, 0x00, sizeof(temp));

	for (i = 0; i < MatSize; i++) {
		for (j = 0; j < MATDIM; j++) {
			temp[i * MATDIM + j] = pRightMatrix[i + j * MATDIM];
		}
	}

	for (i = 0; i < MatSize; i++) {
		for (j = 0; j < MatSize; j++) {
			pDestMatrix[i * MatSize + j] = 0.0;
			for (k = 0; k < MatSize / 32; k++) {
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32] * temp[j * MatSize + k * 32];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 1] * temp[j * MatSize + k * 32 + 1];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 2] * temp[j * MatSize + k * 32 + 2];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 3] * temp[j * MatSize + k * 32 + 3];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 4] * temp[j * MatSize + k * 32 + 4];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 5] * temp[j * MatSize + k * 32 + 5];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 6] * temp[j * MatSize + k * 32 + 6];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 7] * temp[j * MatSize + k * 32 + 7];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 8] * temp[j * MatSize + k * 32 + 8];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 9] * temp[j * MatSize + k * 32 + 9];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 10] * temp[j * MatSize + k * 32 + 10];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 11] * temp[j * MatSize + k * 32 + 11];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 12] * temp[j * MatSize + k * 32 + 12];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 13] * temp[j * MatSize + k * 32 + 13];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 14] * temp[j * MatSize + k * 32 + 14];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 15] * temp[j * MatSize + k * 32 + 15];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 16] * temp[j * MatSize + k * 32 + 16];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 17] * temp[j * MatSize + k * 32 + 17];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 18] * temp[j * MatSize + k * 32 + 18];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 19] * temp[j * MatSize + k * 32 + 19];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 20] * temp[j * MatSize + k * 32 + 20];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 21] * temp[j * MatSize + k * 32 + 21];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 22] * temp[j * MatSize + k * 32 + 22];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 23] * temp[j * MatSize + k * 32 + 23];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 24] * temp[j * MatSize + k * 32 + 24];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 25] * temp[j * MatSize + k * 32 + 25];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 26] * temp[j * MatSize + k * 32 + 26];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 27] * temp[j * MatSize + k * 32 + 27];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 28] * temp[j * MatSize + k * 32 + 28];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 29] * temp[j * MatSize + k * 32 + 29];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 30] * temp[j * MatSize + k * 32 + 30];
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * MatSize + k * 32 + 31] * temp[j * MatSize + k * 32 + 31];

			}
			for (k = 0; k < MatSize % 32; k++)
				pDestMatrix[i * MatSize + j] += pLeftMatrix[i * (MatSize / 32) * 32 + k] * temp[j * (MatSize / 32) * 32 + k];
		}
	}
	free(temp);
}

void init_MatMat(void)
{
	double* ptr;
	pMatA = (double*)malloc(sizeof(double) * MATDIM * MATDIM);
	pMatB = (double*)malloc(sizeof(double) * MATDIM * MATDIM);
	pMatC = (double*)malloc(sizeof(double) * MATDIM * MATDIM);
	srand((unsigned)time(NULL));
	ptr = pMatA;
	for (int i = 0; i < MATDIM * MATDIM; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
	ptr = pMatB;
	for (int i = 0; i < MATDIM * MATDIM; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
}
