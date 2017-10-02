#pragma once
#include "enumLanguagesCodes.h"
#include "INI_Reader.h"


class GeneralOptions
{
	const int numberOfMenuTextures = 3;
	int textureNumber;

	INI_Reader& reader;
	enumLanguagesCodes language;
	std::string player1Name, player2Name;
	std::unique_ptr<GeneralOptions> previousOptions = nullptr;

	static const enumLanguagesCodes defaultLanguage;
	static const int defaultMenuTexture;
	static const std::string defaultPlayer1Name;
	static const std::string defaultPlayer2Name;

public:
	static const std::string s_general;
	static const std::string s_language;
	static const std::string s_lang_PL;
	static const std::string s_lang_EN;
	static const std::string s_menuTexture;
	static const std::string s_player1Name;
	static const std::string s_player2Name;

	GeneralOptions(INI_Reader& config);

	std::string getLanguage_string() const;

	void setLanguage(const std::string& newLang);

	void setMenuTexture(const std::string& newTextureNumber);

	// saves currently choosed options to previous setting
	void saveToPreviousOptions();

	// restores previous settings from last save
	void restorePreviousOptions();

	// function load default settings
	void loadDefaults();

	// checks if any of option is different from previous settings
	bool hasAnyOptionChanged() const;

	// function saves GeneralOptions to .ini file
	void saveToFile();

	void setPlayer1Name(const std::string& s) { player1Name = s; }

	void setPlayer2Name(const std::string& s) { player2Name = s; }

	std::string getPlayer1Name() const { return player1Name; }

	std::string getPlayer2Name() const { return player2Name; }

	int getMenuTextureNumber() const { return textureNumber; }

	std::string getMenuTextureNumber_string() const { return std::to_string(textureNumber); }

	enumLanguagesCodes getLanguage() const { return language; }
};

