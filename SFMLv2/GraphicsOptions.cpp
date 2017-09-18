#include "GraphicsOptions.h"

using std::string;

const std::array<res, 6> AvaliableResolutions::avaliableRes =
{
	res("1024x576",sf::Vector2i(1024, 576)),
	res("1280x720",sf::Vector2i(1280, 720)),
	res("1366x768",sf::Vector2i(1366, 768)),
	res("1600x900",sf::Vector2i(1600, 900)),
	res("1920x1080",sf::Vector2i(1920, 1080)),
	res("2560x1440",sf::Vector2i(2560, 1440))
};

const sf::Vector2i GraphicsOptions::defaultResolution(AvaliableResolutions::avaliableRes[0].resolution_number);
const bool GraphicsOptions::defaultFullScreen = false;
const bool GraphicsOptions::defaultVerticalSyncEnabled = false;
const int GraphicsOptions::defaultResolutionScale = 100;
const bool GraphicsOptions::defaultAntialiasing = true;

const string GraphicsOptions::s_yes = "Yes";
const string GraphicsOptions::s_no = "No";
const string GraphicsOptions::s_verticalsyncenabled = "VerticalSync";
const string GraphicsOptions::s_graphics = "Graphics";
const string GraphicsOptions::s_resolution = "Resolution";
const string GraphicsOptions::s_resolutionscale = "ResolutionScale";
const string GraphicsOptions::s_fullscreen = "FullScreen";
const string GraphicsOptions::s_x = "x";
const string GraphicsOptions::s_antialiasing = "Antialiasing";


GraphicsOptions::GraphicsOptions(INI_Reader & reader)
	: Resolution(sf::Vector2i(0, 0)), ResolutionScale(100), VerticalSyncEnabled(false), FullScreen(false), reader(reader),
	hasFullScreenChanged(false), hasResolutionChanged(false), hasResolutionScaleChanged(false), hasVerticalSyncChanged(false), 
	desktopResolution(0,0), antialiasing(false)
{
	const SettingFile& config = reader.getSettings();

	// Resolution
	try
	{
		int x = reader.getValue(s_graphics, s_resolution).find(s_x);
		int beg = 0;
		Resolution.x = std::stoi(reader.getValue(s_graphics, s_resolution).substr(beg, x));
		Resolution.y = std::stoi(reader.getValue(s_graphics, s_resolution).substr(x + 1));
	}
	catch (...) {}

	if (!isResolutionSupported(Resolution))
	{
		Resolution = AvaliableResolutions::avaliableRes[0].resolution_number;
		reader.insertValue(s_graphics, s_resolution, AvaliableResolutions::avaliableRes[0].resolution_text);
	}

	// VerticalSyncEnabled
	string tmp = reader.getValue(s_graphics, s_verticalsyncenabled);
	if (tmp == s_yes)
		VerticalSyncEnabled = true;
	else if (tmp == s_no)
		VerticalSyncEnabled = false;
	else
	{
		if (defaultVerticalSyncEnabled)
		{
			reader.insertValue(s_graphics, s_verticalsyncenabled, s_yes);
			VerticalSyncEnabled = true;
		}
		else
			reader.insertValue(s_graphics, s_verticalsyncenabled, s_no);
	}

	// FullScreen
	tmp = reader.getValue(s_graphics, s_fullscreen);
	if (tmp == s_yes)
		FullScreen = true;
	else if (tmp == s_no)
		FullScreen = false;
	else
	{
		if (defaultFullScreen)
		{
			reader.insertValue(s_graphics, s_fullscreen, s_yes);
			FullScreen = true;
		}
		else
			reader.insertValue(s_graphics, s_fullscreen, s_no);
	}

	// Antialiasing
	tmp = reader.getValue(s_graphics, s_antialiasing);
	if (tmp == s_yes)
		antialiasing = true;
	else if (tmp == s_no)
		antialiasing = false;
	else
	{
		if (defaultAntialiasing)
		{
			reader.insertValue(s_graphics, s_antialiasing, s_yes);
			antialiasing = true;
		}
		else
			reader.insertValue(s_graphics, s_antialiasing, s_no);
	}

	// ResolutionScale
	try
	{
		ResolutionScale = stoi(reader.getValue(s_graphics, s_resolutionscale));
	}
	catch (...) {}

	if (ResolutionScale < AvaliableResolutionScales::minScale || ResolutionScale > AvaliableResolutionScales::maxScale)
	{
		ResolutionScale = 100;
		reader.insertValue(s_graphics, s_resolutionscale, std::to_string(ResolutionScale));
	}

	// Managing creating copy
	// copyTemp value stops executing constructor over and over (it allows it only for 1 copy)
	static bool copyTemp = true;
	if (copyTemp)
	{
		copyTemp = false;
		previousOptions = std::make_unique<GraphicsOptions>(GraphicsOptions(reader));
	}
	else
		copyTemp = true;
}

bool GraphicsOptions::isResolutionSupported(const sf::Vector2i & Resolution) const
{
	for (auto it = AvaliableResolutions::avaliableRes.begin(); it != AvaliableResolutions::avaliableRes.end(); ++it)
	{
		if (Resolution == it->resolution_number)
			return true;
	}
	return false;
}

void GraphicsOptions::setResolution(const string & res)
{
	if (res == "")
		return;

	sf::Vector2i newResolution(0, 0);
	try
	{
		int x = res.find(s_x);
		int beg = 0;
		newResolution.x = std::stoi(res.substr(beg, x));
		newResolution.y = std::stoi(res.substr(x + 1));
	}
	catch (...) {}

	if (isResolutionSupported(newResolution))
	{
		if (Resolution != newResolution)
		{
			Resolution = newResolution;
			hasResolutionChanged = true;
		}
		reader.insertValue(s_graphics, s_resolution, res);
	}
}

