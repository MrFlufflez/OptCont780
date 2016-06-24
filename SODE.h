#pragma once
class SODE
{
public:
	SODE();
	~SODE();
	static const int dims = 4;
	static const int ldims = 2;
	double x[dims];
	double init[dims];
	double dx[dims];

	double ctrl = 0;

	double smplx[ldims + 1][ldims];

	void func(double[]);
	double Err(void);

	double h = 0.01;
	double t0 = 0;
	double t1 = 4;

	double J;
};

