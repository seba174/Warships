#include "TextureHandler.h"
#include <iostream>

using std::make_pair;

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
		std::string error_message("Failed to load textures!");

		sf::Texture tmp;
		if (!tmp.loadFromFile("Textures/nowefalev5.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("nowefalev5", tmp));

		if (!tmp.loadFromFile("Textures/big_body_final.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("big_body_final", tmp));

		if (!tmp.loadFromFile("Textures/big_body_final_destroyed.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("big_body_final_destroyed", tmp));

		if (!tmp.loadFromFile("Textures/irregular2.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("irregular2", tmp));

		if (!tmp.loadFromFile("Textures/irregular3_final_v2.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("irregular3", tmp));

		if (!tmp.loadFromFile("Textures/irregular3_final_v2_destroyed.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("irregular3_destroyed", tmp));

		if (!tmp.loadFromFile("Textures/buttonFrame.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("buttonFrame", tmp));

		if (!tmp.loadFromFile("Textures/rightArrowOutlined.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("rightarrow", tmp));

		if (!tmp.loadFromFile("Textures/leftArrowOutlined.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("leftarrow", tmp));

		if (!tmp.loadFromFile("Textures/big_body_no_waves.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("big_body_no_waves", tmp));

		if (!tmp.loadFromFile("Textures/irregular3_no_waves.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("irregular3_no_waves", tmp));

		if (!tmp.loadFromFile("Textures/irregular2_no_waves.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("irregular2_no_waves", tmp));

		if (!tmp.loadFromFile("Textures/X.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("X", tmp));

		if (!tmp.loadFromFile("Textures/fire5.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("fire5", tmp));

		//testing

		if (!tmp.loadFromFile("Textures/warshipsMenuSG2.jpg")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("menuTexture0", tmp));

		if (!tmp.loadFromFile("Textures/warshipsMenuSG3.jpg")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("menuTexture1", tmp));

		if (!tmp.loadFromFile("Textures/warshipsMenuSG1.jpg")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("menuTexture2", tmp));

		if (!tmp.loadFromFile("Textures/Untitled.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("test", tmp));

		if (!tmp.loadFromFile("Textures/logoSG.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("logo", tmp));

		if (!tmp.loadFromFile("Textures/star.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("star", tmp));

		if (!tmp.loadFromFile("Textures/trophyGold.png")) std::cout << error_message << std::endl;
		else instance.texture_handler.insert(make_pair("cup", tmp));

		
		initialize = false;
	}
	return instance;
}

void TextureHandler::setSmooth(bool shouldSet)
{

	for (auto& el : TextureHandler::getInstance().texture_handler)
	{
		el.second.setSmooth(shouldSet);
	}
}


