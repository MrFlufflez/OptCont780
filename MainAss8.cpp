#include "HeaderAss8.h"
using namespace std;

double evaluate(SODE *Ass3) {
	double E = 0;
	Ass3->x[0] = 1;
	Ass3->x[1] = 1;

	RK(Ass3);

	E = Ass3->Err();	

	return E;
}

int main(void) {
	string temp;

	SODE Ass3;
	SODE *ptrAss3;
	ptrAss3 = &Ass3;
	double least[] = { 0,0 };
	int i;
	double E_temp1, E_temp2, smplx11, smplx12, smplx13;

	Ass3.init[0] = 1;
	Ass3.init[1] = 1;
	Ass3.init[2] = 0;
	Ass3.init[3] = 0;



	Ass3.x[0] = 1;
	Ass3.x[1] = 1;
	Ass3.x[2] = 0;
	Ass3.x[3] = 0;

	Ass3.t0 = 0;
	Ass3.t1 = 4;
	Ass3.h = 0.001;

	Ass3.init[0] = 1;
	Ass3.init[1] = 1;
	Ass3.init[2] = rand();
	Ass3.init[3] = rand();

	E_temp1 = evaluate(ptrAss3);
	smplx11 = Ass3.init[2];
	smplx12 = Ass3.init[3];




	/*for (i = 0; i <= 10000; i++) {	
		Ass3.init[0] = 1;
		Ass3.init[1] = 1;
		Ass3.init[2] = rand();
		Ass3.init[3] = rand();
		E_temp2 = evaluate(ptrAss3);

		if (E_temp2 < E_temp1) {
			smplx11 = Ass3.init[2];
			smplx12 = Ass3.init[3];

			E_temp1 = E_temp2;

			cout << "Randomize:" << endl;
			cout << "\nError = " << E_temp1 << "\ti11 = " << smplx11 << "\ti12 = " << smplx12
				<< endl;
		}
		Ass3.init[0] = 1;
		Ass3.init[1] = 1;
		Ass3.init[2] = -Ass3.init[2];
		Ass3.init[3] = -Ass3.init[3];
		E_temp2 = evaluate(ptrAss3);
		if (E_temp2 < E_temp1) {
			smplx11 = Ass3.init[2];
			smplx12 = Ass3.init[3];

			E_temp1 = E_temp2;

			cout << "Randomize:" << endl;
			cout << "\nError = " << E_temp1 << "\ti11 = " << smplx11 << "\ti12 = " << smplx12
				<< endl;
		}
		

	}*/

	Ass3.smplx[0][0] = 0;//smplx11;
	Ass3.smplx[0][1] = 0;//smplx12;

	Ass3.smplx[1][0] = 0;
	Ass3.smplx[1][1] = 1;

	Ass3.smplx[2][0] = 1;
	Ass3.smplx[2][1] = -2;
	

	Ass3.init[0] = 1;
	Ass3.init[1] = 1;

	//RK(Ass3);
	//Err(x);
	MinFunc(ptrAss3);
	cout	<< "Initial values:" << endl;
	cout	<< "\nx0 = " << ptrAss3->init[0] << "\tx1 = " << ptrAss3->init[1] 			
			<< endl;

	cout	<< endl;

	cout	<< "Final values:" << endl;
	cout	<< "\nx0 = " << ptrAss3->x[0] << "\tx1 = " << ptrAss3->x[1] 			
			<< endl;
	
	ptrAss3->ctrl = 0;

	RKf(ptrAss3);

	cout << "Initial values:" << endl;
	cout << "x1 = " << ptrAss3->init[0] << "\tx2 = " << ptrAss3->init[1] << "\tl1 = " << ptrAss3->init[2] << "\tl2 = " << ptrAss3->init[3] << "\n"
		<< endl;

	cout << endl;

	cout << "Final values:" << endl;
	cout << "x1 = " << ptrAss3->x[0] << "\tx2 = " << ptrAss3->x[1] << "\tl1 = " << ptrAss3->x[2] << "\tl2 = " << ptrAss3->x[3] << "\n"
		<< endl;

	cout << "Error:" << endl;
	cout << "E = " << ptrAss3->Err() << "\n"
		<< endl;

	cout << "PI:" << endl;
	cout << "J = " << ptrAss3->J << "\n"
		<< endl;
		
	getline(cin, temp);
	//while (1);


	return 0;
}