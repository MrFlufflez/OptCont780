#include "Opt.h"
using namespace std;

void MinFunc(SODE *Ass3) {
	int i, j, highest, ilowest, sechigh, dimsp, nfunc, k;
	int max_iter = 100000;
	double tolfunc, tolr, sum, swap, ytemp, err;
	double insig = 1.0e-10;
	
	vector<double> smplxsumv(Ass3->ldims + 1);
	double* smplxsum = &smplxsumv[0];

	vector<double> yv(Ass3->ldims+1);
	double* y = &yv[0];
	/*double* smplxsum;
	smplxsum = (double*)malloc(Ass3->ldims+1);*/

	/*double* y;
	y = (double*)malloc(Ass3->ldims);*/

	for (i = 0; i <= Ass3->ldims; i++) {
		for (j = 0; j <= Ass3->ldims - 1;j++) {
			Ass3->init[j + Ass3->ldims] = Ass3->smplx[i][j];
		}
		y[i] = evaluate(Ass3);
	}

	tolfunc = 1e-16;
	sum = 0.0;
	dimsp = Ass3->ldims + 1;
	nfunc = 0;

	//sum of smplx
	sum = 0.0;
	for (j = 0; j <= Ass3->ldims-1; j++) {
		for (sum = 0.0, i = 0; i <= Ass3->ldims; i++) {
			sum += Ass3->smplx[i][j];
		}
		smplxsum[j] = sum;
	}

	while (1) {
		ilowest = 0;
		highest = y[0] > y[1] ? (sechigh = 1, 0) : (sechigh = 0, 1);
		for (i = 0;i <= Ass3->ldims;i++) {
			if (y[i] <= y[ilowest]) ilowest = i;
			if (y[i] > y[highest]) {
				sechigh = highest;
				highest = i;
			}
			else if (y[i] > y[sechigh] && i != highest) sechigh = i;
		}

		tolr = 2.0*fabs(y[highest] - y[ilowest]) / (fabs(y[highest]) + fabs(y[ilowest]) + insig);

		if (tolr < tolfunc) {
			//Swap the lowest obtained with the first value and exit
			swap = y[0];
			y[0] = y[ilowest];
			y[ilowest] = swap;

			for (i = 0; i <= Ass3->ldims-1; i++) {
				swap = Ass3->smplx[0][i];
				Ass3->smplx[0][i] = Ass3->smplx[ilowest][i];
				Ass3->smplx[ilowest][i] = swap;
			}
			cout << "nfunc = "<< nfunc << endl;
			//TODO
			//free memory
			break;
		}
		//is max exceeded? >> end calc
		if (nfunc >= max_iter) {
			cout << "Max exceeded." << endl;
			break;
		}
		nfunc += 2;
		//Find reflection point
		err = xtrap(Ass3, y, smplxsum, highest, -1.0);
		if (err <= y[ilowest])
			//extend reflection point
			err = xtrap(Ass3, y, smplxsum, highest, 2.0);
		else if (err >= y[sechigh]) {
			ytemp = y[highest];
			//retract reflection point
			err = xtrap(Ass3, y, smplxsum, highest, 0.5);
			if (err >= ytemp) {
				for (i = 0;i <= Ass3->ldims;i++) {
					if (i != ilowest) {
						for (j = 0; j <= Ass3->ldims-1;j++)
							Ass3->smplx[i][j] = smplxsum[j] = 0.5*(Ass3->smplx[i][j] + Ass3->smplx[ilowest][j]);
						//TODO
						for (j = 0; j <= Ass3->ldims - 1;j++) Ass3->init[j + Ass3->ldims] = smplxsum[j];
						y[i] = evaluate(Ass3); //with smplxsum
					}
				}
				nfunc += Ass3->ldims;
				
				for (j = 0; j <= Ass3->ldims-1; j++) {
					for (sum = 0.0,i = 0; i <= Ass3->ldims; i++) sum += Ass3->smplx[i][j];
					smplxsum[j] = sum;
				}
			}
		}
		else --(nfunc);
		cout << "J = " << Ass3->J << endl;
		cout << "n = " << nfunc << endl;
	} //while

	cout << "End." << endl;
	//smplxsumv.clear();
	//yv.clear();
}


double xtrap(SODE *Ass3, double y[], double smplxsum[], int highest, double fact) {
	int j, k;
	double fact1, fact2, err = 0;
	//double (*smplxnew) = new double(dims);
	vector<double> smplxnewv(Ass3->ldims);

	double* smplxnew = &smplxnewv[0];

	fact1 = (1.0 - fact) / Ass3->ldims;
	fact2 = fact1 - fact;

	for (j = 0;j <= Ass3->ldims - 1;j++) {
		smplxnew[j] = smplxsum[j] * fact1 - Ass3->smplx[highest][j] * fact2;
	}
	//TODO
	for (j = 0; j <= Ass3->ldims - 1;j++) Ass3->init[j + Ass3->ldims] = smplxnew[j];
	err = (evaluate)(Ass3); //with smplxnew

	cout << endl;
	cout << "Error = " << err  << endl;
	cout << endl;
	if (err < y[highest]) {
		y[highest] = err;
		for (j = 0;j <= Ass3->ldims-1;j++) {
			smplxsum[j] += smplxnew[j] - Ass3->smplx[highest][j];
			Ass3->smplx[highest][j] = smplxnew[j];
		}
	}
	//smplxnewv.clear();
	return err;

	
}



