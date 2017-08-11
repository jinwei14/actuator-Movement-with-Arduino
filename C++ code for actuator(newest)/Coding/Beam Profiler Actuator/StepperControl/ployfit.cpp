#include "stdafx.h"
#include "ployfit.h"

ployfit::ployfit() {
}
ployfit::~ployfit() {
}

//Polynomial fit function
int ployfit::polyfit(const double* const dependentValues,
	const double* const independentValues,
	unsigned int        countOfElements,
	unsigned int        order,
	double*             coefficients)
{
	// Declarations...
	// ----------------------------------
	//Arbitary value to ensure program doesn't get stuck in loop
	enum { maxOrder = 5 };
	double B[maxOrder + 1] = { 0.0f };
	double P[((maxOrder + 1) * 2) + 1] = { 0.0f };
	double A[(maxOrder + 1) * 2 * (maxOrder + 1)] = { 0.0f };

	double x, y, powx;
	unsigned int ii, jj, kk;
	// Verify initial conditions....
	// ----------------------------------
	// This method requires that the countOfElements > 
	// (order+1) 
	if (countOfElements <= order)
		return -1;

	// This method has imposed an arbitrary bound of
	// order <= maxOrder.  Increase maxOrder if necessary.
	if (order > maxOrder)
		return -1;
	// Begin Code...
	// ----------------------------------
	// Identify the column vector
	for (ii = 0; ii < countOfElements; ii++)
	{
		x = dependentValues[ii];
		y = independentValues[ii];
		powx = 1;

		for (jj = 0; jj < (order + 1); jj++)
		{
			B[jj] = B[jj] + (y * powx);
			powx = powx * x;
		}
	}

	// Initialize the PowX array
	P[0] = countOfElements;
	// Compute the sum of the Powers of X
	for (ii = 0; ii < countOfElements; ii++)
	{
		x = dependentValues[ii];
		powx = dependentValues[ii];

		for (jj = 1; jj < ((2 * (order + 1)) + 1); jj++)
		{
			P[jj] = P[jj] + powx;
			powx = powx * x;
		}
	}

	// Initialize the reduction matrix
	//
	for (ii = 0; ii < (order + 1); ii++)
	{
		for (jj = 0; jj < (order + 1); jj++)
		{
			A[(ii * (2 * (order + 1))) + jj] = P[ii + jj];
		}
		A[(ii*(2 * (order + 1))) + (ii + (order + 1))] = 1;
	}

	// Move the Identity matrix portion of the redux matrix
	// to the left side (find the inverse of the left side
	// of the redux matrix
	for (ii = 0; ii < (order + 1); ii++)
	{
		x = A[(ii * (2 * (order + 1))) + ii];
		if (x != 0)
		{
			for (kk = 0; kk < (2 * (order + 1)); kk++)
			{
				A[(ii * (2 * (order + 1))) + kk] =
					A[(ii * (2 * (order + 1))) + kk] / x;
			}

			for (jj = 0; jj < (order + 1); jj++)
			{
				if ((jj - ii) != 0)
				{
					y = A[(jj * (2 * (order + 1))) + ii];
					for (kk = 0; kk < (2 * (order + 1)); kk++)
					{
						A[(jj * (2 * (order + 1))) + kk] =
							A[(jj * (2 * (order + 1))) + kk] -
							y * A[(ii * (2 * (order + 1))) + kk];
					}
				}
			}
		}
		else
		{
			// Cannot work with singular matrices
			return -1;
		}
	}

	// Calculate and Identify the coefficients
	for (ii = 0; ii < (order + 1); ii++)
	{
		for (jj = 0; jj < (order + 1); jj++)
		{
			x = 0;
			for (kk = 0; kk < (order + 1); kk++)
			{
				x = x + (A[(ii * (2 * (order + 1))) + (kk + (order + 1))] *
					B[kk]);
			}
			coefficients[ii] = x;
		}
	}
	return 0;
}

