#include <stdio.h>
#include <math.h>
#define PI 3.1415926
#define FSAMP 40000
#define CarrierFreq 1000
#define CarrierAmp 1.0
#define Phase PI/2.0
#define Bitrate 200
#define BitNum 6

double getBinaryWave(int n) {
	double data[6] = {1, 0, 1, 0, 0, 1};
	return data[n];
}

double getCosWave(int n, int freq, int amp, double phase) {
	return amp * cos(2.0 * PI * freq * n / FSAMP + phase);
}


double generateQPSKWave(int n, int m, int freq, int amp) {
	double b1, b2;
	if (getBinaryWave(n) == 0.0) {
		b1 = -1.0;
	} else if (getBinaryWave(n) == 1.0) {
		b1 = 1.0;
	}

	if (getBinaryWave(n + 1) == 0.0) {
		b2 = -1.0;
	} else if (getBinaryWave(n + 1) == 1.0) {
		b2 = 1.0;
	}
	return  b1 * getCosWave(m, freq, amp, 0.0) + b2 * getCosWave(m, freq, amp,  - PI / 2.0);
}

int main(int argc, char const *argv[])
{
	int i = 0, j = 0;
	for (i = 0; i < BitNum; i+=2)
		for (j = (i/2)* Bitrate; j < ((i/2) + 1)*Bitrate; j++)
			printf("%1.7lf %1.7lf\n", j * 1.0 / FSAMP, generateQPSKWave(i, j, CarrierFreq, CarrierAmp));
	/* code */
	return 0;
}