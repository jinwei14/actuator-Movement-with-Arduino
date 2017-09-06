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
#include "loggingChecking.h"
#include "ployfit.h"
#include "GUIInterface.h"
#include "inputBox.h"
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
gcroot<SerialPort^> uStepperInstance;
int movementDistance;
//used to record the machine information
string machineName, userName, serialNo, LPower;
string displayStr = "";
//instance of the loggingChecking class
loggingChecking checker;
//used to calculate the M^2 and accept the z-position and d4 sigma.
ployfit ployfitInstance;
//
// The main movement function, takes one argument, which is movement distance
//
void TraverseMove(int movement) {

	
	try
	{

		//Converts the movement integer to a string to send to the arduino
		std::string movementDistanceStr = std::to_string(movement);
		String^ movementDistanceString = gcnew String(movementDistanceStr.c_str());
		//Writes the movement distance to the arduino
		uStepperInstance->WriteLine(movementDistanceString);
		if (movement < 0) {
			Sleep(-movement);
		}
		else if (movement > 0) {
			Sleep(movement);
		}
		else {
			Sleep(1000);
		}
		
		String^ message = uStepperInstance->ReadLine(); //Reads the encoder value from the uStepper
		std::string distanceTravelled; //Initialises the variable for distance travelled
		distanceTravelled = msclr::interop::marshal_as<std::string>(message); //Converts the uStepper value into a string
		cout << distanceTravelled << endl; //Prints the string to the console for checking

	}
	catch (int e)
	{
		cout << "An exception occurred. Exception Nr. " << e << '\n';
	}
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
		////(console)prompt user to input enter KEY
		//cout << "Please press Enter Key to move 50 mm" << endl;
		////get the first char that been entered
		//getline(cin, input);
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
	//check the length of the string
	if (str.size() == 0) {
		flag = FALSE;
	}
	// loop through the string check if only digit is contained.
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i])) {
			flag = FALSE;
		}
	}
	return flag;
}

//(console)port number validation check if input port match the port number in the serial list
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
		//(console)Asks the user to specifiy the COM Port
		/*std::cout << "Please enter the COM Port that the uStepper is attached to, in the format 'COM*': ";
		cin >> portNameStdStr;*/
		msclr::interop::marshal_context context;
		portNameStdStr = context.marshal_as<std::string>(serialPorts[0]);
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
void StepperControl::GUIInterface::movingHome() {

	displayBox->AppendText("Moving to the home position\r\n");
	cout << "Moving to the home position" << endl;
	//gcroot<String^> portName; //Defines the COM Port used to communicate with the uStepper 
	//string portNameStdStr; //string which accept the port name
	//portNameStdStr = checkPortNum();   //check both part of the input
	//portName = gcnew String(portNameStdStr.c_str());
	////Creates uStepper object and opens the connection
	//uStepper = gcnew SerialPort(portName, baudRate);
	//uStepper->Open();

	//uStepper->WriteLine("0");
	//Sleep(5000);
	
	TraverseMove(0);
}

//process the loggingChecking including csv checking csv renaming csv shifting.
void StepperControl::GUIInterface::initialising(string machineName, string userName, string serialNo) {
	
	//instead of output in console 
	displayStr = "Makeing directory:" + (std::string)"C:\\Users\\" + userName + "\\Documents\\" + serialNo +"\r\n";
	displayBox->AppendText(gcnew String(displayStr.c_str()));
	cout << "Makeing directory:" << "C:\\Users\\" << userName << "\\Documents\\" << serialNo << endl;
	//define the string of the directory
	checker.destination = "C:\\Users\\" + userName + "\\Documents\\" + serialNo;
	displayStr = checker.destination + "\r\n";
	displayBox->AppendText(gcnew String(displayStr.c_str()));
	cout << checker.destination;
	//make the directory that defined by user
	checker.makeDir(checker.destination);
	//if the directory already exist output all the file inside (console)
	checker.outputDir(checker.destination);
	displayBox->AppendText("--------------------------------------------------------\r\n");
	cout << "---------------------------------------------------------" << endl;
	
	Sleep(150);
}

