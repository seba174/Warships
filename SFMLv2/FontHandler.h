#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using std::make_pair;

class FontHandler
{
private:
	
	// Private Constructor
	FontHandler();
	
	// Stop the compiler generating methods of copy the object
	FontHandler(FontHandler const& copy) = delete;            // Not Implemented
	FontHandler& operator=(FontHandler const& copy) = delete; // Not Implemented

public:
	
	// returns the ONLY EXISTING object for handling Fonts
	// font_handler field is made public for getting fonts 
	// e.g font_handler["font_name"] returns REFERENCE to the font!
	static FontHandler& getInstance();

	std::map<std::string, sf::Font> font_handler;
};