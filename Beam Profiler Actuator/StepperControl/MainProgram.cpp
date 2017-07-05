// 
// This program is designing to work with a uStepper board and an Ooznest linear actuator. It allows the user to enter the distance they would like to move along the actuator. 
// Work will progress on linking the camera system
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
#include <algorithm>
#include <array>
#include "MyForm.h"
#using <System.dll>

using namespace System;

using namespace System::IO::Ports;
using namespace System::ComponentModel;
using namespace std;
using namespace System::Windows::Forms;

//
// uStepper VARIABLES
//

int baudRate = 115200;
gcroot<SerialPort^> uStepper;
int movementDistance;

//
// The main movement function, takes one argument, which is movement distance
//
void TraverseMove(int movement) {

	//Converts the movement integer to a string to send to the arduino
	std::string movementDistanceStr = std::to_string(movement);
	String^ movementDistanceString = gcnew String(movementDistanceStr.c_str());

	//Writes the movement distance to the arduino
	uStepper->WriteLine(movementDistanceString);
	if (movement <= 0) {
		Sleep(-movement);
	}
	else {
		Sleep(movement);
	}


	String^ message = uStepper->ReadLine(); //Reads the encoder value from the uStepper

	std::string distanceTravelled; //Initialises the variable for distance travelled
	distanceTravelled = msclr::interop::marshal_as<std::string>(message); //Converts the uStepper value into a string
	cout << distanceTravelled << endl; //Prints the string to the console for checking
}


int inputValidation(int max, int low) {

	int num;
	int flag = 0;
	string junk;

	do {
		cin >> num;
		if (cin.fail()) {//check if the input is a number
			cin.clear();//get rid of the error flag.
			num = max + max;//set the number not between 1-10
		}
		getline(cin, junk); // To skip rest of line
		if (junk[0] != '\0') {//check if user enter like a number and a other thing like "1a"
			num = max + max;
		}
		if (num < max && num > low) { //if the input number is bwteween -32768 to max
			flag = 1;//set the flag as 1 and jump out of the loop
		}
		else {//if the input number is not valid then keep entering until the right number
			cout << "input is not a right port Please re-enter: ";
		}
	} while (flag == 0);

	return num;
}

bool isdigitPort(string str) { //check if the string contain only number
	bool flag = TRUE;
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i])) {
			flag = FALSE;
		}
	}
	return flag;
}

string checkPortNum()
{
	string str1;
	string str2;
	string portNameStdStr;
	bool flag = FALSE;
	//give user a port list that has been connected.
	do {
		cli::array<String^>^ serialPorts = nullptr;
		try{
			// Get a list of serial port names.
			serialPorts = SerialPort::GetPortNames();
		}
		catch (Win32Exception^ ex){
			Console::WriteLine(ex->Message);
		}

		Console::WriteLine("The following serial ports were found:");
		// Display each port name to the console.
		for each(String^ port in serialPorts){
			Console::WriteLine(port);
		}

		//Asks the user to specifiy the COM Port
		std::cout << "Please enter the COM Port that the uStepper is attached to, in the format 'COM*': ";
		cin >> portNameStdStr;
		if (portNameStdStr.size() < 4) {
			flag = FALSE;
			cout << "length of the port number wrong!" << endl;
		}
		else {
			str1 = portNameStdStr.substr(0, 3);     // split com
			str2 = portNameStdStr.substr(3);     // split com 

			transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
			if (str1 != "com") {
				cout << "Port number should be in 'COM*' format" << endl;
			}
			else if (isdigitPort(str2) == FALSE) {
				cout << "port number should be digit" << endl;
			}
			else {
				flag = TRUE;
			}
		}
	} while (flag == FALSE);

	return str1.append(str2);

}



bool is_file_exist(const char *fileName) {
	std::ifstream infile(fileName);
	return infile.good();
}

bool fireLaser() {

	//fire laser for 30 seconds;

	Sleep(30*1000);
	return TRUE;
}

bool checkImage() {
	bool flag;
	string fileName;//the name of the BMP file
	cout << "if the image exist?" << endl;
	if (is_file_exist("BMP.jpg") == 0) {//check is the image exist or not.
		cout << "No, image not exist";
		flag = FALSE;
	}
	else {  //if the image do exist.
		cout << "Yes Image exist";
		flag = TRUE;
	}
	if (flag = TRUE) {

		cout << "rename the file with distance and power!" << endl;
		cin >> fileName;
		string NewName;
		string extention;
		extention = ".jpg";
		NewName = fileName + extention;
		rename("BMP.jpg", NewName.c_str());
	}

	return flag;
}

[STAThread]
void main(cli::array<String^>^ args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	StepperControl::MyForm form;
	Application::Run(%form);

	cout << "*************************************************************************" << endl;
	std::cout << "This program is designed to move the linear actuator in increments \nwith a 2.5 micron resolution, and an input range of -32,768 to 32,767." << std::endl;
	cout << "*************************************************************************" << endl;
	gcroot<String^> portName; //Defines the COM Port used to communicate with the uStepper 
	string portNameStdStr;

	portNameStdStr = checkPortNum();   //check both part of the input
	portName = gcnew String(portNameStdStr.c_str());
	//Creates uStepper object and opens the connection
	uStepper = gcnew SerialPort(portName, baudRate);
	uStepper->Open();

	//uStepper->WriteLine("0");
	//Sleep(5000);
	cout << "Moving to the home position" << endl;
	TraverseMove(0);

	bool flag = TRUE;
	while (flag) {
		string rev = "n";
		Sleep(500);
		cout << "Please enter the distance (step) you would like to move in microns, \nwith a positive value being for forward movement, and a negative one for reverse:" << endl;
		cout << "enter 3206 = one revolution " << endl;
		movementDistance = inputValidation(32767, -32768);
		cout << "moveDistance" << movementDistance << endl;
		TraverseMove(movementDistance);
	}

}

