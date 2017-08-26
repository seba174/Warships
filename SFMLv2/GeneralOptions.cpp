#include "GeneralOptions.h"

const enumLanguagesCodes GeneralOptions::defaultLanguage = EN;

const std::string GeneralOptions::s_general = "General";
const std::string GeneralOptions::s_language = "Language";
const std::string GeneralOptions::s_lang_PL = "Polski";
const std::string GeneralOptions::s_lang_EN = "English";


GeneralOptions::GeneralOptions(INI_Reader & config)
	:reader(config)
{
	// Language
	std::string tmp = reader.getValue(s_general, s_language);
	if (tmp == s_lang_PL)
		language = PL;
	else if (tmp == s_lang_EN)
		language = EN;
	// Default option
	else
	{
		reader.insertValue(s_general, s_language, s_lang_EN);
		language = EN;
	}


	// Managing creating copy
	// copyTemp value stops executing constructor over and over (it allows it only for 1 copy)
	static bool copyTemp = true;
	if (copyTemp)
	{
		copyTemp = false;
		previousOptions = std::make_unique<GeneralOptions>(reader);
	}
	else
		copyTemp = true;
}

std::string GeneralOptions::getLanguage_string() const
{
	switch (language)
	{
	case EN:
		return s_lang_EN;
	case PL:
		return s_lang_PL;
	}
}

void GeneralOptions::setLanguage(const std::string & newLang)
{
	if (newLang == s_lang_EN)
	{
		language = EN;
		reader.insertValue(s_general, s_language, s_lang_EN);
	}
	else if (newLang == s_lang_PL)
	{
		language = PL;
		reader.insertValue(s_general, s_language, s_lang_PL);
	}
}

void GeneralOptions::saveToPreviousOptions()
{
	previousOptions->language = language;
}

void GeneralOptions::restorePreviousOptions()
{
	language = previousOptions->language;
}

void GeneralOptions::loadDefaults()
{
	language = defaultLanguage;
}

bool GeneralOptions::hasAnyOptionChanged() const
{
	if (language == previousOptions->language)
		return false;
	return true;
}

void GeneralOptions::saveToFile()
{
	setLanguage(getLanguage_string());
}



