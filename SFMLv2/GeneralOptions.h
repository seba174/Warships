#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "enumLanguagesCodes.h"
#include "INI_Reader.h"



class GeneralOptions
{
	const int numberOfMenuTextures = 3;
	int textureNumber;

	INI_Reader& reader;
	enumLanguagesCodes language;
	std::unique_ptr<GeneralOptions> previousOptions = nullptr;

	static const enumLanguagesCodes defaultLanguage;
	static const int defaultMenuTexture;
public:
	static const std::string s_general;
	static const std::string s_language;
	static const std::string s_lang_PL;
	static const std::string s_lang_EN;
	static const std::string s_menuTexture;

	GeneralOptions(INI_Reader& config);

	enumLanguagesCodes getLanguage() const { return language; }

	std::string getLanguage_string() const;

	void setLanguage(const std::string& newLang);

	void setMenuTexture(const std::string& newTextureNumber);

	int getMenuTextureNumber() const { return textureNumber; }

	std::string getMenuTextureNumber_string() const { return std::to_string(textureNumber); }

	// saves currently choosed options to previous setting
	void saveToPreviousOptions();

	// restores previous settings from last save
	void restorePreviousOptions();

	// function load default settings
	void loadDefaults();

	// checks if any of option is different from previous settings
	bool hasAnyOptionChanged() const;

	void saveToFile();
};

