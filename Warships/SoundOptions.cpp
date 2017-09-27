#include "stdafx.h"
#include "SoundOptions.h"

const int SoundOptions::defaultMenuThemeVolume = 100;
const int SoundOptions::defaultInGameThemeVolume = 100;
const int SoundOptions::defaultEffectsVolume = 100;

const std::string SoundOptions::s_sounds = "Sounds";
const std::string SoundOptions::s_menuThemeVolume = "MenuThemeVolume";
const std::string SoundOptions::s_inGameThemeVolume = "InGameThemeVolume";
const std::string SoundOptions::s_effectsVolume = "EffectsVolume";

SoundOptions::SoundOptions(INI_Reader & config)
	: reader(config)
{
	std::string tmp = reader.getValue(s_sounds, s_menuThemeVolume);

	// MenuThemeVolume
	int i = defaultMenuThemeVolume;
	try {
		i = std::stoi(tmp);
	}
	catch (...) {}

	if (i >= 0 && i <= 100)
	{
		menuThemeVolume= i;
	}
	else
	{
		menuThemeVolume = defaultMenuThemeVolume;
		reader.insertValue(s_sounds, s_menuThemeVolume, std::to_string(menuThemeVolume));
	}

	// InGameThemeVolume

	tmp = reader.getValue(s_sounds, s_inGameThemeVolume);
	i = defaultInGameThemeVolume;
	try {
		i = std::stoi(tmp);
	}
	catch (...) {}

	if (i >= 0 && i <= 100)
	{
		inGameThemeVolume = i;
	}
	else
	{
		inGameThemeVolume = defaultInGameThemeVolume;
		reader.insertValue(s_sounds, s_inGameThemeVolume, std::to_string(inGameThemeVolume));
	}

	// effectsVolume

	tmp = reader.getValue(s_sounds, s_effectsVolume);
	i = defaultEffectsVolume;
	try {
		i = std::stoi(tmp);
	}
	catch (...) {}

	if (i >= 0 && i <= 100)
	{
		effectsVolume = i;
	}
	else
	{
		effectsVolume = defaultEffectsVolume;
		reader.insertValue(s_sounds, s_effectsVolume, std::to_string(effectsVolume));
	}


	// Managing creating copy
	// copyTemp value stops executing constructor over and over (it allows it only for 1 copy)
	static bool copyTemp = true;
	if (copyTemp)
	{
		copyTemp = false;
		previousOptions = std::make_unique<SoundOptions>(reader);
	}
	else
		copyTemp = true;
}

void SoundOptions::saveToPreviousOptions()
{
	previousOptions->effectsVolume = effectsVolume;
	previousOptions->menuThemeVolume = menuThemeVolume;
	previousOptions->inGameThemeVolume = inGameThemeVolume;
}

void SoundOptions::restorePreviousOptions()
{
	effectsVolume = previousOptions->effectsVolume;
	menuThemeVolume = previousOptions->menuThemeVolume;
	inGameThemeVolume = previousOptions->inGameThemeVolume;
}

void SoundOptions::loadDefaults()
{
	effectsVolume = defaultEffectsVolume;
	menuThemeVolume = defaultMenuThemeVolume;
	inGameThemeVolume = defaultInGameThemeVolume;
}

bool SoundOptions::hasAnyOptionChanged() const
{
	if (effectsVolume == previousOptions->effectsVolume
		&& menuThemeVolume == previousOptions->menuThemeVolume
		&& inGameThemeVolume == previousOptions->inGameThemeVolume)
		return false;
	return true;
}

void SoundOptions::saveToFile()
{
	setMenuThemeVolume(getMenuThemeVolume_string());
	setInGameThemeVolume(getInGameThemeVolume_string());
	setEffectsVolume(getEffectsVolume_string());
}

void SoundOptions::setMenuThemeVolume(const std::string & newMenuThemeVolume)
{
	int newMenuVolume = menuThemeVolume;
	try
	{
		newMenuVolume = std::stoi(newMenuThemeVolume);
	}
	catch (...) {}

	if (newMenuVolume>= 0 && newMenuVolume<= 100)
	{
		menuThemeVolume = newMenuVolume;
		reader.insertValue(s_sounds, s_menuThemeVolume, newMenuThemeVolume);
	}
}

void SoundOptions::setInGameThemeVolume(const std::string & newInGameThemeVolume)
{
	int temp = inGameThemeVolume;
	try
	{
		temp = std::stoi(newInGameThemeVolume);
	}
	catch (...) {}

	if (temp >= 0 && temp<= 100)
	{
		inGameThemeVolume = temp;
		reader.insertValue(s_sounds, s_inGameThemeVolume, newInGameThemeVolume);
	}
}

void SoundOptions::setEffectsVolume(const std::string & newEffectsVolume)
{
	int temp = effectsVolume;
	try
	{
		temp = std::stoi(newEffectsVolume);
	}
	catch (...) {}

	if (temp >= 0 && temp<= 100)
	{
		effectsVolume = temp;
		reader.insertValue(s_sounds, s_effectsVolume, newEffectsVolume);
	}
}
