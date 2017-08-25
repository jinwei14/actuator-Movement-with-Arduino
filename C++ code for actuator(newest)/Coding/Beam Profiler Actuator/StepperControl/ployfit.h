#include "stdafx.h"

#ifndef PLOYFIT_H
#define PLOYFIT_H
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include <math.h>

#define _USE_MATH_DEFINES
#define M_PI  3.14159265358979323846  /* pi */

using namespace std;
//The order of the equation, in this case it is second order
const unsigned int order = 2;
//How many elements are in the array. Will either need changing or coding to pass on to the polyfit function
const unsigned int countOfElements = 15;
//Acceptable error in the system
const double acceptableError = 0.01;
class ployfit {

private:
	//Resulting array of coefs
	double coefficients[order + 1];
	//Holds the result from the polyfit equation
	int result;
	//Wavelength variable
	double lambda = 1080 * pow(10, -9);

	//Ideal data that will produce M^2 ~ 1.1 
	//Z - position of measurements(m)
	double z[countOfElements]
	= { 750, 775, 800, 825, 850, 950, 975, 1000, 1025, 1050, 1150, 1175, 1200, 1225, 1250, };
	//Second moment diameter measurements (m) - d4sigma in spiricon
	double w[countOfElements];
	//	= { 626.7, 567.9, 508.8, 450.5, 393.4, 193.1, 163.7, 154, 168.1, 200.8, 404.5, 461.8, 520, 579.2, 638.5, };

public:
	ployfit();//constructor
	~ployfit();//deconstuctor
	int polyfit(const double* const dependentValues,
		const double* const independentValues,
		unsigned int        countOfElements,
		unsigned int        order,
		double*             coefficients);
	string outputResult();
	void setZposition(int num,int pos);
	void setD4sigma(int num,int pos);
	double* getZposition() { return z; };
	double* getD4sigma() { return w; };
	//int getZpositionSize() { return z->; };
};
#endif