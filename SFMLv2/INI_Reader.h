#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>

using std::list;
using std::string;


class INI_Reader
{
	struct SettingLine
	{
		string name;
		string value;
	};

	struct SettingGroup
	{
		string groupName; 
		list<SettingLine> lines;
	};

	struct SettingFile
	{
		string filePath;
		list<SettingGroup> groups;
	};

	//SettingFile settings;
	bool isEmpty;
	bool shouldUpdateFile;

		// FUNCTIONS

	// updates config file if any changes in settings have been made 
	// or if config file does not exits
	void saveToFile(const string& filePath);

	// loads default config is config file is missing
	void loadDefaultConfig();

public:
	SettingFile settings;

	INI_Reader(const string& filePath);
	
	// returns value from section "groupName" assigned to "optionName"
	// if data is invalid, returns empty string
	string getValue(const string& groupName, const string& optionName) const;
	
	// changes value from setction "groupName" assigned to "optionName"
	// if section or option does not exists, the function does nothing
	void changeValue(const string& groupName, const string& optionName, const string& newValue);

	// returns false if Constructor could not open file
	bool isInitialized() const { return !isEmpty; }
	
	~INI_Reader();
	
};
