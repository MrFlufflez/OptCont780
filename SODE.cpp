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
	double u0 = 0;
	double u1 = 0;

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
	u0 = 50.0 * (xi[11] / xi[1] - xi[9]);
	u1 = -50.0 * xi[10];
#endif // !CONSTRAINED

	
	dx[0] = xi[3]; //x0
	dx[1] = xi[4]; //x1
	dx[2] = xi[5]; //x2
	dx[3] = u0 + (10791.0 * xi[2]) / 625.0; //x3
	dx[4] = u1; //x4
	dx[5] = -(u0 + (67689.0 * xi[2]) / 2500.0 + 2.0 * xi[4]*xi[5]) / xi[1]; //x5
	dx[6] = 0; //la0
	dx[7] = -(xi[11]*(u0 + (67689.0 * xi[2]) / 2500.0 + 2.0 * xi[4]*xi[5])) / (xi[1]*xi[1]); //la1
	dx[8] = (67689.0 * xi[11]) / (2500.0 * xi[1]) - 4.0 * xi[2] - (10791.0 * xi[9]) / 625.0; //la2
	dx[9] = -xi[6]; //la3
	dx[10] = (2.0 * xi[11]*xi[5]) / xi[1] - xi[7]; //la4
	dx[11] = (2.0 * xi[11]*xi[4]) / xi[1] - 4.0 * xi[5] - xi[8]; //la5

	ctrl0 = u0; 
	ctrl1 = u1;

}

double SODE::Err(void) {
	double E;

	E = 100 * pow((x[0] - 10), 2) + 100 * pow((x[1] - 17), 2) + 100 * pow((x[2] - 0), 2) + 200 * pow((x[3] - 0), 2) + 200 * pow((x[4] - 1), 2) + 200 * pow((x[5] - 0), 2);

	return E;
}