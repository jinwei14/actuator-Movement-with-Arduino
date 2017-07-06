//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int main() {
//
//	//double might not be precious
//	vector<double> zPosition;//Z-position of measurements (m)
//	vector<double> secondMoment;//Second moment diameter measurements (m) - d4sigma in spiricon
//
//	//z = [750 775 800 825 850 950 975 1000 1025 1050 1150 1175 1200 1225 1250].*10 ^ -3;
//	double start = 750/1000;
//	for (int i = 0; i++; i < 15) {
//
//		zPosition.push_back(start);
//		start = start + (25 / 1000);
//	}
//	
//	//w = [626.7 567.9 508.8 450.5 393.4 193.1 163.7 154 168.1 200.8 404.5 461.8 520 579.2 638.5].*(10 ^ -6).*2;
//	secondMoment.insert(secondMoment.end(), {
//
//		626.7,567.9,508.8,450.5,393.4,193.1,163.7,154,168.1,200.8,404.5,461.8,520,579.2,638.5 
//	});
//
//	for (auto val : secondMoment) {//loop through all the pointer in the vector and invoke the method
//		val = (val * 2)*pow(10, -6);
//		cout << val << " ";
//	}
//
//	polyfit p;
//	p = polyfit(x, y, n);
//
//
//	return EXIT_SUCCESS;


//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 3.1
// C/C++ source code generated on  : 30-Jun-2017 10:00:52
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include "stdafx.h"
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "BeamMeasurement.h"
#include "polyfit_terminate.h"
#include "polyfit_initialize.h"

// Function Declarations
static double argInit_real_T();
static void main_polyfit();

// Function Definitions

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
	return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_polyfit()
{
	double p[8];
	struct0_T S;
	double mu[2];

	// Initialize function 'polyfit' input arguments.
	// Call the entry-point 'polyfit'.
	polyfit(argInit_real_T(), argInit_real_T(), argInit_real_T(), p, &S, mu);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const[])
{
	// Initialize the application.
	// You do not need to do this more than one time.
	polyfit_initialize();

	// Invoke the entry-point functions.
	// You can call entry-point functions multiple times.
	main_polyfit();

	// Terminate the application.
	// You do not need to do this more than one time.
	polyfit_terminate();
	return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
