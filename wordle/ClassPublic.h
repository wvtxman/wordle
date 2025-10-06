
#pragma once

#include "ClassConvert.h";
 

using namespace System::Runtime::InteropServices;
using namespace std;
using namespace System;
using namespace System::Windows::Forms;



class ClassPublic

{
private:

public:

	int counter;
	Boolean fileFound = false;
	 
	const char* FILE_WORDS = "words.inf";
	

	vector<string> importDictionary()
	{
		string inFile = "ListOfWords.txt";
		string outFile = "FilteredWords.txt";

		fstream inputFile(inFile, ios::in);
		fstream outputFile(outFile, ios::out);

		const int WORD_LENGTH = 5; //5 letters per word

		string str; //string to store in individual words read from file 
		vector<string> arrayToReturn; //vector array to return

		// int vector.capacity() //returns total capacity of vector
		// int vector.size() //returns size (occupied space) of vector

		while (!inputFile.eof()) //end of file function
		{
			inputFile >> str; //read line/word and assign it to str; will ignore whitespaces

			for (int i = 0; i < str.length(); i++)
			{
				if (!isalpha(str[i]))
				{
					str.erase(i, 1);
				}
			}

			if (str.length() == WORD_LENGTH)
			{
				outputFile << str << endl; //output to writing file
				arrayToReturn.push_back(str); //add to vector array
			}
		} //end while

		sort(arrayToReturn.begin(), arrayToReturn.end()); //using algorithm library

		for (int i = 0; i < arrayToReturn.size(); i++)
			outputFile << arrayToReturn[i] << endl; //output to writing file

		inputFile.close();
		outputFile.close();

		return arrayToReturn; //array containing all 'eligible' words
	} //end importDictionary

	vector<string> dictionaryArray = importDictionary(); //dictionary
	 

	struct {
		char word[25];
	}words;


	bool fileExists(const string& filename) {
		ifstream file(filename);
		return file.good();
	}

	const char* SetMainDataDirectory() {
		ClassConvert* classconvert = new ClassConvert();

#ifdef _DEBUG
		// Code specific to debug mode
		String^ AppPath1 = "C:\\cplus\\Wordle Game\\wordle\\";
#else
		String^ AppPath1 = getAppPath() + "\\";
#endif

		std::string AppPath2 = classconvert->ConvertSystemStringToStandardString(AppPath1);
		const char* AppPath = AppPath2.c_str();
		const char* ActualPath = classconvert->CombineTwoConstCharStrings(AppPath, FILE_WORDS);

		 
			const char* MAIN_PROGRAM_PATH = ActualPath;
		 

			 
		
		 


		delete classconvert;
		classconvert = nullptr;
		return  MAIN_PROGRAM_PATH;

	}

	//get the user name that is starting up the program
	std::string getName(std::string path) {


		size_t pos = path.find_last_of("\\\\");
		std::string result = path.substr(pos + 1);
		return result;
	}
 
	std::string capitalizeFirstLetter(std::string& theWord) {

		ClassConvert* classinfo = new ClassConvert();
		bool cap = true;

		for (unsigned int i = 0; i <= theWord.length(); i++)
		{
			if (isalpha(theWord[i]) && cap == true)
			{
				theWord[i] = toupper(theWord[i]);
				cap = false;
			}
			else if (isspace(theWord[i]))
			{
				cap = true;
			}
		}


		return theWord;
	}

	std::string getDate() {


		// Get current time
		time_t currentTime = time(NULL);
		struct tm  localTime;

		localtime_s(&localTime, &currentTime);

		// Extract month, day, and year
		int m = localTime.tm_mon + 1; // tm_mon is 0-11
		int d = localTime.tm_mday; // tm_mday is 1-31
		int year = localTime.tm_year + 1900; // tm_year is years since 1900

		std::string mon = "";
		char* month;

		std::string day;
		char* days;


		if (m < 10) {
			mon = std::to_string(m);
			mon = "0" + mon;
			month = new char[100];


			const char* cstr = mon.c_str();
			// Using strcpy_s
			strcpy_s(month, sizeof(month), cstr);
		}
		else {
			mon = std::to_string(m);
			// Allocate memory for char*
			month = new char[100];
			const char* cstr = mon.c_str();
			// Using strcpy_s
			strcpy_s(month, sizeof(month), cstr);
		}
		if (d < 10) {
			day = std::to_string(d);
			day = "0" + day;
			days = new char[50];

			const char* cstr = day.c_str();
			// Using strcpy_s
			strcpy_s(days, sizeof(days), cstr);


		}
		else {
			day = std::to_string(d);
			// Allocate memory for char*
			days = new char[50];
			const char* cstr = day.c_str();
			// Using strcpy_s
			strcpy_s(days, sizeof(days), cstr);
		}


		std::string str = std::to_string(year);
		const char* years = new char[50];
		years = str.c_str();
		int charSize = sizeof(month) + 50;
		errno_t result = strcat_s(month, charSize, "-");
		result = strcat_s(month, charSize, days);
		result = strcat_s(month, charSize, "-");
		result = strcat_s(month, charSize, years);
		std::string strTime(month);

		return strTime;
	}
 
