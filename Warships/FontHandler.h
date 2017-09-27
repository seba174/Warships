#pragma once

class FontHandler
{
private:
	
	// Private Constructor
	FontHandler() {};
	
	// Stop the compiler generating methods of copy the object
	FontHandler(FontHandler const& copy) = delete;            // Not Implemented
	FontHandler& operator=(FontHandler const& copy) = delete; // Not Implemented

public:
	
	// returns THE ONLY EXISTING object for handling Fonts
	// font_handler field is made public for getting fonts 
	// e.g font_handler["font_name"] returns reference to the font
	static FontHandler& getInstance();

	std::map<std::string, sf::Font> font_handler;
};