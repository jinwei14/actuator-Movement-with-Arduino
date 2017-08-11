// 
// This program is designing to work with a uStepper board and an Ooznest linear actuator. 
// It allows the user to enter the distance they would like to move along the actuator. 
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
#using <System.dll>
#include "loggingChecking.h"
#include "ployfit.h"
using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;
using namespace std;


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
	if (movement < 0) {
		Sleep(-movement);
	}else if (movement > 0) {
		Sleep(movement);
	}
	String^ message = uStepper->ReadLine(); //Reads the encoder value from the uStepper
	std::string distanceTravelled; //Initialises the variable for distance travelled
	distanceTravelled = msclr::interop::marshal_as<std::string>(message); //Converts the uStepper value into a string
	cout << distanceTravelled << endl; //Prints the string to the console for checking
}

//input validation between the minimum  number to the maximum number.
//input should only contain number. (eg 1a, a1 111b will not be accepted)
int inputValidation(int low, int max) {

	int num;
	bool flag = FALSE;
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
			flag = TRUE;//set the flag as 1 and jump out of the loop
		}
		else {//if the input number is not valid then keep entering until the right number
			cout << "input is not a right port Please re-enter: ";
		}
	} while (flag == FALSE);

	return num;
}

//detect user press ENTER button event
bool pressEnterMove() {
	bool flag;
	string input;
	do {
		//prompt user to input enter KEY
		cout << "Please press Enter Key to move 50 mm" << endl;
		//get the first char that been entered
		getline(cin, input);
		if (input.size() == 0) {
			cout << "Move 50 mm." << endl;
			flag = TRUE;
		}//if Enter Key is not been entered
		else {
			flag = FALSE;
		}
	} while (flag == FALSE);
	//return if the user has entered the right key
	return flag;
}

//check if the string contain only number
bool isdigitPort(string str) {
	bool flag = TRUE;
	// loop through the string check if only digit is contained.
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i])) {
			flag = FALSE;
		}
	}
	return flag;
}

//port number validation check if input port match the port number in the serial list
string checkPortNum()
{
	string str1;
	string str2;
	string portNameStdStr;
	bool flag = FALSE;
	//give user a port list that has been connected.
	do {
		cli::array<String^>^ serialPorts = nullptr;
		try {
			serialPorts = SerialPort::GetPortNames();// Get a list of serial port names.
		}catch (Win32Exception^ ex) {
			Console::WriteLine(ex->Message);//output the port list
		}
		if (serialPorts->Length != 0) {
			Console::WriteLine("The following serial ports were found:");
			for each(String^ port in serialPorts) {// Display each port name to the console.
				Console::WriteLine(port);
			}
		}else {
			//no port number has been found, system exist.
			Console::WriteLine("No serial ports were found:");
			system("pause");
			exit(0);
		}
		//Asks the user to specifiy the COM Port
		std::cout << "Please enter the COM Port that the uStepper is attached to, in the format 'COM*': ";
		cin >> portNameStdStr;
		if (portNameStdStr.size() < 4) {//check the length of the string it should less than 4
			flag = FALSE;
			cout << "length of the port number wrong!" << endl;
		}
		//chech the port number be exact format of "COM*"
		else {
			str1 = portNameStdStr.substr(0, 3);     // split com
			str2 = portNameStdStr.substr(3);     // split com 
			//transform the letters into lower case.
			transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
			// check first string be com
			if (str1 != "com") {
				cout << "Port number should be in 'COM*' format" << endl;
			}//check the second be digit
			else if (isdigitPort(str2) == FALSE) {
				cout << "port number should be digit" << endl;
			}//peogram rejected the port if either of them fail 
			else {
				flag = TRUE;
			}
		}
	} while (flag == FALSE);
	//return the whole port number as string
	return str1.append(str2);

}

//check if the file exist in general.
bool is_file_exist(const char *fileName) {
	std::ifstream infile(fileName);
	return infile.good();
}

//bool fireLaser() {
//	//fire laser for 30 seconds;
//	Sleep(30 * 1000);
//	return TRUE;
//}

//bool checkImage() {
//	bool flag;
//	string fileName;//the name of the BMP file
//	cout << "if the image exist?" << endl;
//	if (is_file_exist("BMP.bmp") == 0) {//check is the image exist or not.
//		cout << "No, image not exist";
//		flag = FALSE;
//	}
//	else {  //if the image do exist.
//		cout << "Yes Image exist";
//		flag = TRUE;
//	}
//	if (flag = TRUE) {
//
//		cout << "rename the file with distance and power!" << endl;
//		cin >> fileName;
//		string NewName;
//		string extention;
//		extention = ".bmp";
//		NewName = fileName + extention;
//		rename("BMP.bmp", NewName.c_str());
//	}
//
//	return flag;
//}

