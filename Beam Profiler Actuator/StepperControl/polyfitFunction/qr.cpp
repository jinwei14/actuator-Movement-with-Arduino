//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: qr.cpp
//
// MATLAB Coder version            : 3.1
// C/C++ source code generated on  : 30-Jun-2017 10:00:52
//

// Include Files
#include "stdafx.h"
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "qr.h"
#include "xzlarf.h"

// Function Definitions

//
// Arguments    : const double A[8]
//                double *Q
//                double R[8]
// Return Type  : void
//
void qr(const double A[8], double *Q, double R[8])
{
	double b_A[8];
	double work[8];
	int j;
	for (j = 0; j < 8; j++) {
		b_A[j] = A[j];
		work[j] = 0.0;
	}

	b_A[0] = 1.0;
	xzlarf(1, 7, 0.0, b_A, work);
	b_A[0] = A[0];
	R[0] = A[0];
	for (j = 0; j < 7; j++) {
		R[j + 1] = b_A[j + 1];
	}

	*Q = 1.0;
}

//
// File trailer for qr.cpp
//
// [EOF]
//
