#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.1415926
#define FSAMP 40000
#define CarrierFreq 1000
#define CarrierAmp 1.0
#define Phase PI/2.0
#define Bitrate 200
#define BitNum 6
#define LPFactor 0.95

int getRow(FILE *fp) {
	int count = 0;
	double dammyData1, dammyData2;
	while (fscanf(fp, "%lf %lf", &dammyData1, &dammyData2) != EOF) count++;
	fseek(fp, 0, SEEK_SET);
	printf("データ数%d\n", count );
	return count;
}
void errorMalloc() {
	printf("メモリ確保に失敗しました。終了します。\n");
	exit(1);
}

double getBinaryWave(int n) {
	double data[6] = {1, 0, 1, 0, 0, 1};
	return data[n];
}

double getCosWave(int n, int freq, int amp, double phase) {
	return amp * cos(2.0 * PI * freq * n / FSAMP + phase);
}


int main(int argc, char const *argv[])
{

	FILE *fp;
	char fName[128];
	printf("Input datafile\n");
	int row, i;
	double *rI, *rQ, *dtime, *out1, *out2, *data;
	double dammyData;
	gets(fName);

	fp = fopen(fName, "r");
	if (fp == NULL) {
		printf("I/O error.\n");
		exit(1);
	}
	row = getRow(fp);
	if ((rI = (double *) malloc(sizeof(double) * row) ) == NULL) 	errorMalloc();
	if ((data = (double *) malloc(sizeof(double) * row) ) == NULL) 	errorMalloc();
	if ((dtime = (double *) malloc(sizeof(double) * row) ) == NULL) 	errorMalloc();
	if ((out1 = (double *) malloc(sizeof(double) * row) ) == NULL) 	errorMalloc();
	if ((out2 = (double *) malloc(sizeof(double) * row) ) == NULL) 	errorMalloc();
	if ((rI = (double *) malloc(sizeof(double) * row) ) == NULL) 	errorMalloc();
	if ((rQ = (double *) malloc(sizeof(double) * row) ) == NULL) 	errorMalloc();

	for (i = 0; i < row; i++) fscanf(fp, "%lf %lf", &dtime[i], &data[i]);
	fclose(fp);
	for (i = 0; i < row; i++) {
		rI[i] = data[i] * getCosWave(i, CarrierFreq, CarrierAmp, 0.0);
		rQ[i] = data[i] * getCosWave(i, CarrierFreq, CarrierAmp, -PI / 2.0);
	}
	out1[0] = rI[0];
	out2[0] = rQ[0];
	for (i = 1; i < row; i++) {
		out1[i] = rI[i] + (out1[i - 1] - rI[i]) * LPFactor;
		out2[i] = rQ[i] + (out2[i - 1] - rQ[i]) * LPFactor;
		printf("%1.7lf %1.7lf %1.7lf\n", dtime[i], out1[i], out2[i]);
	}



	/* code */
	return 0;
}