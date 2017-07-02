#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "INI_Reader.h"


class res
{
public:
	string resolution_text;
	sf::Vector2i resolution_number;

	res(const string& resText, const sf::Vector2i& resNumber) :resolution_text(resText), resolution_number(resNumber) {}
};


// class which stores an array of avaliable Resolutions
class AvaliableResolutions
{
public:
	static const std::array<res, 7> avaliableRes;
};


// class which stores the edges of interval of avaliable resolution scales
class AvaliableResolutionScales
{
public:
	static const int minScale = 80, maxScale = 100;
};


class Options
{
	const string s_yes = "Yes";
	const string s_no = "No";
	const string s_verticalsyncenabled = "VerticalSyncEnabled";
	const string s_graphics = "Graphics";
	const string s_resolution = "Resolution";
	const string s_resolutionscale = "ResolutionScale";
	const string s_fullscreen = "FullScreen";
	const string s_x = "x";
public:

	bool VerticalSyncEnabled;
	sf::Vector2i Resolution;
	bool FullScreen;
	int ResolutionScale;
	INI_Reader& reader;


	Options(INI_Reader& config);

	bool isResolutionSupported(const sf::Vector2i& Resolution) const;

	void setResolution(const string& res);

	void setVerticalSyncEnabled(const std::string& isEnabled);

	void setFullScreen(const std::string& isEnabled);

	void setResolutionScale(const std::string& resScale);

	~Options();
};

