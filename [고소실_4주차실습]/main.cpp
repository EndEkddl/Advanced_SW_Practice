#include "my_solver.h"

extern void program1_1(FILE* fp); // Newton-Raphson Method
extern void program1_2(FILE* fp); // Secant Method

extern void sp_program1_1(FILE* fp); // Newton-Raphson Method
extern void sp_program1_2(FILE* fp); // Secant Method

double (*_f)(double);
double (*_fp)(double);

float (*_sp_f)(float);
float (*_sp_fp)(float);

int main() {
	FILE* fp;
	fp = fopen("result.txt", "w");

	_f = _f1;
	_fp = _fp1;

	program1_1(fp);
	program1_2(fp);
	
	_f = _f2;
	_fp = _fp2;

	program1_1(fp);
	program1_2(fp);

	_f = _f3;
	_fp = _fp3;

	for (int i = 0; i < 4; i++) {
		program1_1(fp);
	}

	_f = _f4;
	_fp = _fp4;

	program1_1(fp);
	
	_sp_f = _f4_1;
	_sp_fp = _fp4_1;

	sp_program1_1(fp);


	fclose(fp);
}
