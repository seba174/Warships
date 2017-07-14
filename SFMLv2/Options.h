#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "INI_Reader.h"


class res
{
public:
	std::string resolution_text;
	sf::Vector2i resolution_number;

	res(const std::string& resText, const sf::Vector2i& resNumber) :resolution_text(resText), resolution_number(resNumber) {}
};


// class which stores an array of avaliable Resolutions
class AvaliableResolutions
{
public:
	static const std::array<res, 7> avaliableRes;

	// Returns string with avaliable resolutions separated with ','
	static std::string getResolutionString();
};


// class which stores the edges of interval of avaliable resolution scales
class AvaliableResolutionScales
{
public:
	static const int minScale = 80, maxScale = 100;

	static std::string getScaleString();
};


class Options
{
	INI_Reader& reader;
	bool VerticalSyncEnabled;
	sf::Vector2i Resolution;
	bool FullScreen;
	int ResolutionScale;
	bool hasResolutionChanged, hasFullScreenChanged, hasResolutionScaleChanged, hasVerticalSyncChanged;

public:
	static const std::string s_yes;
	static const std::string s_no;
	static const std::string s_verticalsyncenabled;
	static const std::string s_graphics;
	static const std::string s_resolution;
	static const std::string s_resolutionscale;
	static const std::string s_fullscreen;
	static const std::string s_x;


	Options(INI_Reader& config);

	bool isResolutionSupported(const sf::Vector2i& Resolution) const;

	void setResolution(const std::string& res);

	void setVerticalSyncEnabled(const std::string& isEnabled);

	void setFullScreen(const std::string& isEnabled);

	void setResolutionScale(const std::string& resScale);


	bool isVerticalSyncEnabled() const { return VerticalSyncEnabled; }

	sf::Vector2i getResolution() const { return Resolution; }

	bool isFullScreenEnabled() const { return FullScreen; }

	int getResolutionScale() const { return ResolutionScale; }

	std::string isVerticalSyncEnabled_string() const;

	std::string isFullScreenEnabled_string() const;

	bool wasResolutionChanged() { bool tmp = hasResolutionChanged; hasResolutionChanged = false; return tmp; }

	bool wasFullScreenChanged() { bool tmp = hasFullScreenChanged; hasFullScreenChanged = false; return tmp; }


	~Options();
};

