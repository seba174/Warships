#include "SimpleLogger.h"
#include <ctime>
#include <fstream>
#include "UtilityFunctions.h"

const std::string SimpleLogger::versionString = "Version";
const std::string SimpleLogger::mapSizeString = "MapSize";
const std::string SimpleLogger::AILevelString = "AILevel";
const std::string SimpleLogger::AIShotsFiredString = "AIShotsFired";
const std::string SimpleLogger::accuracyPlayer1String = "AccuracyPlayer1";
const std::string SimpleLogger::accuracyPlayer2String = "AccuracyPlayer2";
const std::string SimpleLogger::accuracyAIString = "AccuracyComputer";
const std::string SimpleLogger::playerVsAIString = "PlayerVsAIMode";
const std::string SimpleLogger::playerVsPlayerString = "PlayerVsPlayerMode";


SimpleLogger::SimpleLogger(const std::string & filePath, const std::string& version)
{
	logFile.filePath = filePath;
	gameVersion = version;
}

void SimpleLogger::logPlayerVsAIGame(int mapSize, LevelsDifficulty level, unsigned AIShotsFired, bool activated, float AccuracyPlayer, unsigned starsPlayer, float AccuracyAI, unsigned starsAI)
{
	bool isDataValid = true;
	SettingGroup group;
	struct tm ptm;

	std::string stringLevel;
	switch (level)
	{
	case LevelsDifficulty::EASY:
		stringLevel = "Easy"; break;
	case LevelsDifficulty::MEDIUM:
		stringLevel = "Medium"; break;
	case LevelsDifficulty::HARD:
		stringLevel = "Hard"; break;
	}

	time(&timer);
	if (timer == -1)
		isDataValid = false;

	group.groupName = playerVsAIString;
	if (isDataValid)
	{
		gmtime_s(&ptm, &timer);
		std::string day(std::to_string(ptm.tm_mday)), month(std::to_string(ptm.tm_mon + 1)), year(std::to_string(ptm.tm_year + 1900)),
			hours(std::to_string(ptm.tm_hour)), minutes(std::to_string(ptm.tm_min)), seconds(std::to_string(ptm.tm_sec));
		group.lines.push_back(SettingLine('[' + hours + ':' + minutes + ':' + seconds + ", " + day + "." + month + '.' + year + ']', ""));
	}
	else
		group.lines.push_back(SettingLine("[Error reading date]", ""));

	group.lines.push_back(SettingLine(versionString, gameVersion));
	group.lines.push_back(SettingLine(mapSizeString, std::to_string(mapSize)));
	group.lines.push_back(SettingLine(AILevelString, stringLevel));
	if (activated)
		group.lines.push_back(SettingLine(AIShotsFiredString, std::to_string(AIShotsFired) + " (true)"));
	else
		group.lines.push_back(SettingLine(AIShotsFiredString, std::to_string(AIShotsFired) + " (false)"));
	group.lines.push_back(SettingLine(accuracyPlayer1String, floatWith2DecimalPlaces(AccuracyPlayer, std::string()) + " (" + std::to_string(starsPlayer) + " stars)"));
	group.lines.push_back(SettingLine(accuracyAIString, floatWith2DecimalPlaces(AccuracyAI, std::string()) + " (" + std::to_string(starsAI) + " stars)"));

	logFile.groups.push_back(group);
}

void SimpleLogger::logPlayerVsPlayerGame(int mapSize, float AccuracyPlayer1, unsigned starsPlayer1, float AccuracyPlayer2, unsigned starsPlayer2)
{
	bool isDataValid = true;
	SettingGroup group;
	struct tm ptm;

	time(&timer);
	if (timer == -1)
		isDataValid = false;

	group.groupName = playerVsPlayerString;
	if (isDataValid)
	{
		gmtime_s(&ptm, &timer);
		std::string day(std::to_string(ptm.tm_mday)), month(std::to_string(ptm.tm_mon + 1)), year(std::to_string(ptm.tm_year + 1900)),
			hours(std::to_string(ptm.tm_hour)), minutes(std::to_string(ptm.tm_min)), seconds(std::to_string(ptm.tm_sec));
		group.lines.push_back(SettingLine('[' + hours + ':' + minutes + ':' + seconds + ", " + day + "." + month + '.' + year + ']', ""));
	}
	else
		group.lines.push_back(SettingLine("[Error reading date]", ""));

	group.lines.push_back(SettingLine(versionString, gameVersion));
	group.lines.push_back(SettingLine(mapSizeString, std::to_string(mapSize)));
	group.lines.push_back(SettingLine(accuracyPlayer1String, floatWith2DecimalPlaces(AccuracyPlayer1, std::string()) + " (" + std::to_string(starsPlayer1) + " stars)"));
	group.lines.push_back(SettingLine(accuracyPlayer2String, floatWith2DecimalPlaces(AccuracyPlayer2, std::string()) + " (" + std::to_string(starsPlayer2) + " stars)"));

	logFile.groups.push_back(group);
}

void SimpleLogger::saveToFile() const
{
	std::ofstream out(logFile.filePath, std::ios::out | std::ios::app);

	for (auto it = logFile.groups.begin(); it != logFile.groups.end(); ++it)
	{
		std::string tmp;
		tmp += '[' + it->groupName + ']';
		out << tmp << std::endl;
		for (auto it2 = it->lines.begin(); it2 != it->lines.end(); ++it2)
		{
			if (it2->value != "")
			{
				tmp = it2->name + " - " + it2->value;
				out << '\t' << tmp << std::endl;
			}
			else
			{
				tmp = it2->name;
				out << tmp << std::endl;
			}	
		}
		out << std::endl;
	}
	out.close();
}
