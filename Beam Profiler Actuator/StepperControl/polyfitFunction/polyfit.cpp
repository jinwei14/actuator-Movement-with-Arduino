//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: polyfit.cpp
//
// MATLAB Coder version            : 3.1
// C/C++ source code generated on  : 30-Jun-2017 10:00:52
//

// Include Files
#include "stdafx.h"
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "xzlarf.h"
#include "qr.h"

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
	double y;
	double d0;
	double d1;
	if (rtIsNaN(u0) || rtIsNaN(u1)) {
		y = rtNaN;
	}
	else {
		d0 = fabs(u0);
		d1 = fabs(u1);
		if (rtIsInf(u1)) {
			if (d0 == 1.0) {
				y = rtNaN;
			}
			else if (d0 > 1.0) {
				if (u1 > 0.0) {
					y = rtInf;
				}
				else {
					y = 0.0;
				}
			}
			else if (u1 > 0.0) {
				y = 0.0;
			}
			else {
				y = rtInf;
			}
		}
		else if (d1 == 0.0) {
			y = 1.0;
		}
		else if (d1 == 1.0) {
			if (u1 > 0.0) {
				y = u0;
			}
			else {
				y = 1.0 / u0;
			}
		}
		else if (u1 == 2.0) {
			y = u0 * u0;
		}
		else if ((u1 == 0.5) && (u0 >= 0.0)) {
			y = sqrt(u0);
		}
		else if ((u0 < 0.0) && (u1 > floor(u1))) {
			y = rtNaN;
		}
		else {
			y = pow(u0, u1);
		}
	}

	return y;
}

//
// POLYFIT Fit polynomial to data.
//    POLYFIT(X,Y,N) finds the coefficients of a polynomial P(X) of
//    degree N that fits the data, P(X(I))~=Y(I), in a least-squares sense.
//
//    [P,S] = POLYFIT(X,Y,N) returns the polynomial coefficients P and a
//    structure S for use with POLYVAL to obtain error estimates on
//    predictions.  If the errors in the data, Y, are independent normal
//    with constant variance, POLYVAL will produce error bounds which
//    contain at least 50% of the predictions.
//
//    The structure S contains the Cholesky factor of the Vandermonde
//    matrix (R), the degrees of freedom (df), and the norm of the
//    residuals (normr) as fields.
//
//    [P,S,MU] = POLYFIT(X,Y,N) finds the coefficients of a polynomial
//    in XHAT = (X-MU(1))/MU(2) where MU(1) = mean(X) and MU(2) = std(X).
//    This centering and scaling transformation improves the numerical
//    properties of both the polynomial and the fitting algorithm.
//
//    Warning messages result if N is >= length(X), if X has repeated, or
//    nearly repeated, points, or if X might need centering and scaling.
//
//    See also POLY, POLYVAL, ROOTS.
// Arguments    : double x
//                double y
//                double n
//                double p[8]
//                struct0_T *S
//                double mu[2]
// Return Type  : voidvf
//
void polyfit(double x, double y, double n, double p[8], struct0_T *S, double mu
	[2])
{
	double V[8];
	double r;
	int j;
	double b_j;
	double Q;
	double R[8];
	double B;
	int k;
	double vn1[8];
	double b_x[8];
	signed char jpvt[8];
	int rankR;
	int ix;
	double work[8];
	double tol;

	//    Copyright 1984-2002 The MathWorks, Inc.
	//    $Revision: 5.17 $  $Date: 2002/04/09 00:14:25 $
	//  The regression problem is formulated in matrix format as:
	//
	//     y = V*p    or
	//
	//           3  2
	//     y = [x  x  x  1] [p3
	//                       p2
	//                       p1
	//                       p0]
	//
	//  where the vector p contains the coefficients to be found.  For a
	//  7th order polynomial, matrix V would be:
	//
	V[0] = rt_powd_snf(x, 7.0);
	V[1] = rt_powd_snf(x, 6.0);
	V[2] = rt_powd_snf(x, 5.0);
	V[3] = rt_powd_snf(x, 4.0);
	V[4] = rt_powd_snf(x, 3.0);
	V[5] = x * x;
	V[6] = x;
	V[7] = 1.0;
	r = x - x;
	mu[0] = x;
	mu[1] = sqrt(r * r);
	x = (x - x) / mu[1];

	//  Construct Vandermonde matrix.
	V[(int)(n + 1.0) - 1] = 1.0;
	for (j = 0; j < (int)-(1.0 + (-1.0 - n)); j++) {
		b_j = n + -(double)j;
		V[(int)b_j - 1] = x * V[(int)(b_j + 1.0) - 1];
	}

	//  Solve least squares problem, and save the Cholesky factor.
	qr(V, &Q, R);

	// ws = warning('off','all');
	B = Q * y;
	k = 0;
	for (j = 0; j < 8; j++) {
		b_x[j] = R[j];
		jpvt[j] = (signed char)(1 + j);
		vn1[j] = fabs(R[k]);
		k++;
	}

	rankR = 0;
	ix = 0;
	r = vn1[0];
	for (k = 0; k < 7; k++) {
		ix++;
		if (vn1[ix] > r) {
			rankR = k + 1;
			r = vn1[ix];
		}
	}

	if (rankR + 1 != 1) {
		b_x[rankR] = R[0];
		b_x[0] = R[rankR];
		jpvt[0] = (signed char)(rankR + 1);
	}

	r = b_x[0];
	b_x[0] = 1.0;
	memset(&work[0], 0, sizeof(double) << 3);
	xzlarf(1, 7, 0.0, b_x, work);
	rankR = 0;
	tol = 8.0 * fabs(r) * 2.2204460492503131E-16;
	while ((rankR < 1) && (fabs(r) >= tol)) {
		rankR = 1;
	}

	memset(&vn1[0], 0, sizeof(double) << 3);
	ix = 1;
	while (ix <= rankR) {
		vn1[jpvt[0] - 1] = B;
		ix = 2;
	}

	while (rankR > 0) {
		vn1[jpvt[0] - 1] /= r;
		rankR = 0;
	}

	//  Same as p = V\y;
	// warning(ws);
	//   warning('MATLAB:polyfit:PolyNotUnique', ...
	//       'Polynomial is not unique; degree >= number of data points.')
	//  Polynomial coefficients are row vectors by convention.
	//  S is a structure containing three elements: the Cholesky factor of the
	//  Vandermonde matrix, the degrees of freedom and the norm of the residuals.  
	S->df = 1.0 - (n + 1.0);
	r = 0.0;
	for (rankR = 0; rankR < 8; rankR++) {
		p[rankR] = vn1[rankR];
		S->R[rankR] = R[rankR];
		r += V[rankR] * vn1[rankR];
	}

	S->normr = fabs(y - r);
}

//
// File trailer for polyfit.cpp
//
// [EOF]
//
