#include <stdlib.h>
#include <stdio.h>
#include "stdafx.h"
#include <iostream>
#include <Engine.h> //include the matlab engine
#include <cmath>

//additional dependency part from linker
#pragma comment (lib, "libmat.lib")//type and "name"
#pragma comment (lib, "libmx.lib")
#pragma comment (lib, "libmex.lib")
#pragma comment (lib, "libeng.lib")

using namespace std;
#define  BUFSIZE 256

int main()

{
	Engine *ep;
	mxArray *T = NULL, *result = NULL;
	char buffer[BUFSIZE + 1];
	double time[10] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

	/*
	* Call engOpen with a NULL string. This starts a MATLAB process
	* on the current host using the command "matlab".
	*/
	if (!(ep = engOpen(""))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}

	/*
	* PART I
	*
	* For the first half of this demonstration, we will send data
	* to MATLAB, analyze the data, and plot the result.
	*/

	/*
	* Create a variable for our data
	*/
	T = mxCreateDoubleMatrix(1, 10, mxREAL);
	memcpy((void *)mxGetPr(T), (void *)time, sizeof(time));
	/*
	* Place the variable T into the MATLAB workspace
	*/
	engPutVariable(ep, "T", T);

	/*
	* Evaluate a function of time, distance = (1/2)g.*t.^2
	* (g is the acceleration due to gravity)
	*/
	engEvalString(ep, "D = .5.*(-9.8).*T.^2;");

	/*
	* Plot the result
	*/
	engEvalString(ep, "plot(T,D);");
	engEvalString(ep, "title('Position vs. Time for a falling object');");
	engEvalString(ep, "xlabel('Time (seconds)');");
	engEvalString(ep, "ylabel('Position (meters)');");

	/*
	* use fgetc() to make sure that we pause long enough to be
	* able to see the plot
	*/
	printf("Hit return to continue\n\n");
	fgetc(stdin);
	/*
	* We're done for Part I! Free memory, close MATLAB figure.
	*/
	printf("Done for Part I.\n");
	mxDestroyArray(T);
	engEvalString(ep, "close;");


	/*
	* PART II
	*
	* For the second half of this demonstration, we will request
	* a MATLAB string, which should define a variable X.  MATLAB
	* will evaluate the string and create the variable.  We
	* will then recover the variable, and determine its type.
	*/

	/*
	* Use engOutputBuffer to capture MATLAB output, so we can
	* echo it back.  Ensure first that the buffer is always NULL
	* terminated.
	*/

	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);
	while (result == NULL) {
		char str[BUFSIZE + 1];
		/*
		* Get a string input from the user
		*/
		printf("Enter a MATLAB command to evaluate.  This command should\n");
		printf("create a variable X.  This program will then determine\n");
		printf("what kind of variable you created.\n");
		printf("For example: X = 1:5\n");
		printf(">> ");

		fgets(str, BUFSIZE, stdin);

		/*
		* Evaluate input with engEvalString
		*/
		engEvalString(ep, str);

		/*
		* Echo the output from the command.
		*/
		printf("%s", buffer);

		/*
		* Get result of computation
		*/
		printf("\nRetrieving X...\n");
		if ((result = engGetVariable(ep, "X")) == NULL)
			printf("Oops! You didn't create a variable X.\n\n");
		else {
			printf("X is class %s\t\n", mxGetClassName(result));
		}
	}

	/*
	* We're done! Free memory, close MATLAB engine and exit.
	*/
	printf("Done!\n");
	mxDestroyArray(result);
	engClose(ep);
	system("pause");
	return EXIT_SUCCESS;
}


//
//
//int main() {
//	//double pixel_size_x = 5e-6; //5 * pow(10, -6), Pixel size, Units m 
//	//double Pixel_size_y = 5e-6;
//	////Far - field mirror focal lengths
//	////Focal length of sampling optic, Units m
//	//double Focal_Length = 0.152;      
//
//	//cout << pixel_size_x << endl;
//
//	//_sleep(30000);
//
//	//open engine create the pointer to the engine reference this name later
//	Engine* m_pEngine;
//	m_pEngine = engOpen("null");
//
//	const int arraysize = 1000;
//	const double degTorad = .0174;
//
//	double sinArray[arraysize];
//	double cosArray[arraysize];
//	double degree[arraysize];
//
//	for (int i = 0; i < arraysize; i++) {
//		degree[i] = i;
//		sinArray[i] = sin(i*degTorad);
//		cosArray[i] = cos(i*degTorad);
//	}
//
//	cout << "Example 1 or 2 ?";
//	int sim;
//	cin >> sim;
//
//	//example below 
//	//pass entire array to be plotted 
//
//	if (sim == 1) {
//		//passing a one dementional array (vector) of length arraysize
//		mxArray* SIN = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
//		//putting value into SIN -get pointer to SIN point to the array sinArray. size must be entered
//		memcpy((void*)mxGetPr(SIN), (void*)sinArray, sizeof(double)*arraysize);
//		//put the variable through the matlab engine.
//		engPutVariable(m_pEngine, "SinGraph", SIN);
//
//		//passing a one dementional array (vector) of length arraysize
//		mxArray* COS = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
//		//putting value into SIN -get pointer to SIN point to the array sinArray. size must be entered
//		memcpy((void*)mxGetPr(COS), (void*)sinArray, sizeof(double)*arraysize);
//		//put the variable through the matlab engine.
//		engPutVariable(m_pEngine, "CosGraph", COS);
//
//
//		mxArray* DEG = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
//		memcpy((void*)mxGetPr(DEG), (void*)sinArray, sizeof(double)*arraysize);
//		engPutVariable(m_pEngine, "Degrees", DEG);
//
//		//open up matlab figure windows, define a figure size of my screen
//		engEvalString(m_pEngine, "figure('units','normalized','outerposition',[0 0 1 1]),");
//		//every time set command for matlab need to use engEvalstring
//		//plot(X(degree)Y(sindegree) pair, colour read. second XY pair)
//		engEvalString(m_pEngine, "plot(Degrees,SinGraph,'r',Degrees,CosGraph,'b'),grid minor, title('our matlab plot'),");
//
//		system("pause");
//	}
//
//	return EXIT_SUCCESS;
//}