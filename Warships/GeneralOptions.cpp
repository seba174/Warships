#include "stdafx.h"
#include "GeneralOptions.h"
#include "Player.h"

const enumLanguagesCodes GeneralOptions::defaultLanguage = EN;
const int GeneralOptions::defaultMenuTexture = 0;
const std::string GeneralOptions::defaultPlayer1Name = "Player1";
const std::string GeneralOptions::defaultPlayer2Name = "Player2";

const std::string GeneralOptions::s_general = "General";
const std::string GeneralOptions::s_language = "Language";
const std::string GeneralOptions::s_lang_PL = "Polski";
const std::string GeneralOptions::s_lang_EN = "English";
const std::string GeneralOptions::s_menuTexture = "MenuTexture";
const std::string GeneralOptions::s_player1Name = "Player1Name";
const std::string GeneralOptions::s_player2Name = "Player2Name";


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


	// Player1Name
	tmp = reader.getValue(s_general, s_player1Name);
	for (auto it = tmp.begin(); it != tmp.end(); ++it)
	{
		if ((*it) < 33 || (*it) > 126)
		{
			tmp = defaultPlayer1Name;
			reader.insertValue(s_general, s_player1Name, tmp);
		}
	}

	if (tmp.size() == 0)
	{
		tmp = defaultPlayer1Name;
		reader.insertValue(s_general, s_player1Name, tmp);
	}

	if (tmp.size() > Player::maximumPlayerNameSize)
	{
		tmp = defaultPlayer1Name;
		reader.insertValue(s_general, s_player1Name, tmp);
	}
	player1Name = tmp;

	// Player2Name
	tmp = reader.getValue(s_general, s_player2Name);
	for (auto it = tmp.begin(); it != tmp.end(); ++it)
	{
		if ((*it) < 33 || (*it) > 126)
		{
			tmp = defaultPlayer2Name;
			reader.insertValue(s_general, s_player2Name, tmp);
		}
	}

	if (tmp.size() == 0)
	{
		tmp = defaultPlayer2Name;
		reader.insertValue(s_general, s_player2Name, tmp);
	}

	if (tmp.size() > Player::maximumPlayerNameSize)
	{
		tmp = defaultPlayer2Name;
		reader.insertValue(s_general, s_player2Name, tmp);
	}
	player2Name = tmp;


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
	return std::string();
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
	player1Name = defaultPlayer1Name;
	player2Name = defaultPlayer2Name;
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
	reader.insertValue(s_general, s_player1Name, player1Name);
	reader.insertValue(s_general, s_player2Name, player2Name);
}



