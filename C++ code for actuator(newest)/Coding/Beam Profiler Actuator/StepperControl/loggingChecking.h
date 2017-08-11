#include "stdafx.h"
//
//Name: jinwei.zhang
//
#ifndef LOGGINGCHECKINg_H
#define LOGGINGCHECKING_H
#include <string>
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

//header file of imageChecking class which contains the attribute 
class loggingChecking {

public://(need to imporve)
	//directory of the 
	string dir = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data";
	//full path of the image including name
	string fullPath = "C:\\Users\\jinwei\\Documents\\BeamGage\\Data\\bmp_0001.results.csv";
	//destination of the image which is C:\\Users+username+Documentment+beamgage serial number.
	string destination;

public:
	loggingChecking();//constructor
	~loggingChecking();//deconstuctor
	//int getWrath() { return wrath; };//get wrath method
	//string getType() { return type; };
	//void print_character();//print the foe information.
	bool is_file_exist(string fileName);
	bool checkImage(string path);
	bool removeFile(string path);
	void outputDir(string path);
	std::string base_name(std::string const & path);
	string z_postion();
	string renameFileManual(string path, string dir);
	string renameFileAuto(string machineName, string path, string dir);
	int CopyFile(string initialFilePath, string outputFilePath);
	bool dirExists(const std::string& dirName_in);
	bool makeDir(string dir);
	double readCSV(string path);
};
#endif
