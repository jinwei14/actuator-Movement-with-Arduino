#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <filesystem>
#include <experimental/filesystem> // C++-standard header file name  
#include <ctime>
namespace fs = std::experimental::filesystem;
using namespace std;
string dir = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data";
string fullPath = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data\\bmp_0001.png";
string destination ;
//validate the input only number should be accepted.
int inputValidation( int low, int max) {

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
			cout << "input is not a right number Please re-enter: ";
		}
	} while (flag == 0);

	return num;
}

//checking if the file is exist
bool is_file_exist(string fileName) {
	std::ifstream infile(fileName);
	return infile.good();
}

//the is method will check if the image exist if so rename the image.
bool checkImage(string path) {
	bool flag;
	cout << "Checking for image" << endl;
	if (is_file_exist(path) == 0) {//check is the image exist or not.
		flag = FALSE;
	}
	else {  //if the image do exist.
		cout << "Image captured" << endl;
		flag = TRUE;
	}

	return flag;
}


//remove the file by it full path
bool removeFile(string path) {
	bool flag;
	if (remove(path.c_str()) != 0) {
		perror("Error deleting file");
		flag = FALSE;
	}
	else {
		puts("Image transferred");
		flag = TRUE;
	}
	return flag;
}

//output the directory that store the image.
void outputDir(string path) {
	for (auto & p : fs::directory_iterator(path)) {
		std::cout << p << std::endl;
	}
}

//return the base name of the file with the extention
std::string base_name(std::string const & path) {
	return path.substr(path.find_last_of("/\\") + 1);
}

//function for z_positon genertaion.
double random_z = 1;
string z_postion() {

	random_z += 1;

	std::ostringstream strs;
	strs << random_z;
	std::string str = strs.str();
	return str;
}



//rename the file by it full path
string renameFileManual(string path, string dir) {
	bool flag;
	string oldName = base_name(path);
	string fileName;//the name of the bitmap file
	cout << "Rename the file with distance and power!" << endl;
	cout << "Old name:" << oldName << endl;
	cin >> fileName;
	string NewName;
	string extention = ".png";
	string slash = "\\";
	NewName = dir + slash + fileName + extention ;
	try {

		rename(path.c_str(), NewName.c_str());
		cout << "Image renamed" << endl;
		flag = TRUE;
	}
	catch (const char* msg) {
		cerr << "Error occur:" << msg << endl;
		flag = FALSE;
	}
	return (slash + fileName + extention);
}

string renameFileAuto(string machineName,string path, string dir) {
	string fileName, NewName;
	string extention = ".png";
	string slash = "\\";
	//get the current time
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
    //give the new name to the file
	fileName = machineName + '_' + std::to_string(now->tm_year + 1900) + '-'
		+ std::to_string(now->tm_mon + 1) + '-'
		+ std::to_string(now->tm_mday) + '-'
		+ std::to_string(now->tm_hour) + '.'
		+ std::to_string(now->tm_min) + '.'
		+ std::to_string(now->tm_sec) + "(s)"+'_'
		+ z_postion();
	NewName = dir + slash + fileName + extention;
	try {

		rename(path.c_str(), NewName.c_str());
		cout << "Image renamed" << endl;
	}
	catch (const char* msg) {
		cerr << "Error occur:" << msg << endl;
	}

	return (slash + fileName + extention);
}



//CopyFile is a simple function that copies a file from arg1 to arg2
int CopyFile(string initialFilePath, string outputFilePath){

	ifstream initialFile(initialFilePath.c_str(), ios::in | ios::binary);
	ofstream outputFile(outputFilePath.c_str(), ios::out | ios::binary);
	//defines the size of the buffer
	initialFile.seekg(0, ios::end);
	long fileSize = initialFile.tellg();
	//Requests the buffer of the predefined size
	//As long as both the input and output files are open...
	if (initialFile.is_open() && outputFile.is_open())
	{
		short * buffer = new short[fileSize / 2];
		//Determine the file's size
		//Then starts from the beginning
		initialFile.seekg(0, ios::beg);
		//Then read enough of the file to fill the buffer
		initialFile.read((char*)buffer, fileSize);
		//And then write out all that was read
		outputFile.write((char*)buffer, fileSize);
		//delete[] buffer;
	}
	//If there were any problems with the copying process, let the user know
	else if (!outputFile.is_open())
	{
		cout << "couldn't open " << outputFilePath << " for copying!\n";
		return 0;
	}
	else if (!initialFile.is_open())
	{
		cout << "couldn't open " << initialFilePath << " for copying!\n";
		return 0;
	}

	initialFile.close();
	outputFile.close();

	return 1;
}

//check if the directory exist or not
bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

//creat the directory and check existence
bool makeDir(string dir) {
	bool flag;
	if (!fs::exists(dir)) { // Check if src folder exists
		fs::create_directory(dir); // create src folder
		flag = TRUE;
	}
	else {//fail making directory
		cout << "Directory already exist" << endl;
		flag = FALSE;
	}
	return flag;
}


int main() {
	//get the current time
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	cout << (now->tm_year + 1900) << '-'
		 << (now->tm_mon + 1) << '-'
		 << now->tm_mday << '-'
		 <<now->tm_hour << ':'
		 <<now->tm_min << ':'
		 <<now->tm_sec <<"(s)"
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
	inputValidation(1,10);
	cout << "Makeing directory:"<< "C:\\Users\\"<< userName <<"\\Documents\\"<<serialNo << endl;
	//define the string of the directory
	destination = "C:\\Users\\" + userName + "\\Documents\\" + serialNo;
	makeDir(destination);
	outputDir(destination);
	cout << "------------------------------------------------" << endl;
	bool loop;
	while (TRUE) {
		loop = !checkImage(fullPath);
		if (loop == TRUE) {
			_sleep(1500);
		}
		else {
			
			string newName = renameFileAuto(machineName,fullPath, dir);
			//chage the destination and full path 
			destination = destination + newName;
			fullPath = dir + newName;
			CopyFile(fullPath, destination);
			removeFile(fullPath);
			cout << "------------------------------------------------" << endl;
			dir = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data";
			fullPath = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data\\bmp_0001.png";
			destination = "C:\\Users\\" + userName + "\\Documents\\" + serialNo;
		}

	}

	//removeFile(fullPath);
	/*string oldName = base_name(fullPath);
	cout << oldName <<  endl;*/

	system("pause");
	return EXIT_SUCCESS;
}