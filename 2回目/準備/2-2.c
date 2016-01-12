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


double generateFSKWave(int n, int m, int freq, int amp) {
	if(getBinaryWave(n)==0) freq = 400;
	if(getBinaryWave(n)==1) freq = 1000;

	return  getCosWave(m, freq, amp, PI *  - PI / 2.0);
}

int main(int argc, char const *argv[])
{
	int i = 0, j = 0;
	for (i = 0; i < BitNum; i++)
		for (j = i * Bitrate; j < (i + 1)*Bitrate; j++)
			printf("%1.7lf %1.7lf\n", j * 1.0 / FSAMP, generateFSKWave(i, j, CarrierFreq, CarrierAmp));
	/* code */
	return 0;
}