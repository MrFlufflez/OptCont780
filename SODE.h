#pragma once
class SODE
{
public:
	SODE();
	~SODE();
	static const int dims = 12;
	static const int ldims = 6;
	double x[dims];
	double init[dims];
	double dx[dims];

	double ctrl0 = 0;
	double ctrl1 = 0;

	double smplx[ldims + 1][ldims];

	void func(double[]);
	double Err(void);

	double h = 0.01;
	double t0 = 0;
	double t1 = 6;

	double J;
};

