#include "Opt.h"
using namespace std;

double evaluate(SODE *Ass3) {
	double E = 0;
	Ass3->x[0] = 0;
	Ass3->x[1] = 14;
	Ass3->x[2] = 0;
	Ass3->x[3] = 2.5;
	Ass3->x[4] = 0;
	Ass3->x[5] = 0;

	RK(Ass3);

	E = Ass3->Err();	

	return E;
}
#ifndef CONSTRAINED
void sort(double *arr, double smplx[7][6], int size) {
	double temp;
	double ts[5];
	int j,i,k;

	for (i = 0; i < (size - 1); ++i)
	{
		for (j = 0; j < size - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;

				for (k = 0; k <= 5 - 1; k++ ) {
					ts[k] = smplx[j + 1][k];
					smplx[j + 1][k] = smplx[j][k];
					smplx[j][k] = ts[k];
				}
				
			}
		}
	}
}
#endif
#ifdef CONSTRAINED
void sort(double *arr, double smplx[8][7], int size) {
	double temp;
	double ts[5];
	int j, i, k;

	for (i = 0; i < (size - 1); ++i)
	{
		for (j = 0; j < size - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;

				for (k = 0; k <= 5 - 1; k++) {
					ts[k] = smplx[j + 1][k];
					smplx[j + 1][k] = smplx[j][k];
					smplx[j][k] = ts[k];
				}

			}
		}
	}
}
#endif

