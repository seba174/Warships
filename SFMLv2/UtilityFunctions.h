#pragma once
#include <string>

// returns a wstring representing given value with only 2 decimal places
// e.g. function returns 70.51 for value 70.515040
std::wstring floatWith2DecimalPlaces(float value, const std::wstring& onlyToReturnWstring);

// returns a string representing given value with only 2 decimal places
// e.g. function returns 70.51 for value 70.515040
std::string floatWith2DecimalPlaces(float value, const std::string& onlyToReturnString);