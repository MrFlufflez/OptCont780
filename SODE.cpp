#include "SODE.h"
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

	
	if (abs(xi[3]) <= 2) {
		u = -0.5*xi[3]; 
	}
	else if (xi[3] < -2) {
		u = 1;
	}
	else {
		u = -1;
	}
	
	//x[0] = x1
	//x[1] = x2
	//x[2] = l1
	//x[3] = l2
	dx[0] = xi[1]; 
	dx[1] = u;
	dx[2] = 0;
	dx[3] = -xi[2];

	ctrl = u; 

}

double SODE::Err(void) {
	double E;

	E = pow((x[0]), 2) + pow((x[1]), 2);

	return E;
}