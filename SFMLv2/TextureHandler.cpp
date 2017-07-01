#include "TextureHandler.h"

TextureHandler::TextureHandler()
{
}

TextureHandler & TextureHandler::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static TextureHandler instance;
	static bool initialize = true;
	if (initialize)
	{
		sf::Texture tmp;
		if (!tmp.loadFromFile("Textures/nowefalev5.png"));
		else instance.texture_handler.insert(make_pair("nowefalev5", tmp));
	
		if (!tmp.loadFromFile("Textures/big_body_final.png"));
		else instance.texture_handler.insert(make_pair("big_body_final", tmp));
		
		if (!tmp.loadFromFile("Textures/irregular2.png"));
		else instance.texture_handler.insert(make_pair("irregular2", tmp));
		
		if (!tmp.loadFromFile("Textures/irregular3_final.png"));
		else instance.texture_handler.insert(make_pair("irregular3", tmp));
	
		if (!tmp.loadFromFile("Textures/buttonFrame.png")) std::cout << "NIE UDALO SIE ZALADOWAC!" << std::endl;
		else instance.texture_handler.insert(make_pair("buttonFrame", tmp));
		
		if (!tmp.loadFromFile("Textures/rightArrowOutlined.png")) std::cout << "NIE UDALO SIE ZALADOWAC!" << std::endl;
		else instance.texture_handler.insert(make_pair("rightarrow", tmp));

		if (!tmp.loadFromFile("Textures/leftArrowOutlined.png")) std::cout << "NIE UDALO SIE ZALADOWAC!" << std::endl;
		else instance.texture_handler.insert(make_pair("leftarrow", tmp));

		if (!tmp.loadFromFile("Textures/Untitled.png"))std::cout << "nie ma!";
		else instance.texture_handler.insert(make_pair("test", tmp));

		initialize = false;
	}
	return instance;
}
