#include "INI_Reader.h"
#include <iostream>

using std::string;
using std::list;

void INI_Reader::saveToFile(const string & filePath)
{
	std::ofstream out;
	out.open(filePath);

	out << "% Warships config file %" << std::endl << std::endl;
	for (auto it = settings.groups.begin(); it != settings.groups.end(); ++it)
	{
		string tmp;
		tmp += '[' + it->groupName + ']';
		out << tmp << std::endl;
		for (auto it2 = it->lines.begin(); it2 != it->lines.end(); ++it2)
		{
			tmp = it2->name + '=' + it2->value;
			out << tmp << std::endl;
		}
		out << std::endl;
	}
	out.close();
}


INI_Reader::INI_Reader(const string& filePath)
	: isEmpty(false)
{
	settings.filePath = filePath;

	std::ifstream in(filePath);
	if (!in)
	{
		std::cout << "Can't find config file!" << std::endl;
		isEmpty = true;
		return;
	}
	
	string line;
	int numberOfSettingGroups = 0;
	
	while (getline(in, line))
	{
		if (!line.empty())
		{
			int beg = line.find('[');
			int end = line.find(']');
			int tmp = line.find('%');
			if (beg != string::npos && end != string::npos)
			{
				// SettingGroup must have a form [*], where * is at least 1 character
				if (end > beg + 1)
				{
					++numberOfSettingGroups;
					settings.groups.push_back(SettingGroup());

					list<SettingGroup>::iterator it = settings.groups.begin();
					std::advance(it, numberOfSettingGroups - 1);
					(*it).groupName = line.substr(beg + 1, end - (beg + 1));
				}
			}
			// if line has '%' inside, it means it is an comment!
			else if (tmp == string::npos && numberOfSettingGroups > 0)
			{
				list<SettingGroup>::iterator it = settings.groups.begin();
				std::advance(it, numberOfSettingGroups - 1);
				int mid;
				mid = line.find('=');

				// after '=' there must be at least 1 character
				if (mid != string::npos && mid != line.size() - 1)
				{
					SettingLine temp;
					temp.name = line.substr(0, mid);
					temp.value = line.substr(mid + 1);
					(*it).lines.push_back(temp);
				}
			}
		}
	}
	in.close();
}

string INI_Reader::getValue(const string & groupName, const string & optionName) const
{
	for (auto it = settings.groups.begin(); it != settings.groups.end(); ++it)
	{
		if (it->groupName == groupName)
		{
			for (auto tmp = it->lines.begin(); tmp != it->lines.end(); ++tmp)
			{
				if (tmp->name == optionName)
					return tmp->value;
			}
		}
	}
	// returns empty string if data is invalid
	return "";
}

void INI_Reader::changeValue(const string & groupName, const string & optionName, const string & newValue)
{
	// Do not accept empty options
	if (newValue == "")
		return;

	for (auto it = settings.groups.begin(); it != settings.groups.end(); ++it)
	{
		if (it->groupName == groupName)
		{
			for (auto tmp = it->lines.begin(); tmp != it->lines.end(); ++tmp)
			{
				if (tmp->name == optionName)
					tmp->value = newValue;
			}
		}
	}
}

void INI_Reader::insertValue(const string & groupName, const string & optionName, const string & Value)
{
	// Do not accept empty options
	if (Value == "")
		return;

	bool foundGroup = false;
	bool foundOption = false;
	list<SettingGroup>::iterator iter;

	for (auto it = settings.groups.begin(); it != settings.groups.end(); ++it)
	{
		if (it->groupName == groupName)
		{
			for (auto tmp = it->lines.begin(); tmp != it->lines.end(); ++tmp)
			{
				if (tmp->name == optionName)
				{
					tmp->value = Value;
					foundOption = true;
				}
			}
			foundGroup = true;
			iter = it;
		}
	}

	if (!foundGroup)
	{
		SettingGroup group;
		SettingLine line;
		group.groupName = groupName;
		line.name = optionName;
		line.value = Value;
		group.lines.push_back(line);
		settings.groups.push_back(group);
	}
	else if (!foundOption)
	{
		SettingLine line;
		line.name = optionName;
		line.value = Value;
		iter->lines.push_back(line);
	}
}

INI_Reader::~INI_Reader()
{
	saveToFile(settings.filePath);
}
