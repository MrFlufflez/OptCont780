#include "Opt.h"
#include <cmath>


SODE::SODE() {
	int i, j;

	for (i = 0; i <= dims - 1; i++) {
		x[i] = 0;
		init[i] = 0;
		dx[i] = 0;
	}
	for (i = 0; i <= ldims; i++) {
		for (j = 0; j <= ldims - 1; j++) smplx[3][2] = 0;
	}

}

SODE::~SODE()
{
}

void SODE::func(double xi[]) { //
	double u = 0;

#ifdef CONSTRAINED
	if (abs(xi[9]) <= 2) {
		u = -0.5*xi[9]; 
	}
	else if (xi[9] < -2) {
		u = 1;
	}
	else {
		u = -1;
	}
#endif // CONSTRAINED
#ifndef CONSTRAINED
	u = -0.5*xi[9];
#endif // !CONSTRAINED

	
	dx[0] = xi[1];
	dx[1] = ((2.0 * cos(xi[0])*sin(xi[0])*xi[1] * xi[1]) / 35.0 + (49.0 * sin(xi[0])) / 25.0 - (3.0 * xi[3] * cos(xi[0])) / 7.0 + (2.0 * xi[4] * cos(xi[0])) / 7.0) / ((2.0 * cos(xi[0])*cos(xi[0])) / 35.0 - 217.0 / 1000.0);
	dx[2] = xi[3];
	dx[3] = -((sin(xi[0])*xi[1] * xi[1]) / 5.0 - (3 * xi[3]) / 2.0 + xi[4] + (56.0 * cos(xi[0])*sin(xi[0])) / 31.0) / ((40.0 * cos(xi[0])*cos(xi[0])) / 217.0 - 7.0 / 10.0);
	dx[4] = u;
	dx[5] = (xi[8] * ((xi[1] * xi[1] * cos(xi[0])) / 5.0 + (56.0 * cos(xi[0])*cos(xi[0])) / 31.0 - (56.0 * sin(xi[0])*sin(xi[0])) / 31.0)) / ((40.0 * cos(xi[0])*cos(xi[0])) / 217.0 - 7.0 / 10.0) - (xi[6] * ((49.0 * cos(xi[0])) / 25.0 + (2.0 * xi[1] * xi[1] * cos(xi[0])*cos(xi[0])) / 35.0 - (2.0 * xi[1] * xi[1] * sin(xi[0])*sin(xi[0])) / 35.0 + (3.0 * xi[3] * sin(xi[0])) / 7.0 - (2.0 * xi[4] * sin(xi[0])) / 7.0)) / ((2.0 * cos(xi[0])*cos(xi[0])) / 35.0 - 217.0 / 1000.0) + (80.0 * xi[8] * cos(xi[0])*sin(xi[0])*((sin(xi[0])*xi[1] * xi[1]) / 5.0 - (3.0 * xi[3]) / 2.0 + xi[4] + (56.0 * cos(xi[0])*sin(xi[0])) / 31.0)) / (217.0 * ((40.0 * cos(xi[0])*cos(xi[0])) / 217.0 - 7.0 / 10.0)*((40.0 * cos(xi[0])*cos(xi[0])) / 217.0 - 7.0 / 10.0)) - (4.0 * xi[6] * cos(xi[0])*sin(xi[0])*((2.0 * cos(xi[0])*sin(xi[0])*xi[1] * xi[1]) / 35.0 + (49.0 * sin(xi[0])) / 25.0 - (3.0 * xi[3] * cos(xi[0])) / 7.0 + (2.0 * xi[4] * cos(xi[0])) / 7.0)) / (35.0 * ((2.0 * cos(xi[0]) * cos(xi[0])) / 35.0 - 217.0 / 1000.0)*((2.0 * cos(xi[0]) *cos(xi[0])) / 35.0 - 217.0 / 1000.0));
	dx[6] = (2.0 * xi[8] * xi[1] * sin(xi[0])) / (5.0 * ((40.0 * cos(xi[0])*cos(xi[0])) / 217.0 - 7.0 / 10.0)) - xi[5] - (4.0 * xi[6] * xi[1] * cos(xi[0])*sin(xi[0])) / (35.0 * ((2.0 * cos(xi[0])*cos(xi[0])) / 35.0 - 217.0 / 1000.0));
	dx[7] = 0.0;
	dx[8] = (3.0 * xi[6] * cos(xi[0])) / (7.0 * ((2.0 * cos(xi[0])*cos(xi[0])) / 35.0 - 217.0 / 1000.0)) - (3.0 * xi[8]) / (2.0 * ((40.0 * cos(xi[0])*cos(xi[0])) / 217.0 - 7.0 / 10.0)) - xi[7];
	dx[9] = xi[8] / ((40.0 * cos(xi[0])*cos(xi[0])) / 217.0 - 7.0 / 10.0) - (2.0 * xi[6] * cos(xi[0])) / (7.0 * ((2.0 * cos(xi[0])*cos(xi[0])) / 35.0 - 217.0 / 1000.0));

	ctrl = u; 

}

double SODE::Err(void) {
	double E;

	E = 100 * pow((x[0] - 3.14), 2) + 10 * pow((x[1] - 0), 2) + 10 * pow((x[2] - 0), 2) + 10 * pow((x[3] - 0), 2) + 1 * pow((x[4] - 0), 2);

	return E;
}