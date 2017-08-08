#pragma once
#include <string>
#include <list>
#include <fstream>


struct SettingLine
{
	std::string name;
	std::string value;
};

struct SettingGroup
{
	std::string groupName;
	std::list<SettingLine> lines;
};

struct SettingFile
{
	std::string filePath;
	std::list<SettingGroup> groups;
};

class INI_Reader
{
	//SettingFile settings;
	bool isEmpty;

		// FUNCTIONS

	// updates config file if any changes in settings have been made 
	// or if config file does not exits
	void saveToFile(const std::string& filePath);

	SettingFile settings;

public:
	
	INI_Reader(const std::string& filePath);
	
	// returns value from section "groupName" assigned to "optionName"
	// if data is invalid, returns empty string
	std::string getValue(const std::string& groupName, const std::string& optionName) const;
	
	// changes value from setction "groupName" assigned to "optionName"
	// if section or option does not exists, the function does nothing
	void changeValue(const std::string& groupName, const std::string& optionName, const std::string& newValue);

	// changes value from setction "groupName" assigned to "optionName"
	// if section or option does not exists, the function creates it
	void insertValue(const std::string& groupName, const std::string& optionName, const std::string& Value);

	// returns false if Constructor could not open file
	bool isInitialized() const { return !isEmpty; }

	const SettingFile& getSettings() const { return settings; }
	
	~INI_Reader();
};

