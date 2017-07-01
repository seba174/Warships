#pragma once
#include <SFML/Graphics.hpp>
#include "INI_Reader.h"

class Options
{
public:

	bool VerticalSyncEnabled;
	sf::Vector2i Resolution;
	bool FullScreen;
	int ResolutionScale;
	INI_Reader& reader;


	Options(INI_Reader& config);


	~Options();
};