void StepperControl::GUIInterface::checkingCSV(string machineName, string userName, string serialNo) {

	bool loop = TRUE;
	while (loop) {
		//judge if the image has been generated
		loop = !checker.checkImage(checker.fullPath);
		displayBox->AppendText ("Checking for CSV file \r\n");
		if (loop == TRUE) {
			Sleep(1500);
		}
		else {
			displayBox->AppendText("CSV captured \r\n");
			loggingChecking fileR;
			double result = fileR.readCSV("C:\\Users\\jinwei\\Documents\\BeamGage\\Data\\
				.results.csv");
			displayBox->AppendText("Data being added");
			//put the d4sigma and the z positoin in an array every single time 
			int i = 0;
			while (true) {
				if (ployfitInstance.getD4sigma()[i] != 0) {
					i++;
				}
				else {
					break;
				}
				
			}
			ployfitInstance.getD4sigma()[i] = result;
			//first rename the file as machineName_Date_Time_Z-position_power
			string newName = checker.renameFileAuto(machineName, checker.fullPath, checker.dir);
			displayBox->AppendText("CSV renamed \r\n");
			//chage the destination and full path 
			checker.destination = checker.destination + newName;
			checker.fullPath = checker.dir + newName;
			//copy the file to the new directory
			checker.CopyFile(checker.fullPath, checker.destination);
			//remove the file in the old directory 
			checker.removeFile(checker.fullPath);
			displayBox->AppendText("CSV transformed \r\n");
			displayBox->AppendText("--------------------------------------------------------\r\n");
			cout << "---------------------------------------------------------" << endl;
			//change back the directory, fullpath and  destination to previous values
			checker.dir = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data";
			checker.fullPath = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data\\D4.results.csv";
			checker.destination = "C:\\Users\\" + userName + "\\Documents\\" + serialNo;
			loop = FALSE;
		}
	}

}



/**
*
*
*
*
*
*event generatede in the userinput box
*
*
*
*
*
*
*
*
*
*/
//button click event : clear all the text in all the textBox
void UserInputControl::inputBox::clearButton2_Click(System::Object^  sender, System::EventArgs^  e) {
	//clean all the test box once the button is clicked. 
	machineNamtextBox1->Clear();
	userNamtextBox2->Clear();
	SerialtextBox3->Clear();
	PowertextBox4->Clear();
}

//button click event : check the power interval and the other textBox.
void UserInputControl::inputBox::confirmButton1_Click(System::Object^  sender, System::EventArgs^  e) {
	//convert the system string to the std string.
	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>(PowertextBox4->Text);
	bool flag = isdigitPort(standardString);
	// system string to int
	int initialpower;
	if (flag == true) {
		initialpower = int::Parse(PowertextBox4->Text);
	}
	//check the length of the each field every blank must be fullfilled.
	if (machineNamtextBox1->Text->Length == 0||
		userNamtextBox2->Text->Length == 0 ||
		SerialtextBox3->Text->Length == 0 ||
		PowertextBox4->Text->Length == 0) {
		String^ message = "You should fill in all the blanks";
		String^ caption = "Blank entry";
		MessageBoxButtons buttons = MessageBoxButtons::OK;
		System::Windows::Forms::DialogResult result;

		// Displays the MessageBox.
		result = MessageBox::Show(this, message, caption, buttons);
	}
	//check the power between the interval 
	else if (flag == false || initialpower > 100 || initialpower < 50){
		//MessageBox(NULL, "The driver is sleeping!!", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		String^ message = "You did not enter a right power. Re-enter?";
		String^ caption = "Power not right";
		MessageBoxButtons buttons = MessageBoxButtons::OK;
		System::Windows::Forms::DialogResult result;

		// Displays the MessageBox.
		result = MessageBox::Show(this, message, caption, buttons);
		PowertextBox4->BackColor = Color::Red; //Pick any Color;
	
	}//load up the new windows if all the input is entered.
	else {
		
		//convert the system string into the std string then store in the variable
		machineName = msclr::interop::marshal_as<std::string>(machineNamtextBox1->Text);
		userName = msclr::interop::marshal_as<std::string>(userNamtextBox2->Text);
		serialNo = msclr::interop::marshal_as<std::string>(SerialtextBox3->Text);
		LPower = msclr::interop::marshal_as<std::string>(PowertextBox4->Text);
		this->Hide();
		//close down the user input windiws and open the main windows.
		StepperControl::GUIInterface ^ mainForm = gcnew StepperControl::GUIInterface();
		mainForm->Show();

	}

}

/**
*
*
*
*
*
*event generatede in the GUI interface
*
*
*
*
*
*
*
*
*
*/

//event: confirm button is clicked. 
void StepperControl::GUIInterface::confirmButton_Click(System::Object^  sender, System::EventArgs^  e) {
	//declear as global variable;
	int baudRate = 115200;
	
	//////////////////
	bool flag = true;
	gcroot<String^> portName; //Defines the COM Port used to communicate with the uStepper
	portName = gcnew String(comboBox1->Text);
	if (comboBox1->Text == "") {
		displayBox->AppendText("Port should not be empty\r\n");

		flag = false;
	}
	if (flag) {
		//Creates uStepper object and opens the connection
		uStepperInstance = gcnew SerialPort(portName, baudRate);
		uStepperInstance->Open();
		displayBox->AppendText("Connect successfully\r\n");
		initialising(machineName, userName, serialNo);
		confirmButton->Enabled = false;
		moveButton->Enabled = true;
	}
}
//event: when the move button is clicked 

void StepperControl::GUIInterface::moveButton_Click(System::Object^  sender, System::EventArgs^  e) {
	TraverseMove(500);
	checkingCSV( machineName, userName,serialNo);
	
}
//event: when the calculate button is clicked 
void StepperControl::GUIInterface::calculateButton_Click(System::Object^  sender, System::EventArgs^  e) {
	//size of the d4sigma data array
	int size = 0;
	while (true) {
		if (ployfitInstance.getD4sigma()[size] != 0) {
			size++;
		}
		else {
			break;
		}

	}
	//if there is enough d4Sigma data 
	if (size >= 15) {
		
		string result = ployfitInstance.outputResult();
		displayBox->AppendText(gcnew String(result.c_str()));
		//display all the information and stored them in a txt file.
		std::ofstream out("output.txt");
		out << result;
		
		ployfit bbb;
		for (int k = 0; k<16; k++){
			out << "D4sigma :" << bbb.getD4sigma()[k] << endl; //Outputs array to txtFile
		}	
		out.close();
		bbb.outputResult();
		bbb.plotFuction();
	}
	else {
		//prompt user there is not enough data
		displayBox->AppendText("Data not enough, Can not calculate the result\r\n");
	}

}
//event when the setHome button is clicked 
void StepperControl::GUIInterface::setHomeButton_Click(System::Object^  sender, System::EventArgs^  e) {
	movingHome();
}
//when the stop button is click.stop the actuator instantly
void StepperControl::GUIInterface::haltButton_Click(System::Object^  sender, System::EventArgs^  e) {

}



//windows form thread that load up the user input windows.
[STAThread]
int main(void) {

	

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false) ;
	//StepperControl::GUIInterface mainForm;
	UserInputControl::inputBox startUp;
	Application::Run(%startUp);
	
	return EXIT_SUCCESS;

}

