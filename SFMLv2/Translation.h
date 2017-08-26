#pragma once
#include <string>
#include "enumLanguagesCodes.h"


class Translation
{
	enumLanguagesCodes languageCode;
	std::wstring translation;

public:
	Translation(enumLanguagesCodes, const std::wstring& translation);

	enumLanguagesCodes getLanguageCode() const{ return languageCode; }

	std::wstring getTranslation() const { return translation; }

};

