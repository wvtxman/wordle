#include "pch.h"
#include "ClassPublic.h"
#include <ctime>
#include <iostream>
#include <chrono>
using namespace std;
// Get the current date/time. The format is YYYY-MM-DD.HH:mm:ss
 


string currentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);

    std::cout << "Current Time and Date: " << std::ctime(&end_time) << std::endl;
    
    return std::ctime(&end_time);
}

 struct {             // Structure declaration
     std::string date; ;         // Member (int variable)
     std::string firstpo;   // Member (string variable)
     std::string secondpo;
     std::string material;
     std::string vendor;
     std::string who;
     double poamount;
 } ponumbers;       // Structure variable
  
