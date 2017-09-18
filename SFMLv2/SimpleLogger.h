#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "iniFileStructure.h"
#include "enumLevelsDifficulty.h"

class SimpleLogger
{
	time_t timer;
	SettingFile logFile;
	std::string gameVersion;

	static const std::string versionString;
	static const std::string mapSizeString;
	static const std::string AILevelString;
	static const std::string AIShotsFiredString;
	static const std::string accuracyPlayer1String;
	static const std::string accuracyPlayer2String;
	static const std::string accuracyAIString;
	static const std::string playerVsAIString;
	static const std::string playerVsPlayerString;

public:

	SimpleLogger(const std::string& filePath, const std::string& version);

	void logPlayerVsAIGame(int mapSize, LevelsDifficulty level, unsigned AIShotsFired, bool activated, float AccuracyPlayer, unsigned starsPlayer, float AccuracyAI, unsigned starsAI);

	void logPlayerVsPlayerGame(int mapSize, float AccuracyPlayer1, unsigned starsPlayer1, float AccuracyPlayer2, unsigned starsPlayer2);

	void saveToFile() const;
};

