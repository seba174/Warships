#include "GeneralOptions.h"

const enumLanguagesCodes GeneralOptions::defaultLanguage = EN;
const int GeneralOptions::defaultMenuTexture = 0;

const std::string GeneralOptions::s_general = "General";
const std::string GeneralOptions::s_language = "Language";
const std::string GeneralOptions::s_lang_PL = "Polski";
const std::string GeneralOptions::s_lang_EN = "English";
const std::string GeneralOptions::s_menuTexture = "MenuTexture";


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

	//MenuTexture
	tmp = reader.getValue(s_general, s_menuTexture);
	int i = defaultMenuTexture;
	try {
		i = std::stoi(tmp);
	}
	catch (...) {}

	if (i >= 0 && i < numberOfMenuTextures)
	{
		textureNumber = i;
	}
	else
	{
		textureNumber = defaultMenuTexture;
		reader.insertValue(s_general, s_menuTexture, std::to_string(textureNumber));
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

void GeneralOptions::setMenuTexture(const std::string & newTextureNumber)
{
	int textNumber = 0;
	try
	{
		textNumber = std::stoi(newTextureNumber);
	}
	catch (...) {}

	if (textNumber >= 0 && textNumber < numberOfMenuTextures)
	{
		textureNumber = textNumber;
		reader.insertValue(s_general, s_menuTexture, newTextureNumber);
	}
}

void GeneralOptions::saveToPreviousOptions()
{
	previousOptions->language = language;
	previousOptions->textureNumber = textureNumber;
}

void GeneralOptions::restorePreviousOptions()
{
	language = previousOptions->language;
	textureNumber = previousOptions->textureNumber;
}

void GeneralOptions::loadDefaults()
{
	language = defaultLanguage;
	textureNumber = defaultMenuTexture;
}

bool GeneralOptions::hasAnyOptionChanged() const
{
	if (language == previousOptions->language
		&& textureNumber == previousOptions->textureNumber)
		return false;
	return true;
}

void GeneralOptions::saveToFile()
{
	setLanguage(getLanguage_string());
	setMenuTexture(getMenuTextureNumber_string());
}