void GraphicsOptions::setVerticalSyncEnabled(const std::string& isEnabled)
{
	if (isEnabled == s_yes)
	{
		VerticalSyncEnabled = true;
		reader.insertValue(s_graphics, s_verticalsyncenabled, s_yes);
	}
	else if (isEnabled == s_no)
	{
		VerticalSyncEnabled = false;
		reader.insertValue(s_graphics, s_verticalsyncenabled, s_no);
	}
}

void GraphicsOptions::setFullScreen(const std::string& isEnabled)
{
	if (isEnabled == s_yes)
	{
		if (!FullScreen)
		{
			hasFullScreenChanged = true;
		}
		FullScreen = true;
		reader.insertValue(s_graphics, s_fullscreen, s_yes);
	}
	else if (isEnabled == s_no)
	{	if(FullScreen)
		{
			hasFullScreenChanged = true;
		}
		FullScreen = false;
		reader.insertValue(s_graphics, s_fullscreen, s_no);
	}
}

void GraphicsOptions::setAntialiasingEnabled(const std::string & isEnabled)
{
	if (isEnabled == s_yes)
	{
		antialiasing = true;
		reader.insertValue(s_graphics, s_antialiasing, s_yes);
	}
	else if (isEnabled == s_no)
	{
		antialiasing = false;
		reader.insertValue(s_graphics, s_antialiasing, s_no);
	}

}

void GraphicsOptions::setResolutionScale(const std::string& resScale)
{
	if (resScale == "")
		return;

	int newResScale = 0;
	try
	{
		newResScale = stoi(resScale);
	}
	catch (...) {}

	if (newResScale >= AvaliableResolutionScales::minScale && newResScale <= AvaliableResolutionScales::maxScale)
	{
		ResolutionScale = newResScale;
		reader.insertValue(s_graphics, s_resolutionscale, resScale);
	}
}

std::string GraphicsOptions::isVerticalSyncEnabled_string() const
{
	if (VerticalSyncEnabled)
		return s_yes;
	else
		return s_no;
}

std::string GraphicsOptions::isFullScreenEnabled_string() const
{
	if (FullScreen)
		return s_yes;
	else
		return s_no;
}

std::string GraphicsOptions::isAntialiasingEnabled_string() const
{
	if (antialiasing)
		return s_yes;
	else
		return s_no;
}

void GraphicsOptions::saveToPreviousOptions()
{
	previousOptions->FullScreen = FullScreen;
	previousOptions->Resolution = Resolution;
	previousOptions->ResolutionScale = ResolutionScale;
	previousOptions->VerticalSyncEnabled = VerticalSyncEnabled;
	previousOptions->antialiasing = antialiasing;
	previousOptions->hasFullScreenChanged = hasFullScreenChanged;
	previousOptions->hasResolutionChanged = hasResolutionChanged;
	previousOptions->hasResolutionScaleChanged = hasResolutionScaleChanged;
	previousOptions->hasVerticalSyncChanged = hasVerticalSyncChanged;
}

void GraphicsOptions::restorePreviousOptions()
{
	FullScreen = previousOptions->FullScreen;
	Resolution = previousOptions->Resolution;
	ResolutionScale = previousOptions->ResolutionScale;
	VerticalSyncEnabled = previousOptions->VerticalSyncEnabled;
	antialiasing = previousOptions->antialiasing;
	hasFullScreenChanged = previousOptions->hasFullScreenChanged;
	hasResolutionChanged = previousOptions->hasResolutionChanged;
	hasResolutionScaleChanged = previousOptions->hasResolutionScaleChanged;
	hasVerticalSyncChanged = previousOptions->hasVerticalSyncChanged;
}

bool GraphicsOptions::hasAnyOptionChanged() const
{
	if (FullScreen == previousOptions->FullScreen
		&& Resolution == previousOptions->Resolution
		&& ResolutionScale == previousOptions->ResolutionScale
		&& VerticalSyncEnabled == previousOptions->VerticalSyncEnabled
		&& antialiasing == previousOptions->antialiasing)
		return false;
	return true;
}

void GraphicsOptions::loadDefaults()
{ 
	Resolution = defaultResolution;
	VerticalSyncEnabled = defaultVerticalSyncEnabled;
	ResolutionScale = defaultResolutionScale;
	FullScreen = defaultFullScreen;
	antialiasing = defaultAntialiasing;
	saveToPreviousOptions();
}

void GraphicsOptions::saveToFile()
{
	setResolution(getResolution_string());
	setVerticalSyncEnabled(isVerticalSyncEnabled_string());
	setFullScreen(isFullScreenEnabled_string());
	setResolutionScale(getResolutionScale_string());
	setAntialiasingEnabled(isAntialiasingEnabled_string());
}

std::string AvaliableResolutions::getResolutionString()
{
	std::string res;
	for (auto it = AvaliableResolutions::avaliableRes.begin(); it != AvaliableResolutions::avaliableRes.end(); ++it)
	{
		res += it->resolution_text;
		// if it is the last resolution option, do not put ','
		if ((++it) == AvaliableResolutions::avaliableRes.end());
		else
			res += ',';
		--it;
	}
	return res;
}

std::string AvaliableResolutionScales::getScaleString()
{
	std::string tmp;
	int i = minScale;
	while (i <= maxScale)
	{
		tmp += std::to_string(i);
		if (i + add <= maxScale)
			tmp += ',';
		i += add;
	}
	return tmp;
}
