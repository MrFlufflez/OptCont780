#pragma once
class SODE
{
public:
	SODE();
	~SODE();
	static const int dims = 10;
	static const int ldims = 5;
	double x[dims];
	double init[dims];
	double dx[dims];

	double ctrl = 0;

	double smplx[ldims + 1][ldims];

	void func(double[]);
	double Err(void);

	double h = 0.001;
	double t0 = 0;
	double t1 = 3.14;

	double J;
};

