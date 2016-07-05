#pragma once
#define CONSTRAINED
#define CONTINUOUS
#define pi 3.14159265359
class SODE
{
public:
	SODE();
	~SODE();
#ifndef CONSTRAINED
	static const int dims = 12;
	static const int ldims = 6;
#endif
#ifdef CONSTRAINED
	static const int dims = 14;
	static const int ldims = 7;
#endif
	double x[dims];
	double init[dims];
	double dx[dims];

	double ctrl0 = 0;
	double ctrl1 = 0;

	double smplx[ldims + 1][ldims];

	void func(double[]);
	double Err(void);

	double h = 0.001;
	double t0 = 0;
	double t1 = 6;

	double J;
};

