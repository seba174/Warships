#include "UtilityFunctions.h"

std::wstring floatWith2DecimalPlaces(float value, const std::wstring& onlyToReturnWstring)
{
	int integer = static_cast<int>(value), temp;
	float afterDecimalPoint = value - integer;

	temp = static_cast<int>(afterDecimalPoint * 10);
	if (temp == 0)
	{
		temp = static_cast<int>(afterDecimalPoint * 100);
		return std::to_wstring(integer) + L'.' + L'0' + std::to_wstring(temp);
	}

	temp = static_cast<int>(afterDecimalPoint * 100);
	return std::to_wstring(integer) + L'.' + std::to_wstring(temp);
}

std::string floatWith2DecimalPlaces(float value, const std::string & string)
{
	int integer = static_cast<int>(value), temp;
	float afterDecimalPoint = value - integer;

	temp = static_cast<int>(afterDecimalPoint * 10);
	if (temp == 0)
	{
		temp = static_cast<int>(afterDecimalPoint * 100);
		return std::to_string(integer) + '.' + '0' + std::to_string(temp);
	}

	temp = static_cast<int>(afterDecimalPoint * 100);
	return std::to_string(integer) + '.' + std::to_string(temp);
}
