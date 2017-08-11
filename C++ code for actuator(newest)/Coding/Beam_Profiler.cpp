// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <direct.h>
#include <vcclr.h>  
#include <fstream>
#include <msclr\marshal_cppstd.h>
#include <math.h>
#include <string>

using namespace System;
using namespace System::IO::Ports;
using namespace std;

//
//
// uStepper VARIABLES
//
//
gcroot<String^> portName; //Defines the COM Port usaed to communicate with the uStepper 
int baudRate = 9600;
gcroot<SerialPort^> uStepper;

void TraverseMoveForward() {

	arduino->WriteLine("1");

	Sleep(1000);

	String^ message = uStepper->ReadLine(); //Reads the voltage value from the uStepper

	std::string distanceTravelled; //Initialises the variable for distance travelled
	distanceTravelled = msclr::interop::marshal_as<std::string>(message); //Converts the uStepper value into a string
	std::cout << distanceTravelled << std::endl; //Prints the string to the console for checking
}

void TraverseMoveBackwards() {

	arduino->WriteLine("2");

	Sleep(1000);

	String^ message = uStepper->ReadLine(); //Reads the voltage value from the uStepper

	std::string distanceTravelled; //Initialises the variable for distance travelled
	distanceTravelled = msclr::interop::marshal_as<std::string>(message); //Converts the uStepper value into a string
	std::cout << distanceTravelled << std::endl; //Prints the string to the console for checking
}

int main()
{
	string portNameStdStr;

	//Asks the user to specifiy the COM Port
	std::cout << "Please enter the COM Port that the uStepper is attached to, in the format 'COMX': ";
	std::cin >> portNameStdStr;

	portName = gcnew String(portNameStdStr.c_str());

	
	int x = 1;

	//while (x < 2) {
		std::cout << "Please enter 'F' for forwards, or 'B' for backwards movement" << std::endl;
		
		std::cin >> programSelect;

		Sleep(4000);

		if (programSelect == "F" || programSelect == "f") {
			TraverseMoveForward();
		}
		else if (programSelect == "B" || programSelect == "b") {
			TraverseMoveBackwards();
		}
		else {
			std::cout << "Error. Please enter a correct profile letter";

		}
	//}


    return 0;
}

