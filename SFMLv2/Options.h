#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include "INI_Reader.h"


class res
{
public:
	std::string resolution_text;
	sf::Vector2i resolution_number;

	res(const std::string& resText, const sf::Vector2i& resNumber)
		:resolution_text(resText), resolution_number(resNumber) {}
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
	static const int add = 5;
public:
	static const int minScale = 80, maxScale = 100;

	// Returns string with avaliable resolution scales separated with ','
	// Values are created by adding "add" to minScale while it is smaller than maxScale
	static std::string getScaleString();
};


class Options
{
	// Reader for config file
	INI_Reader& reader;

	bool VerticalSyncEnabled;
	sf::Vector2i Resolution;
	bool FullScreen;
	int ResolutionScale;
	sf::Vector2i desktopResolution;

	// stores previous options
	std::unique_ptr<Options> previousOptions = nullptr;

	// True if one of the values changed it's state (e.g. from true to false)
	bool hasResolutionChanged, hasFullScreenChanged, hasResolutionScaleChanged, hasVerticalSyncChanged;

	// default settings
	static const sf::Vector2i defaultResolution;
	static const bool defaultVerticalSyncEnabled;
	static const bool defaultFullScreen;
	static const int defaultResolutionScale;

public:
	// Default strings with options
	static const std::string s_yes;
	static const std::string s_no;
	static const std::string s_verticalsyncenabled;
	static const std::string s_graphics;
	static const std::string s_resolution;
	static const std::string s_resolutionscale;
	static const std::string s_fullscreen;
	static const std::string s_x;

	// Note that config file can be modified!
	Options(INI_Reader& config);

	// Function checks if Resolution is in AvaliableResolution list
	bool isResolutionSupported(const sf::Vector2i& Resolution) const;

	// Function sets new Resolution
	// X and Y values in string must be separated with s_x string!
	void setResolution(const std::string& res);

	// Function sets VerticalSync option
	// NOTE that only s_yes and s_no strings are accepted!
	void setVerticalSyncEnabled(const std::string& isEnabled);

	// Function sets FullScreen option
	// NOTE that only s_yes and s_no strings are accepted!
	void setFullScreen(const std::string& isEnabled);

	// Function sets ResolutionScale option
	// New ResolutionScale must be valid (inside the AvaliableResolutionScale interval)
	void setResolutionScale(const std::string& resScale);

	// Checks if VerticalSync option is enabled
	bool isVerticalSyncEnabled() const { return VerticalSyncEnabled; }

	// Function returns the current Resolution
	sf::Vector2i getResolution() const { return Resolution; }

	// Checks if the FullScreen option is enabled
	bool isFullScreenEnabled() const { return FullScreen; }

	// Gets ResolutionScales option
	int getResolutionScale() const { return ResolutionScale; }

	// Returns s_yes if VerticalSync is enabled
	// or s_no if VerticalSync is disabled
	std::string isVerticalSyncEnabled_string() const;

	// Returns s_yes if FullScreen is enabled
	// or s_no if FullScreen is disabled
	std::string isFullScreenEnabled_string() const;

	// Chcecks if the Resolution option was changed
	// NOTE that function sets hasResolutionChanged option false 
	bool wasResolutionChanged() { bool tmp = hasResolutionChanged; hasResolutionChanged = false; return tmp; }

	// Chcecks if the FullScreen option was changed
	// NOTE that function sets hasFullScreenChanged option false 
	bool wasFullScreenChanged() { bool tmp = hasFullScreenChanged; hasFullScreenChanged = false; return tmp; }

	// saves currently choosed options to previous setting
	void saveToPreviousOptions();

	// restores previous settings from last save
	void restorePreviousOptions();

	// checks if any of option is different from previous settings
	bool hasAnyOptionChanged() const;

	// function load default settings
	void loadDefaults();

	// sets Desktop Resolution
	void setDesktopResolution(const sf::Vector2i& desktopRes) { desktopResolution = desktopRes; }

	// returns Desktop Resolution
	sf::Vector2i getDesktopResolution() const { return desktopResolution; }

	// returns desktop resolution as a string with Options::s_x value bewtween X and Y coords
	std::string getDesktopResolution_string() const { return std::to_string(desktopResolution.x) + s_x + std::to_string(desktopResolution.y); }

	// returns resolution as a string with Options::s_x value bewtween X and Y coords
	std::string getResolution_string() const { return std::to_string(Resolution.x) + s_x + std::to_string(Resolution.y); }
	
	std::string getResolutionScale_string() const { return std::to_string(ResolutionScale); }

	void saveToFile();
};