	String^ getAppPath() {

		ClassConvert* classconvert = new ClassConvert();
		// Define a buffer 
		const int size = 1024;
		// Allocate a character array to store the directory path
		char buffer[size];

		// Call _getcwd to get the current working directory and store it in buffer
		if (_getcwd(buffer, size) != NULL) {
			// print the current working directory
			//cout << "Current working directory: " << buffer << endl;
		}
		std::string pathConverted = classconvert->ConvertCharToStandardString(buffer);
		String^ path = classconvert->ConvertStandardStringToSystem(pathConverted);
		return path;

		delete classconvert;
		classconvert = nullptr;
	}

 
	Boolean checkForDirectory(const char* dir) {



		// Structure which would store the metadata
		struct stat sb;

		// Calls the function with path as argument
		// If the file/directory exists at the path returns 0
		// If block executes if path exists
		if (stat(dir, &sb) == 0)
			return true; // "The path is valid!";
		else
			//	cout << "The Path is invalid!";
			return false;

	}
 

	 
	std::string Trim(const std::string& str) {

		size_t first = str.find_first_not_of(' ');
		if (std::string::npos == first) {
			return ""; // No content
		}
		size_t last = str.find_last_not_of(' ');
		return str.substr(first, (last - first + 1));
	}

 

	std::string getThreeCharsBeforePeriod(const std::string& fileName) {
		size_t pos = fileName.rfind('.');
		if (pos != std::string::npos && pos >= 3) {
			return fileName.substr(pos - 3, 3);
		}
		return ""; // Return empty if not enough characters
	}

	 
	std::string getFirstThreeChar(String^ currentMajorNumber) {

		ClassConvert* classconvert = new ClassConvert();

		std::string MajorNumber = classconvert->ConvertSystemStringToStandardString(currentMajorNumber);

		size_t len = MajorNumber.length();
		std::string firstThreeChars = "";
		if (len == 7) {
			// Get the first three characters

			firstThreeChars = MajorNumber.substr(0, 3);
		}
		else {
			firstThreeChars = MajorNumber.substr(0, 6);
		}
		return firstThreeChars;
		delete classconvert;
		classconvert = nullptr;

	}

	std::string getLastThreeChar(String^ currentMajorNumber) {
		ClassConvert* classconvert = new ClassConvert();
		std::string  lastThreeChars;

		std::string MajorNumber = classconvert->ConvertSystemStringToStandardString(currentMajorNumber);

		size_t len = MajorNumber.length();


		// Get the length of the string
		size_t length = MajorNumber.length();

		// Check if the string has at least three characters
		if (length >= 3)
		{
			// Get the last three characters
			lastThreeChars = MajorNumber.substr(length - 3);
		}

		return lastThreeChars;
		delete classconvert;
		classconvert = nullptr;

	}

	 

	size_t getWordsCount() {

		const char* MAIN_PROGRAM_PATH = SetMainDataDirectory();
		ClassConvert* classconvert = new ClassConvert();
		const char* path = classconvert->CombineTwoConstCharStrings(MAIN_PROGRAM_PATH, FILE_WORDS);
		ifstream file(path, ios::binary);
		size_t recordSize = sizeof(words);
		file.seekg(0, ios::end);
		size_t fileSize;
		size_t recordCount;
		std::streamoff length = file.tellg(); // Get the file size

		if (length >= 0) { // Check for non-negative value
			fileSize = static_cast<size_t>(length); // Safe conversion
			recordCount = fileSize / recordSize;
		}
		else {
			// Handle error: negative length
			recordCount = 0;
		}

		file.close();
		return recordCount;
	}

	std::string extractLastNChars(std::string str, size_t n)
	{
		if (str.size() < n) {
			return str;
		}

		std::string s;
		std::copy_n(str.end() - n, n, std::back_inserter(s));
		return s;
	}

	int charcount(FILE* const fin)
	{
		int c, count;

		count = 0;
		for (;; )
		{
			c = fgetc(fin);
			if (c == EOF || c == '\\n')
				break;
			++count;
		}

		return count;
	}

	void MarshalString(String^ s, string& os) {
		using namespace Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	void MarshalString(String^ s, wstring& os) {
		using namespace Runtime::InteropServices;
		const wchar_t* chars = (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}



};


