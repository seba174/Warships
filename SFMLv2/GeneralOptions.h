#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "enumLanguagesCodes.h"
#include "INI_Reader.h"



class GeneralOptions
{
	INI_Reader& reader;
	enumLanguagesCodes language;
	std::unique_ptr<GeneralOptions> previousOptions = nullptr;

	static const enumLanguagesCodes defaultLanguage;
public:
	static const std::string s_general;
	static const std::string s_language;
	static const std::string s_lang_PL;
	static const std::string s_lang_EN;

	GeneralOptions(INI_Reader& config);

	enumLanguagesCodes getLanguage() const { return language; }

	std::string getLanguage_string() const;

	void setLanguage(const std::string& newLang);

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

