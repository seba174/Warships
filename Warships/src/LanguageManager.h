#pragma once
#include "Translation.h"


class LanguageManager
{
	enumLanguagesCodes lang;
	std::map<std::string, std::list<Translation>> hashMap;

public:

	LanguageManager(enumLanguagesCodes code);

	std::wstring getText(const std::string& code) const;
};

