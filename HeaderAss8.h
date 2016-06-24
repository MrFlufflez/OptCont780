#include "SODE.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

void MinFunc(SODE *Ass3);
double xtrap(SODE *Ass3, double y[], double smplxsum[], int highest, double fact);
void RK(SODE *Ass3);
void RKf(SODE *Ass3);
//void func(double dx[], double x[]);//

double evaluate(SODE *Ass3);