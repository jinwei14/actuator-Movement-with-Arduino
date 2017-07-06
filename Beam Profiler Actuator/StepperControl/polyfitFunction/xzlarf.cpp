//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzlarf.cpp
//
// MATLAB Coder version            : 3.1
// C/C++ source code generated on  : 30-Jun-2017 10:00:52
//

// Include Files
#include "stdafx.h"
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "xzlarf.h"

// Function Definitions

//
// Arguments    : int m
//                int n
//                double tau
//                double C[8]
//                double work[8]
// Return Type  : void
//
void xzlarf(int m, int n, double tau, double C[8], double work[8])
{
	int lastv;
	int lastc;
	int i;
	int jy;
	boolean_T exitg2;
	int iac;
	int exitg1;
	int ix;
	double c;
	int i0;
	int ijA;
	if (tau != 0.0) {
		lastv = m;
		i = m;
		while ((lastv > 0) && (C[i - 1] == 0.0)) {
			lastv--;
			i--;
		}

		lastc = n;
		exitg2 = false;
		while ((!exitg2) && (lastc > 0)) {
			i = lastc;
			do {
				exitg1 = 0;
				if (i + 1 <= lastc + lastv) {
					if (C[i] != 0.0) {
						exitg1 = 1;
					}
					else {
						i++;
					}
				}
				else {
					lastc--;
					exitg1 = 2;
				}
			} while (exitg1 == 0);

			if (exitg1 == 1) {
				exitg2 = true;
			}
		}
	}
	else {
		lastv = 0;
		lastc = 0;
	}

	if (lastv > 0) {
		if (lastc == 0) {
		}
		else {
			for (jy = 1; jy <= lastc; jy++) {
				work[jy - 1] = 0.0;
			}

			jy = 0;
			for (iac = 2; iac <= lastc + 1; iac++) {
				ix = 0;
				c = 0.0;
				i0 = (iac + lastv) - 1;
				for (i = iac; i <= i0; i++) {
					c += C[i - 1] * C[ix];
					ix++;
				}

				work[jy] += c;
				jy++;
			}
		}

		if (-tau == 0.0) {
		}
		else {
			i = 1;
			jy = 0;
			for (iac = 1; iac <= lastc; iac++) {
				if (work[jy] != 0.0) {
					c = work[jy] * -tau;
					ix = 0;
					i0 = lastv + i;
					for (ijA = i; ijA + 1 <= i0; ijA++) {
						C[ijA] += C[ix] * c;
						ix++;
					}
				}

				jy++;
				i++;
			}
		}
	}
}

//
// File trailer for xzlarf.cpp
//
// [EOF]
//
