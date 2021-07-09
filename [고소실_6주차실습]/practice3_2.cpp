#include "my_solver.h"

void practice3_2() {
	char readfile[256];
	char writefile[256];

	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;

	for (int t = 1; t <= 6; t++) {

		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		fscanf(fp_r, "%d", &DEGREE);
		NCOEF = DEGREE + 1;

		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);


		/********************************/

		for (i = 0; i < NCOEF; i++) {
			fscanf(fp_r, "%lf", &poly[i]);
		}

		rpoly_(poly, &DEGREE, zeror, zeroi, &fail);

		if (fail) {
			printf("wrong\n");
			fprintf(fp_w, "wrong\n");
		//	return;
			continue;
		}

		fprintf(fp_w, "zeror:\n");
		for (i = 0; i < DEGREE; i++)
			fprintf(fp_w, "%20.15f ", zeror[i]);
		fprintf(fp_w, "\n");
		fprintf(fp_w, "zeroi:\n");
		for (i = 0; i < DEGREE; i++)
			fprintf(fp_w, "%20.15f ", zeroi[i]);
		fprintf(fp_w, "\n\n");

		double value_x;
		for (int k = 0; k < DEGREE; k++) {
			if (zeroi[k] == 0.0) {
				value_x = zeror[k];
			
				double sum = 0.0;
				double temp_sum = 1.0;
				for (i = 0; i < NCOEF; i++) {
					temp_sum = 1.0;
					for (int j = 0; j < DEGREE - i; j++) {
						temp_sum *= value_x;
					}
					sum += temp_sum * poly[i];
				}
				fprintf(fp_w, "f(%.15lf) = %.15lf\n\n", value_x, sum);
			
			}

		}


		/********************************/


		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
}