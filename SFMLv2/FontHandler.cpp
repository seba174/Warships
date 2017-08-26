#include "FontHandler.h"

FontHandler::FontHandler()
{
}

FontHandler & FontHandler::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static FontHandler instance;
	static bool initialize = true;
	if (initialize)
	{
		sf::Font tmp;
		if (!tmp.loadFromFile("Fonts/arial.ttf"));
		else instance.font_handler.insert(make_pair("arial", tmp));


		// !! inna nazwa

		if (!tmp.loadFromFile("Fonts/arial.ttf"));
		else instance.font_handler.insert(make_pair("Mecha", tmp));

		initialize = false;
	}
	return instance;
}