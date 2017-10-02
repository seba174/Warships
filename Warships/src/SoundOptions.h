#pragma once
#include "INI_Reader.h"

class SoundOptions
{
	int menuThemeVolume, inGameThemeVolume, effectsVolume;
	INI_Reader& reader;
	std::unique_ptr<SoundOptions> previousOptions = nullptr;

	static const int defaultMenuThemeVolume;
	static const int defaultInGameThemeVolume;
	static const int defaultEffectsVolume;

public:
	static const std::string s_sounds;
	static const std::string s_menuThemeVolume;
	static const std::string s_inGameThemeVolume;
	static const std::string s_effectsVolume;

	SoundOptions(INI_Reader& config);

	// saves currently choosed options to previous setting
	void saveToPreviousOptions();

	// restores previous settings from last save
	void restorePreviousOptions();

	// function load default settings
	void loadDefaults();

	// checks if any of option is different from previous settings
	bool hasAnyOptionChanged() const;

	// function saves SoundOptions to .ini file
	void saveToFile();

	void setMenuThemeVolume(const std::string& newMenuThemeVolume);

	void setInGameThemeVolume(const std::string& newInGameThemeVolume);

	void setEffectsVolume(const std::string& newEffectsVolume);

	std::string getMenuThemeVolume_string() const { return std::to_string(menuThemeVolume); }

	std::string getInGameThemeVolume_string() const { return std::to_string(inGameThemeVolume); }

	std::string getEffectsVolume_string() const { return std::to_string(effectsVolume); }

	int getMenuThemeVolume() const { return menuThemeVolume; }

	int getEffectsVolume() const { return effectsVolume; }

	int getInGameThemeVolume() const { return inGameThemeVolume; }
};

