#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

// Function declarations
int printMenu(vector<string> menu);
time_t convertDateString(string dateStr);
vector<string> split(string s, char delimiter);
string timeToDateString(time_t t);

#endif // MISC_FUNCTIONS_H
