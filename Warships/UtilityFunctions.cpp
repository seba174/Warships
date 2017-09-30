#include "stdafx.h"
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

std::wstring stringToWstringConversion(const std::string & s)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return std::wstring(converter.from_bytes(s));
}

std::string createStringOfValuesInInterval(int beg, int end, int interval)
{
	int maxIters = 40000;
	std::string temp;
	while (maxIters)
	{
		if (beg <= end)
		{
			temp += std::to_string(beg) + ',';
			beg += interval;
		}
		else
		{
			if (temp.size() != 0)
				temp.erase(temp.end() - 1);
			return temp;
		}
		--maxIters;
	}
	return "";
}