void ployfit::outputResult() {


		//Used to multiply Z by 10^-3 in order to get correct units
		int zUnitCorrection;
		for (zUnitCorrection = 0; zUnitCorrection < 15; zUnitCorrection++) z[zUnitCorrection] *= 0.001;
	
		//Used to multiply w by 2x due to ideal data being radius
		int wRadiusCorrection;
		for (wRadiusCorrection = 0; wRadiusCorrection < 15; wRadiusCorrection++) w[wRadiusCorrection] *= 2;
	
		//Used to multiply Z by 10^-6 in order to get correct units
		int wUnitCorrection;
		for (wUnitCorrection = 0; wUnitCorrection < 15; wUnitCorrection++) w[wUnitCorrection] *= 0.000001;
	
		//Used to square w fitting this against z eliminates the sqrt from the function allowing the standard polyfit function to be used.
		int wSquared;
		for (wSquared = 0; wSquared < 15; wSquared++) w[wSquared] = w[wSquared] * w[wSquared];
	
		//Run the polyfit function with the values calculated
		result = polyfit(z,
			w,
			countOfElements,
			order,
			coefficients);
	
		/*CHECK_EQUAL(0, result);
		DOUBLES_EQUAL(0.5, coefficients[3], acceptableError);
		DOUBLES_EQUAL(2.5, coefficients[2], acceptableError);
		DOUBLES_EQUAL(1.0, coefficients[1], acceptableError);
		DOUBLES_EQUAL(3.0, coefficients[0], acceptableError);*/
	
		//These values are the coefficients equivilent  to ax^2 + bx + c
		double a = coefficients[2];
		double b = coefficients[1];
		double c = coefficients[0];
	
		std::cout << " Coefficients, a, b, and c, are: " << std::endl;
		//Prints to coefficients incase they are needed
		for (int i = 0; i < 3; i++)
			std::cout << coefficients[i] << std::endl;
	
		//Full M2 equation
		double M2 = (M_PI / (8 * lambda))*sqrt((4 * a*c) - (pow(b, 2)));
	
		//Prints the M2 value
		std::cout << "M2: ";
		std::cout << M2 << std::endl;
	
		//Waist location
		double z0 = -b / (2 * c);
	
		//Prints the z0, waist location, value
		std::cout << "z0, Waist Location: ";
		std::cout << z0 << std::endl;
	
		// Waist diameter
		double w0 = (1 / (2 * sqrt(c)))*sqrt((4 * a*c) - (pow(b, 2)));
	
		//Prints the w0, waist diameter, value
		std::cout << "w0, Waist Diameter: ";
		std::cout << w0 << std::endl;
	
		Sleep(3000);
	

}


void ployfit::addZposition(int num,int pos) {
	z[pos] = num;
}
void ployfit::addD4sigma(int num, int pos) {
	w[pos] = num;
}

//int main()
//{
//	//Used to multiply Z by 10^-3 in order to get correct units
//	int zUnitCorrection;
//	for (zUnitCorrection = 0; zUnitCorrection < 15; zUnitCorrection++) z[zUnitCorrection] *= 0.001;
//
//	//Used to multiply w by 2x due to ideal data being radius
//	int wRadiusCorrection;
//	for (wRadiusCorrection = 0; wRadiusCorrection < 15; wRadiusCorrection++) w[wRadiusCorrection] *= 2;
//
//	//Used to multiply Z by 10^-6 in order to get correct units
//	int wUnitCorrection;
//	for (wUnitCorrection = 0; wUnitCorrection < 15; wUnitCorrection++) w[wUnitCorrection] *= 0.000001;
//
//	//Used to square w fitting this against z eliminates the sqrt from the function allowing the standard polyfit function to be used.
//	int wSquared;
//	for (wSquared = 0; wSquared < 15; wSquared++) w[wSquared] = w[wSquared] * w[wSquared];
//
//	//Run the polyfit function with the values calculated
//	result = polyfit(z,
//		w,
//		countOfElements,
//		order,
//		coefficients);
//
//	/*CHECK_EQUAL(0, result);
//	DOUBLES_EQUAL(0.5, coefficients[3], acceptableError);
//	DOUBLES_EQUAL(2.5, coefficients[2], acceptableError);
//	DOUBLES_EQUAL(1.0, coefficients[1], acceptableError);
//	DOUBLES_EQUAL(3.0, coefficients[0], acceptableError);*/
//
//	//These values are the coefficients equivilent  to ax^2 + bx + c
//	double a = coefficients[2];
//	double b = coefficients[1];
//	double c = coefficients[0];
//
//	std::cout << " Coefficients, a, b, and c, are: " << std::endl;
//	//Prints to coefficients incase they are needed
//	for (int i = 0; i < 3; i++)
//		std::cout << coefficients[i] << std::endl;
//
//	//Full M2 equation
//	double M2 = (M_PI / (8 * lambda))*sqrt((4 * a*c) - (pow(b, 2)));
//
//	//Prints the M2 value
//	std::cout << "M2: ";
//	std::cout << M2 << std::endl;
//
//	//Waist location
//	double z0 = -b / (2 * c);
//
//	//Prints the z0, waist location, value
//	std::cout << "z0, Waist Location: ";
//	std::cout << z0 << std::endl;
//
//	// Waist diameter
//	double w0 = (1 / (2 * sqrt(c)))*sqrt((4 * a*c) - (pow(b, 2)));
//
//	//Prints the w0, waist diameter, value
//	std::cout << "w0, Waist Diameter: ";
//	std::cout << w0 << std::endl;
//
//	Sleep(30000);
//	return result;
//
//}