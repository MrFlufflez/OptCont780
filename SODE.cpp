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
	double g[4] = { 0,0,0,0 };
	int H[4] = { 0,0,0,0 };
	int i;

	g[0] = xi[3] + 2.5;
	g[1] = -xi[3] + 2.5;
	g[2] = xi[4] + 1;
	g[3] = -xi[4] + 1;

	for (i = 0; i < 4; i++) {
		if (g[i] >= 0) H[i] = 0;
		else H[i] = 1;
	}
#ifndef CONTINUOUS
	if (abs(50.0*(xi[12] / xi[1] - xi[10])) <= 2.833744) {
		u0 = (50.0*(xi[12] / xi[1] - xi[10]));
	}
	else if ((50.0*(xi[12] / xi[1] - xi[10])) < -2.833744) {
		u0 = -2.833744;
	}
	else {
		u0 = 2.833744;
	}

	

	if (((xi[11]) >= -0.71265/50.0) && (xi[11] <= 0.80865/50.0)) {
		u1 = -50.0 * xi[11];
	}
	else if ((xi[11]) > 0.80865/50.0) {
		u1 = -0.80865;
	}
	else {
		u1 = 0.71265;
	}
#endif
#ifdef CONTINUOUS
	u0 = 2.833744*(2.0 / pi)*atan(2.0 * 20.0 * (xi[12] / xi[1] - xi[10]));
	u1 = -(0.76065)*(2.0 / pi)*atan(2.0 * 70.0 * xi[11]) - 0.048;
#endif

	
	dx[0] = xi[3]; //x0
	dx[1] = xi[4]; //x1
	dx[2] = xi[5]; //x2
	dx[3] = u0 + (10791.0 * xi[2]) / 625.0; //x3
	dx[4] = u1; //x4
	dx[5] = -(u0 + (67689.0 * xi[2]) / 2500.0 + 2.0 * xi[4] * xi[5]) / xi[1]; //x5
	dx[6] = g[0] * g[0] * H[0] + g[1] * g[1] * H[1] + g[2] * g[2] * H[2] + g[3] * g[3] * H[3]; //x6

	dx[7] = 0; //la0
	dx[8] = -(xi[12] * (u0 + (67689.0 * xi[2]) / 2500.0 + 2.0 * xi[4] * xi[5])) / (xi[1] * xi[1]); //la1
	dx[9] = (67689.0 * xi[12]) / (2500.0 * xi[1]) - 4.0 * xi[2] - (10791.0 * xi[10]) / 625.0; //la2
	dx[10] = -xi[7] - xi[13] * (H[0] * (2.0 * xi[3] + 5.0) + H[1] * (2.0 * xi[3] - 5.0));//la3
	dx[11] = (2.0 * xi[12] * xi[5]) / xi[1] - xi[8] - xi[13] * (H[2] * (2.0 * xi[4] + 2.0) + H[3] * (2.0 * xi[4] - 2.0)); //la4
	dx[12] = (2.0 * xi[12] * xi[4]) / xi[1] - 4.0 * xi[5] - xi[9]; //la5
	dx[13] = 0; //la6
	
#endif // CONSTRAINED
#ifndef CONSTRAINED
	u0 = 50.0 * (xi[11] / xi[1] - xi[9]);
	u1 = -50.0 * xi[10];
		
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
#endif // !CONSTRAINED

	ctrl0 = u0; 
	ctrl1 = u1;

}

double SODE::Err(void) {
	double E;
#ifndef CONSTRAINED
	E = 100 * pow((x[0] - 10), 2) + 100 * pow((x[1] - 17), 2) + 100 * pow((x[2] - 0), 2) + 200 * pow((x[3] - 0), 2) + 200 * pow((x[4] - 1), 2) + 200 * pow((x[5] - 0), 2);
#endif
#ifdef CONSTRAINED
	E = 100.0 * pow((x[0] - 10), 2) + 100.0 * pow((x[1] - 17), 2) + 100.0 * pow((x[2] - 0), 2) + 200.0 * pow((x[3] - 0), 2) + 200.0 * pow((x[4] - 1), 2) + 200.0 * pow((x[5] - 0), 2) + 200000.0 * pow((x[6] - 0), 2);
#endif

	return E;
}