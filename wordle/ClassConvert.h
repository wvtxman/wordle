#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <stdlib.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <vector>
#include <utility>
#include <sys/stat.h> 
#include <Windows.h>
#include <direct.h> 
#include <conio.h>
#include <sys/types.h>


using namespace System::Runtime::InteropServices;
using namespace std;
using namespace System;
using namespace System::Windows::Forms;


class ClassConvert
{
private:


public:


	/*
	CONVERTS SYSTEM STRING TO CONST CHAR*
	String^ clistr;
	IntPtr p = Marshal::StringToHGlobalAnsi(clistr);
	const char* linkStr = static_cast<char*>(p.ToPointer());
	system(linkStr);
	Marshal::FreeHGlobal(p);
	return linkStr;
 */
	double ConvertSystemStringToDouble(String^ str) {

		IntPtr ptr = Marshal::StringToHGlobalAnsi(str);
		std::string result(static_cast<char*>(ptr.ToPointer()));
		Marshal::FreeHGlobal(ptr);

		double num = std::stod(result);
		return num;
	}
	String^ ConvertStandardStringToSystem(std::string cpp_str) {


		System::String^ sys_str = gcnew System::String(cpp_str.c_str());
		return sys_str;
	}

	std::string ConvertSystemStringToStandardString(System::String^ sysString) {
		IntPtr ptr = Marshal::StringToHGlobalAnsi(sysString);
		std::string result(static_cast<char*>(ptr.ToPointer()));
		Marshal::FreeHGlobal(ptr);
		return result;
	}

	float ConvertStandardStringToFloat(std::string amount) {

		float invoiceAmount = std::stof(amount);

		return invoiceAmount;
	}
	String^ ConvertIntegerToSystemString(int count) {

		String^ counter = System::Convert::ToString(count);

		return counter;
	}
	int ConvertStandardStringToInteger(std::string str) {

		int num = std::stoi(str);
		return num;
	}

	std::string ConvertIntergerToStandardString(int num) {

		string str = to_string(num);
		return str;
	}

	const char* ConvertStandardStringToChar(std::string myString) {
		const char* charPointer = myString.c_str();
		return charPointer;
	}

	std::string ConvertCharToStandardString(const char* orig) {
		// Convert the C-style string to a basic_string and display it.
		std::string basicstring(orig);
		//basicstring += " (basic_string)";
		return basicstring;
	}

	String^ ConvertCharToSystemString(const char* orig) {
		// Convert the C-style string to a System::String and display it.
		String^ systemstring = gcnew String(orig);
		//	systemstring += " (System::String)";
		return systemstring;
	}


	int ConvertSystemStringToInterger(System::String^ sysString) {
		IntPtr ptr = Marshal::StringToHGlobalAnsi(sysString);
		std::string result(static_cast<char*>(ptr.ToPointer()));
		Marshal::FreeHGlobal(ptr);

		int num = std::stoi(result);
		return num;
	}



	const char* CombineTwoConstCharStrings(const char* str1, const char* str2) {

		// Allocate memory for the combined string
	//	char* combined = new char[strlen(str1) + strlen(str2) + 1]; // +1 for null terminator

		// Copy and concatenate
		//strcpy(combined, str1);
		//strcat(combined, str2);

		char* combined = new char[strlen(str1) + strlen(str2) + 1]; // +1 for null terminator
		strcpy_s(combined, strlen(str1) + 1, str1);
		strcat_s(combined, strlen(str1) + strlen(str2) + 1, str2);

		return combined;
		delete[] combined;

	}
	//used to format numbers to: 10.00
	template <typename T>
	std::string formatAmount(const char* f, T value)
	{
		char buffer[64];
		snprintf(buffer, sizeof(buffer), f, value);
		return string(buffer);
	}



};

