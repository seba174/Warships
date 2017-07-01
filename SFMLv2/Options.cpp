#include "Options.h"



Options::Options(INI_Reader & reader)
	: Resolution(sf::Vector2i(0,0)), ResolutionScale(100), VerticalSyncEnabled(false), FullScreen(false), reader(reader)
{
	const SettingFile& config = reader.getSettings();
	
	// Resolution
	try
	{
		int x = reader.getValue("Graphics", "Resolution").find('x');
		int beg = 0;
		Resolution.x = std::stoi(reader.getValue("Graphics", "Resolution").substr(beg, x));
		Resolution.y = std::stoi(reader.getValue("Graphics", "Resolution").substr(x + 1));
	}
	catch (...) {}
	
	if (Resolution != sf::Vector2i(960, 540) && Resolution != sf::Vector2i(1280, 720) && Resolution != sf::Vector2i(1600, 900) &&
		Resolution != sf::Vector2i(1024, 576) && Resolution != sf::Vector2i(1366, 768) && Resolution != sf::Vector2i(1920, 1080)
		&& Resolution != sf::Vector2i(2560, 1440))
	{
		Resolution = sf::Vector2i(960, 540);
		reader.insertValue("Graphics", "Resolution", "960x540");
	}
	
	// VerticalSyncEnabled
	string tmp = reader.getValue("Graphics", "VerticalSyncEnabled");
	if (tmp == "Yes" || tmp == "yes")
		VerticalSyncEnabled = true;
	else if (tmp == "No" || tmp == "no")
		VerticalSyncEnabled = false;
	else
	{
		reader.insertValue("Graphics", "VerticalSyncEnabled", "No");
	}

	// FullScreen
	tmp = reader.getValue("Graphics", "FullScreen");
	if (tmp == "Yes" || tmp == "yes")
		FullScreen = true;
	else if (tmp == "No" || tmp == "no")
		FullScreen = false;
	else
	{
		reader.insertValue("Graphics", "FullScreen", "No");
	}

	// ResolutionScale
	try
	{
		ResolutionScale = stoi(reader.getValue("Graphics", "ResolutionScale"));
	}
	catch(...) {}
	
	if (ResolutionScale < 80 || ResolutionScale > 100)
	{
		ResolutionScale = 100;
		reader.insertValue("Graphics", "ResolutionScale", "100");
	}

}

Options::~Options()
{
}
