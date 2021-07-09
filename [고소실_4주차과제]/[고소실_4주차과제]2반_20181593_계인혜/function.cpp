#define _USE_MATH_DEFINES
#include <math.h>

double _f1(double x) {
	return pow(x, 2) - 4 * x + 4 - log(x);
}

double _fp1(double x) {
	return 2 * x - 4 - (1 / x);
}

double _f2(double x) {
	return x + 1 - 2 * sin(M_PI * x);
}

double _fp2(double x) {
	return 1 - 2 * M_PI * cos(M_PI * x);
}

double _f3(double x) {
	return pow(x, 4) - 11 * pow(x, 3) + 42.35 * pow(x, 2) - 66.55 * x + 35.1384;
}

double _fp3(double x) {
	return 4 * pow(x, 3) - 33 * pow(x, 2) + 84.7 * x - 66.55;
}

double _f4(double x) {
	return log(x) - 1;
}

double _fp4(double x) {
	return 1 / x;
}

double _fHw2(double x) {
	int l = 89, h=49, d=55;
	double b = 11.5;

	return (l * sin(b*M_PI/180)) * sin(x) * cos(x) + 
		(l * cos(b * M_PI / 180)) * pow(sin(x), 2) - 
		((h + 0.5 * d) * sin(b * M_PI / 180) - 0.5 * d * tan(b * M_PI / 180)) * cos(x)
		- ((h + 0.5 * d) * cos(b * M_PI / 180) - 0.5 * d) * sin(x);

}
double _fpHw2(double x) {
	int l = 89, h = 49, d = 55;
	double b = 11.5;

	return (l * sin(b * M_PI / 180)) * cos(2 * x) +
		(l * cos(b * M_PI / 180)) * sin(2 * x) +
		((h + 0.5 * d) * sin(b * M_PI / 180) - 0.5 * d * tan(b * M_PI / 180)) * sin(x) -
		((h + 0.5 * d) * cos(b * M_PI / 180) - 0.5 * d) * cos(x);

}