//function which moving to the home position until switch is triggered
void movingHome() {

	gcroot<String^> portName; //Defines the COM Port used to communicate with the uStepper 
	string portNameStdStr; //string which accept the port name
	portNameStdStr = checkPortNum();   //check both part of the input
	portName = gcnew String(portNameStdStr.c_str());
	//Creates uStepper object and opens the connection
	uStepper = gcnew SerialPort(portName, baudRate);
	uStepper->Open();
	//uStepper->WriteLine("0");
	//Sleep(5000);
	cout << "Moving to the home position" << endl;
	TraverseMove(0);
}

//process the loggingChecking including csv checking csv renaming csv shifting.
void logProcessing(string machineName, string userName, string serialNo) {
	//instance of the loggingChecking class
	loggingChecking checker;

	cout << "Makeing directory:" << "C:\\Users\\" << userName << "\\Documents\\" << serialNo << endl;
	//define the string of the directory
	checker.destination = "C:\\Users\\" + userName + "\\Documents\\" + serialNo;
	cout << checker.destination;
	//make the directory that defined by user
	checker.makeDir(checker.destination);
	//if the directory already exist output all the file inside
	checker.outputDir(checker.destination);
	cout << "---------------------------------------------------------" << endl;
	bool loop = TRUE;
	while (loop) {
		//judge if the image has been generated
		loop = !checker.checkImage(checker.fullPath);
		if (loop == TRUE) {
			Sleep(1500);
		}
		else {
			//first rename the file as machineName_Date_Time_Z-position_power
			string newName = checker.renameFileAuto(machineName, checker.fullPath, checker.dir);
			//chage the destination and full path 
			checker.destination = checker.destination + newName;
			checker.fullPath = checker.dir + newName;
			//copy the file to the new directory
			checker.CopyFile(checker.fullPath, checker.destination);
			//remove the file in the old directory 
			checker.removeFile(checker.fullPath);
			cout << "---------------------------------------------------------" << endl;
			//change back the directory, fullpath and  destination to previous values
			checker.dir = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data";
			checker.fullPath = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data\\bmp_0001.results.csv";
			checker.destination = "C:\\Users\\" + userName + "\\Documents\\" + serialNo;
			loop = FALSE;
		}
	}
	Sleep(1500);
}

void calculationM2() {
	ployfit pf;
	pf.outputResult();
}


int main(void) {
	loggingChecking fileR;
	double result = fileR.readCSV("C:\\Users\\jinwei\\Documents\\BeamGage\\Data\\bmp_0001.results.csv");
	cout <<"this is final" <<result << endl;
	//strat of the program
	//get the current time
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	cout << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday << '-'
		<< now->tm_hour << ':'
		<< now->tm_min << ':'
		<< now->tm_sec << "(s)"
		<< endl;

	//user input at the beginning of the program.
	string machineName, userName, serialNo, LPower;
	cout << "Enter the machine name" << endl;
	cin >> machineName;
	cout << "Enter the user name" << endl;
	cin >> userName;
	cout << "Enter BeamGage serial number" << endl;
	cin >> serialNo;
	cout << "Laser Power" << endl;
	inputValidation(50, 5000);
	cout << "*************************************************************************" << endl;
	cout << "This program is designed to move the linear actuator in increments" << endl;
	cout << "with a 2.5 micron resolution, and an input range of -32,768 to 32,767." << endl;
	cout << "*************************************************************************" << endl;
	movingHome();

	//main loop the program
	bool flag = TRUE;
	while (flag) {
		Sleep(500);
		//menu prompt for user input
		cout << "Please enter the distance (step) you would like to move in microns," << endl;
		cout << "with a positive value being for forward movement, and a negative one for reverse:" << endl;
		cout << "enter 3206 = one revolution " << endl;
		////Either enter the length of movement by hand or pressing an enter.
		//movementDistance = inputValidation(-32768, 32767);
		//cout << "moveDistance" << movementDistance << endl;
		//TraverseMove(movementDistance);
		if (pressEnterMove()) {
			TraverseMove(500);
			//ployfit pt;
			//pt.addD4sigma(750, 0);
		
		
		}
	
		logProcessing(machineName, userName, serialNo);
		//calculationM2();
		
	}

	return EXIT_SUCCESS;

}

