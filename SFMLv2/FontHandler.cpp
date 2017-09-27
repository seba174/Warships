#include "stdafx.h"
#include "FontHandler.h"

using std::make_pair;


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
		//if (!tmp.loadFromFile("Fonts/arial.ttf"));
		//else instance.font_handler.insert(make_pair("arial", tmp));


		if (!tmp.loadFromFile("Fonts/AutourOne-Regular.otf"));
		else instance.font_handler.insert(make_pair("Mecha", tmp));

		initialize = false;
	}
	return instance;
}