int main(void) {
#ifndef CONSTRAINED
	const int len = 7;
#endif
#ifdef CONSTRAINED
	const int len = 8;
#endif
	bool check = false;
	string temp;
	SODE Ass3;
	SODE *ptrAss3;
	ptrAss3 = &Ass3;
	double least[] = { 0,0 };
	int i,j,k;
	double E[len], E_min, E_new;
	double smplx[len][len-1];

	srand(time(NULL));

	Ass3.h = 0.001;

	for (i = 0; i <= Ass3.dims - 1; i++) Ass3.init[i] = 0; //initialization variables
	Ass3.init[0] = 0;
	Ass3.init[1] = 14;
	Ass3.init[2] = 0;
	Ass3.init[3] = 2.5;
	Ass3.init[4] = 0;
	Ass3.init[5] = 0;
#ifdef CONSTRAINED
	Ass3.init[6] = 0;
#endif
	for (i = 0; i <= Ass3.dims - 1; i++) Ass3.x[i] = 0; //clear final values and change to initial
	Ass3.x[0] = 0;
	Ass3.x[1] = 14;
	Ass3.x[2] = 0;
	Ass3.x[3] = 2.5;
	Ass3.x[4] = 0;
	Ass3.x[5] = 0;
#ifdef CONSTRAINED
	Ass3.x[6] = 0;
#endif
	for (i = 0; i <= len-1; i++) E[i] = 0;

	for (j = 0; j <= Ass3.ldims-1; j++) Ass3.init[Ass3.ldims + j] = (rand() / 10000000.0);
	
	E[0] = evaluate(ptrAss3);
	for (j = 0; j <= Ass3.ldims-1; j++) smplx[0][j] = Ass3.init[Ass3.ldims + j];

	for (i = 1; i <= len-1; i++) E[i] = E[0];
	for (j = 1; j <= len - 1; j++) {
		for (i = 0; i <= len - 2; i++) smplx[j][i] = smplx[0][i];
	}


	for (i = 0; i <= 10000; i++) {
		E_min = E[len - 1];
		check = false;
		for( j = 0; j <= Ass3.ldims-1; j++) Ass3.init[Ass3.ldims + j] = (rand()/10000000.0);
		
		E_new = evaluate(ptrAss3);

		if (E_new < E_min) {
			//for( j = 0; j <= Ass3.ldims-1; j++) smplx[j] = Ass3.init[Ass3.ldims + j];

			

			for (k = 0; k <= len - 1; k++ ) {
				if (E_new == E[k]) {
					check = false;
					break;
				}
				else check = true;
			}
			if (check) {
				E_min = E_new;
				E[len-1] = E_new;
				for (j = 0; j <= Ass3.ldims - 1; j++) smplx[len-1][j] = Ass3.init[Ass3.ldims + j];
				sort(E, smplx, len);
				check = false;
			}

			cout << "Randomize:" << endl;
			cout << "\nError = " << E[0] << "\ti0 = " << smplx[0] << "\ti1 = " << smplx[1] << "\ti2 = " << smplx[2] << "\ti3 = " << smplx[3] << "\ti4 = " << smplx[4]
				<< endl;
		}
		
	}
	k = 0; //for NM iterations+
	//for (k = 0; k <= len - 1; k++) {


		for (i = 0; i <= len - 1; i++) {
			for (j = 0; j <= len - 2; j++) {
				Ass3.smplx[i][j] = smplx[i][j];
			}
		}

		/*Ass3.smplx[0][0] = smplx[0][0];
		Ass3.smplx[0][1] = smplx[0][1];
		Ass3.smplx[0][2] = smplx[0][2];
		Ass3.smplx[0][3] = smplx[0][3];
		Ass3.smplx[0][4] = smplx[0][4];

		Ass3.smplx[1][0] = 1;
		Ass3.smplx[1][1] = 0;
		Ass3.smplx[1][2] = 0;
		Ass3.smplx[1][3] = 0;
		Ass3.smplx[1][4] = 0;

		Ass3.smplx[2][0] = 0;
		Ass3.smplx[2][1] = 1;
		Ass3.smplx[2][2] = 0;
		Ass3.smplx[2][3] = 0;
		Ass3.smplx[2][4] = 0;

		Ass3.smplx[3][0] = 0;
		Ass3.smplx[3][1] = 0;
		Ass3.smplx[3][2] = 1;
		Ass3.smplx[3][3] = 0;
		Ass3.smplx[3][4] = 0;

		Ass3.smplx[4][0] = 0;
		Ass3.smplx[4][1] = 0;
		Ass3.smplx[4][2] = 0;
		Ass3.smplx[4][3] = 1;
		Ass3.smplx[4][4] = 0;

		Ass3.smplx[5][0] = 0;
		Ass3.smplx[5][1] = 0;
		Ass3.smplx[5][2] = 0;
		Ass3.smplx[5][3] = 0;
		Ass3.smplx[5][4] = 1;
		
		Ass3.smplx[6][0] = 0;
		Ass3.smplx[6][1] = 0;
		Ass3.smplx[6][2] = 0;
		Ass3.smplx[6][3] = 0;
		Ass3.smplx[6][4] = 1;*/


		for (i = 0; i <= Ass3.dims - 1; i++) Ass3.init[i] = 0; //initialization variables
		Ass3.init[0] = 0;
		Ass3.init[1] = 14;
		Ass3.init[2] = 0;
		Ass3.init[3] = 2.5;
		Ass3.init[4] = 0;
		Ass3.init[5] = 0;
#ifdef CONSTRAINED
		Ass3.init[6] = 0;
#endif
		for (i = 0; i <= Ass3.dims - 1; i++) Ass3.x[i] = 0; //clear final values and change to initial
		Ass3.x[0] = 0;
		Ass3.x[1] = 14;
		Ass3.x[2] = 0;
		Ass3.x[3] = 2.5;
		Ass3.x[4] = 0;
		Ass3.x[5] = 0;
#ifdef CONSTRAINED
		Ass3.x[6] = 0;
#endif

		//RK(Ass3);
		//Err(x);
		MinFunc(ptrAss3);
		cout << "Initial values:" << endl;
		cout << "x1 = " << ptrAss3->init[0] << "\tx2 = " << ptrAss3->init[1] << "\tx3 = " << ptrAss3->init[2] << "\tx4 = " << ptrAss3->init[3] << "\tx5 = " << ptrAss3->init[4] << "\tx6 = " << ptrAss3->init[5]
			<< "\n" << endl;

		cout << endl;

		cout << "Final values:" << endl;
		cout << "x1 = " << ptrAss3->x[0] << "\tx2 = " << ptrAss3->x[1] << "\tx3 = " << ptrAss3->x[2] << "\tx4 = " << ptrAss3->x[3] << "\tx5 = " << ptrAss3->x[4] << "\tx6 = " << ptrAss3->x[5]
			<< "\n" << endl;

		ptrAss3->ctrl0 = 0;
		ptrAss3->ctrl1 = 0;

		RKf(ptrAss3);

		cout << "Initial values:" << endl;
		cout << "x1 = " << ptrAss3->init[0] << "\tx2 = " << ptrAss3->init[1] << "\tx3 = " << ptrAss3->init[2] << "\tx4 = " << ptrAss3->init[3] << "\tx5 = " << ptrAss3->init[4] << "\tx6 = " << ptrAss3->init[5]
			<< "\n" << endl;

		cout << endl;

		cout << "Final values:" << endl;
		cout << "x1 = " << ptrAss3->x[0] << "\tx2 = " << ptrAss3->x[1] << "\tx3 = " << ptrAss3->x[2] << "\tx4 = " << ptrAss3->x[3] << "\tx5 = " << ptrAss3->x[4] << "\tx6 = " << ptrAss3->x[5]
			<< "\n" << endl;

		cout << "Error:" << endl;
		cout << "E = " << ptrAss3->Err()
			<< "\n" << endl;

		cout << "PI:" << endl;
		cout << "J = " << ptrAss3->J
			<< "\n" << endl;

		getline(cin, temp);
		//while (1);
	//}

	return 0;
}