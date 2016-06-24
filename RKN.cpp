#include "HeaderAss8.h"
using namespace std;
void RK(SODE *Ass3) {
	int n,i, j;
	double *kp;
	double t;
	double res;
	res = 0;
	vector<vector<double>> kv(4,vector<double>(Ass3->dims));
	
	vector<double> xsumv(Ass3->dims);
	vector<double> kavev(Ass3->dims);
	vector<double> dxsavev(Ass3->dims);

	//File
	/*FILE *cfptr;
	const char *fle = "Ass3b.dat";

	if ((fopen_s(&cfptr, fle, "w")) == NULL) {
		cout << "Error creating file->" << endl;
	}*/
	//end file
	
	t = Ass3->t0;
	double* k0 = &kv[0][0];
	double* k1 = &kv[1][0];
	double* k2 = &kv[2][0];
	double* k3 = &kv[3][0];
	
	double* kave = &kavev[0];
	double* xsum = &xsumv[0];
	double* dxsave = &dxsavev[0];

	for (i = 0; i <= Ass3->dims - 1; i++)	Ass3->dx[i] = 0;
	for (i = 0; i <= Ass3->dims - 1; i++)	xsum[i] = Ass3->init[i];

	res = res + Ass3->h * Ass3->x[0] * Ass3->x[0] + Ass3->h * Ass3->x[1] * Ass3->x[1];

	n = int((Ass3->t1 - Ass3->t0) / Ass3->h);
	for (i = 0; i <= Ass3->dims-1; i++)	Ass3->x[i] = Ass3->init[i];
	cout << endl;

	for (i = 0; i <= Ass3->dims - 1; i++) {
		Ass3->dx[i] = 0;
	}
	//cout << t << "\tx1 = " << Ass3->x[0] << "\tl1 = " << Ass3->x[1] << endl;
	//fprintf(cfptr, "%g, %g, %g, %g, %g, %g \n", t, Ass3->x[0], Ass3->x[1], Ass3->x[2], Ass3->x[3], Ass3->x[4]);

	for (i = 1; i <= n; i++) {
	//	cout << "t = " << t << "\nx0 = " << Ass3->x[0] << "\tx1 = " << Ass3->x[1] << "\tx2 = " << Ass3->x[2] 
	//			<< "\tx3 = " << Ass3->x[3] << "\tx4 = " << Ass3->x[4] << "\nl0 = " << Ass3->x[5] << "\tl1 = " << Ass3->x[6] 
	//		<< "\tl2 = " << Ass3->x[7] << "\tl3 = " << Ass3->x[8] << "\tl4 = " << Ass3->x[9] << endl;

		//k0
		Ass3->func(Ass3->x);
		for (j = 0; j <= Ass3->dims - 1; j++)	k0[j] = Ass3->dx[j];

		for (j = 0; j <= Ass3->dims - 1; j++)  dxsave[j] = Ass3->dx[j]; //save new dx value

		//k1
		for (j = 0; j <= Ass3->dims - 1; j++) {
			xsum[j] = Ass3->x[j] + 0.5 * Ass3->h*k0[j];
		}
		Ass3->func(xsum);
		for (j = 0; j <= Ass3->dims - 1; j++)	k1[j] = Ass3->dx[j];

		//k2
		for (j = 0; j <= Ass3->dims - 1; j++) {
			xsum[j] = Ass3->x[j] + 0.5*Ass3->h*k1[j];
		}
		Ass3->func(xsum);
		for (j = 0; j <= Ass3->dims - 1; j++)	k2[j] = Ass3->dx[j];

		//k3
		for (j = 0; j <= Ass3->dims - 1; j++) {
			xsum[j] = Ass3->x[j] + Ass3->h*k2[j];
		}
		Ass3->func(xsum);
		for (j = 0; j <= Ass3->dims - 1; j++)	k3[j] = Ass3->dx[j];
		
		//kave
		for (j = 0; j <= Ass3->dims - 1; j++) {
			kave[j] = (k0[j] + 2.0 * k1[j] + 2.0 * k2[j] + k3[j]) / 6.0;
		}

		
		
		for (j = 0; j <= Ass3->dims - 1; j++) {
			Ass3->x[j] = Ass3->x[j] + Ass3->h*kave[j];
		}
		t = t + Ass3->h;
		res = res + Ass3->h * Ass3->x[0] * Ass3->x[0] + Ass3->h * Ass3->x[1] * Ass3->x[1];
		//fprintf(cfptr, "%g, %g, %g, %g, %g, %g \n", t, Ass3->x[0], Ass3->x[1], Ass3->x[2], Ass3->x[3], Ass3->x[4]);
		
	}
	//fclose(cfptr);
	/*cout << "t = " << t << "\tx1 = " << Ass3->x[0] << "\tx2 = " << Ass3->x[1] << "\tl1 = " << Ass3->x[2] << "\tl2 = " << Ass3->x[3] << endl;
	cout << "J = " << res << endl;*/
	Ass3->J = res;
	cout << endl;
	 
}